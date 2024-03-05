target remote localhost:1234
file dist/pkos.bin

# use the syntax that NASM uses for debugging
set disassembly-flavor intel

# uncomment to enable gui
tui enable

# break vga.c:vga_enter
# break vga.c:vga_exit

