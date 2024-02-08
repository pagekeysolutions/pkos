# OS9: Multiboot (Bootloader Breakup)
Sunday, June 21, 2020
12:00 PM
 
- Welcome back - I hope you\'re having a great day. This is OS9, where we make our kernel multiboot compliant!
- What\'s that mean, you may ask? Why would we want to do it?
- Like I said in the last video, I\'m moving away from rolling our own bootloader, instead choosing to focus on developing the kernel.
- In this video, we cut those ties for real. I moved our old custom bootloader into the aptly named \'bootloader.asm\'.
- The new boot.asm will be compliant with the Multiboot Specification. The Multiboot specification is an open standard describing how a boot loader can load an x86 operating system kernel. By using this specification, we can use something like GRUB (grand unified bootloader) to load our kernel, just like any other Linux kernel!
- Luckily, qemu has support for multiboot as well, which means that we don\'t have to write any kind of bootloader - we can just pass it our new compiled kernel using the -kernel option, and it will know what to do with it.
- Let\'s take a look at what we\'ll be building today.
- As you can see here, we\'ve filled the screen with X\'s and wrote OS9 in the top left. Let\'s peek at the C code that goes with it.
- Beautiful! We actually have a for loop! There\'s really no difference here from our last video, just a bit fancier.
- The other new component is a multiboot-compliant boot.asm that calls our kernel\'s main method. Let\'s take a look.
- I copied this pretty much exactly from a Linux Journal article by Petros Koutoupis - the link is in the description and it\'s a great read, definitely check it out. As you can see, we get to start out in 32 bit mode - quite a luxury! Since we\'re using ELF format for this, we also have sections now. The multiboot section has a magic number, flags of which we set none, and a checksum. Then we have the text section containing our code. All we do is declare that we\'ll be referencing main (extern main). Then at the start label, we disable interrupts, set up the stack pointer, and call our kernel. When it returns from the kernel, we use the HLT command to stop the CPU.
- This is all great stuff, but it doesn\'t mean much if we can\'t compile it. Let\'s look at the Makefile to see how it\'s done.
- When assembling boot.asm, notice that we\'re now using ELF format rather than BIN, or binary. This is huge, because it allows us to call external functions rather than jumping to a memory location to enter our C code.
- Last, rather than separately linking the boot file and the kernel file and ramming them together with the \`cat\` command, we use a linker script. We pass the script to ld, which resolves all of the memory locations in ELF metadata and creates the final kernel file that we can actually run.
- What\'s in the linker file? This is another thing that matches the LinuxJournal article exactly - thanks Petros! This is my first time writing out a linker script, but my interpretation of this is that we\'re defining our output format as 32-bit ELF, we tell it that the .start label we saw in boot.asm is our etnry point, and then we tell it how much space to give to each section of memory. I\'ll have to look into linker scripts more down the line, because that\'s the best I can do!
- With all of these things in place, we\'re free to continue writing our kernel - and maybe add some actual functionality - without worrying about the finer details of messing with the BIOS and loading our kernel from the disk into memory. It was a great learning experience, but I certainly won\'t miss it!!
- If you\'re up to it, you may want to poke around in kernel.c. Change some stuff around, print some cool messages, and maybe event write a screen driver - more on that a few videos down the line ;)
- Thanks for watching - hope you enjoyed OS9.
- **Sources**
- <https://www.linuxjournal.com/content/what-does-it-take-make-kernel-0>

## VIDEO DESCRIPTION
In this video, we break up with our old bootloader :( Don\'t worry, life without it is much better!

Notes for this video (and all others) are on the wiki:
<https://github.com/stephengrice/pkos/wiki>
Latest source can be found at the main repo:
<https://github.com/stephengrice/pkos>

Special thanks to Petros Koutoupis for his awesome Linux Journal article. Please check it out at this link - it\'s a great read!
<https://www.linuxjournal.com/content/what-does-it-take-make-kernel-0>

----------------------

Follow PageKey Solutions on Instagram: @pagekeysolutions
Data Structures & Algorithms Series: <https://www.youtube.com/watch?v=zHi5v78W1f0&list=PL3Kz_hCNpKSQbpQQjSDoQ68K75gjSFaDq>
OS Tutorial Series: <https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW>
Done in 90 Seconds Series: <https://www.youtube.com/watch?v=Jl_C_sy02MA&list=PL3Kz_hCNpKSRBep--agob7KJT4-gC6CFR>
