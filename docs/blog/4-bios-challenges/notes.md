# OS4: Debugging, Functions, and FUN
Tuesday, December 31, 2019
6:41 PM

-   Go over the challenges
    -   Challenge 1-3 (already written) in video2 folder
-   Go over functions
    -   Give example: Print string with call, pusha, popa, ret
-   Go over debugging
    -   Apt install gdb
    -   Debug the print string program or something very simple
-   Create new program with this knowledge (PAUSE TO ATTEMPT)
    -   Print string and hex value w/ separate file includes
    -   Maybe even get input from user? Nah too complex, would need buffer
-   Next video - maybe execute some different code and (IF YOU\'RE LUCKY!) launch 32 bit protected
-   This one should be fairly quick. No slides.
-   ~~Show at least one more cool program~~
    -   ~~Snake?~~
    -   ~~Tip calculator?~~
-   ~~Teaser: Next video we will enter 32-bit protected mode~~
 
- Keep notes
	- <https://stackoverflow.com/questions/14242958/debugging-bootloader-with-gdb-in-qemu>
	- qemu with -s -S
	- gdb
	- target remote localhost:1234
	- br \*0x7c00
	- c
	- x/i \$eip
	- <https://stackoverflow.com/questions/2420813/using-gdb-to-single-step-assembly-code-outside-specified-executable-causes-error>
	- Move to next with stepi/si/nexti/ni
	- <https://stackoverflow.com/questions/8569285/permanently-change-disassembly-flavor-in-gdb>
	- set disassembly-flavor intel
	- Place in file \~/.gdbinit to make permanent
	- **NOTE**
	- FUNCTIONS not preceded with dot. Labels that are not functions are preceded with a dot (convention)
	- <https://stackoverflow.com/questions/5429137/how-to-print-register-values-in-gdb>
	- info registers
	- info registers ax
	- <https://stackoverflow.com/questions/1737095/how-do-i-disassemble-raw-16-bit-x86-machine-code>
	- objdump -D -b binary -mi386 -Maddr16,data16 -Mintel,i8086 filename.bin
	- With NASM, I\'ve had much better experience in gdb when using the dwarf debugging format. gdb then treats the assembly source as if it were any other language (i.e., no disassemble commands necessary)
	- nasm -f elf64 -g -F dwarf file64.asm
	- *From \<<https://stackoverflow.com/questions/7464039/linux-64-bit-nasm-and-gdb>\>*
