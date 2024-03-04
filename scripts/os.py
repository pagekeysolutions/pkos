#!/usr/bin/env python3

import glob
import os
import subprocess
import sys

COLOR_RED_BOLD = '\033[31;1m'
COLOR_YELLOW_BOLD = '\033[33;1m'
COLOR_GREEN_BOLD = '\033[32;1m'
COLOR_CYAN_BOLD = '\033[36;1m'
COLOR_RESET = '\033[0m'

ASSEMBLE_COMMAND = "nasm -f elf32 -g -F dwarf  %s -o %s"
COMPILE_COMMAND = "gcc -m32 -ffreestanding -fno-stack-protector -c %s -o %s"
COMPILE_COMMAND_DEBUG = "gcc -ggdb -Og -m32 -ffreestanding -fno-stack-protector -c %s -o %s"
COMPILE_TEST_COMMAND = "g++ %s %s -m32 -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage"
LINK_COMMAND = "ld -m elf_i386 -T %s -o %s %s %s"

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_DIR = os.path.join(REPO_ROOT, 'src')
TEST_DIR = os.path.join(REPO_ROOT, 'test')
BUILD_DIR = os.path.join(REPO_ROOT, 'build')
DIST_DIR = os.path.join(REPO_ROOT, 'dist')
LINKER_SCRIPT = os.path.join(REPO_ROOT, 'src', 'linker.ld')

ASM_FILES = glob.glob(os.path.join(SRC_DIR, '*', '*.asm'), recursive=True)
SOURCE_FILES = glob.glob(os.path.join(SRC_DIR, '*', '*.c'), recursive=True)
UNIT_TEST_FILES = glob.glob(os.path.join(TEST_DIR, 'unit', '*.cpp'), recursive=True)

BIN_FILES = [f.replace('.asm', '.bin') for f in ASM_FILES]
O_FILES = [f.replace('.c', '.o') for f in SOURCE_FILES]

KERNEL_OUT = os.path.join(DIST_DIR, 'pkos.bin')
ISO_OUT = os.path.join(DIST_DIR, 'pkos.iso')

def pretty_print(message, color=COLOR_GREEN_BOLD):
    print(color + message + COLOR_RESET)

def pretty_call(command, color=COLOR_GREEN_BOLD, shell=False):
    pretty_print(command, color)
    subprocess.check_call(command.split(), shell=shell)

def build(debug=False):
    os.makedirs('build', exist_ok=True)
    os.makedirs('dist', exist_ok=True)
    os.makedirs('public', exist_ok=True)
    # Assemble assembly code
    for file_in, file_out in zip(ASM_FILES, BIN_FILES):
        rendered_command = ASSEMBLE_COMMAND % (file_in, file_out)
        pretty_call(rendered_command, COLOR_RED_BOLD)
    
    # Compile C code
    for file_in, file_out in zip(SOURCE_FILES, O_FILES):
        if debug:
            compile_command = COMPILE_COMMAND_DEBUG
        else:
            compile_command = COMPILE_COMMAND
        rendered_command = compile_command % (file_in, file_out)
        pretty_call(rendered_command, COLOR_YELLOW_BOLD)
    
    # Link the assembly and C code together, create .bin file
    rendered_command = LINK_COMMAND % (
        LINKER_SCRIPT,
        KERNEL_OUT,
        ' '.join(BIN_FILES),
        ' '.join(O_FILES),
    )
    pretty_call(rendered_command, COLOR_CYAN_BOLD)
    
    # Generate ISO file
    pretty_call('mkdir -p build/iso/boot/grub', COLOR_CYAN_BOLD)
    pretty_call('cp grub.cfg build/iso/boot/grub', COLOR_CYAN_BOLD)
    pretty_call('cp %s build/iso/boot/grub' % KERNEL_OUT, COLOR_CYAN_BOLD)
    pretty_call('grub-mkrescue -o %s build/iso' % ISO_OUT, COLOR_CYAN_BOLD)
    pretty_call('rm -rf build', COLOR_CYAN_BOLD)
	
    pretty_print('Built %s' % KERNEL_OUT)
    pretty_print('Built %s' % ISO_OUT)
    print("Done!")

def test():
    # build()
    test_unit()
    test_integration()

def test_unit():
    pretty_call('rm -rf build')
    pretty_call('mkdir build')
    os.chdir(BUILD_DIR)
    pretty_call(
        COMPILE_TEST_COMMAND % (
            ' '.join(UNIT_TEST_FILES), 
            ' '.join(glob.glob(os.path.join(SRC_DIR, 'common', '*.c'))), # temporary workaround
            # ' '.join(BIN_FILES),
            # ' '.join(SOURCE_FILES), # TODO get unit tests working with all source files
        )
    )
    pretty_call('./a.out')
    pretty_call('gcov ../test/unit/*.cpp src/common/*.cpp')
    pretty_call('lcov -b . -d . -c --output-file coverage.info')
    # not sure why this lcov cmd doesn't work with subprocess:
    pretty_print("lcov -r coverage.info '/usr/include/*' '*/test/unit/*.cpp' --output-file coverage.info")
    os.system("lcov -r coverage.info '/usr/include/*' '*/test/unit/*.cpp' --output-file coverage.info")
    pretty_call('genhtml coverage.info --output-directory ../public/')
    os.chdir(REPO_ROOT)

def test_integration():
    pretty_call('pytest %s' % os.path.join(REPO_ROOT, 'test', 'integration'))

SATA_IMG_PATH = 'dist/SATA.img'
SATA_DRIVE_OPTS = f'-drive id=disk,file={SATA_IMG_PATH},if=none -device ahci,id=ahci -device ide-hd,drive=disk,bus=ahci.0'
def run():
    build()
    if not os.path.exists(SATA_IMG_PATH):
        with open(SATA_IMG_PATH, 'w'): # just write a blank file for now
            pass
    pretty_call(f'qemu-system-i386 -debugcon file:dbg.out -kernel {KERNEL_OUT} {SATA_DRIVE_OPTS}')

def run_debug():
    build(debug=True)
    if not os.path.exists(SATA_IMG_PATH):
        with open(SATA_IMG_PATH, 'w'): # just write a blank file for now
            pass
    os.system(f'qemu-system-i386 -kernel {KERNEL_OUT}  {SATA_DRIVE_OPTS} -s -S &')
    os.system('gdb -x .gdbinit')

def clean():
    os.system('rm -rf build dist public *.gcno a.out')

def print_usage():
    print("Usage: %s [build,test,test-unit,run,run_debug,clean]" % sys.argv[0])
    sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print_usage()
    elif sys.argv[1] == 'build':
        build()
    elif sys.argv[1] == 'test':
        test()
    elif sys.argv[1] == 'test-unit':
        test_unit()
    elif sys.argv[1] == 'run':
        run()
    elif sys.argv[1] == 'run_debug':
        run_debug()
    elif sys.argv[1] == 'clean':
        clean()
    else:
        print("Command not recognized: %s" % sys.argv[1])
        print_usage()
