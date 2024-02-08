# OS15: VGA

started:: 2022-04-11
uploaded:: 2022-05-10
published:: 2022-05-10

## To Do
- [x] Finish coding
	- [x] Draw something nice
- [x] Try to switch out of text mode
- [x] Complete writeup
- [x] Create slides
- [x] Record real-life intro with green screen
- [x] Find fake BG that is cool
- [x] Edit intro
- [x] Restore old version of slides from OneDrive
- [x] Record slides voiceover
	- [x] Record lecture take 1
	- [x] Record lecture take 2
	- [x] Record lecture take 3
	- [x] Record lecture with nice audio
- [x] Record demos
	- [x] Scrolling through writeup https://pagekeytech.com/projects/pkos/15
	- [x] QEMU Demo of VGA test
	- [x] Real hardware demo of VGA test
	- [x] Code walkthrough
- [x] Edit
- [x] Rewatch and touch-up Lecture.mlt
- [x] Watch entire thing
- [x] Export
- [x] Publish blog article
- [x] Post

## Notes
Title idea
- OS15: Writing a Simple VGA Driver (Graphics)
- OS15: Plotting a Pixel with Bare Metal VGA (Simplest Possible Driver)
Thumbnail idea:
- My hand with a floating VGA card above it. Card is glowing. Bg=?

Video order:
- Run the OS
- Go through 
	- notes, 
	- lessons learned, 
	- code
- Do a test on real hardware

- Summary
	- Figured out how to init VGA mode using sample code
	- Cleared the screen (had wrong VGA mem addr at first)
		- Show what it looked like
	- Once able to clear the screen, also plotted a pixel!
	- Then started drawing a few things - some faces, and a color palette
	- Tried to switch out of text mode - did not work well
		- Branch: vga-text-mode
	- Also: Added ability to easily debug with docker_run_debug script
		- Learned about C global variables in headers (and why it's not so good) - https://stackoverflow.com/questions/8201944/multiple-definition-and-header-only-libraries

### Writeup
Our OS just got a lot more colorful. In this post, we figure out how to draw on the screen by switching to VGA mode and manually editing the video memory.

Thanks to Scott Spitler for suggesting this topic.

(timestamps)

(steps to repro)
clone, docker compose up

Background

VGA stands for Video Graphics Array [^1]. Designed for use with CRT monitors, this old-fashioned video display chipset doesn't support digital monitors. It has been replaced by DVI, or Digital Video Interface [^2]. As it turns out, the HDMI standard is just DVI with better color support and audio bundled into the same (smaller) connector [^3].

QEMU Hardware

I thought it may be helpful to look into what hardware is being simulated in our beloved i386 QEMU emulator. Thankfully, the man page for `qemu-system-i386` tells us exactly what to expect. For VGA, emulator uses the "Cirrus CLGD 5446 PCI VGA card or dummy VGA card with Bochs VESA extensions" [^4].  This card connects via the PCI bus [^5].  It seems to be old enough that it's hard to purchase anywhere. I am wondering how modern computers, like the laptop I've tried this OS out on in ==LINK TO OTHER VIDEO==, support VGA mode for x86. I can't seem to find any sources on it, but I thought that I read somewhere (maybe on the OSDev Wiki) that the external VGA chipsets were replaced with a smaller version included directly on the motherboard.

VGA Hardware

As always, the OS Dev Wiki has our back on this topic. Their page on VGA hardware greets me with an encouraging quote:

> While the VGA chip is quite a simple piece of hardware ... it is possibly one of the most complicated devices to program for

Wonderful! However, it goes on to mention that there are many shortcuts you can take to make it easier, and it's still a good place to get your start developing video drivers [^6]. With this in mind, I found some code in the public domain that I was able to make heavy use of to get *something* working, even if that something isn't the most elegant graphics code ever written. The OS Dev post [^6] goes into great depth about which ports are used to control VGA. It seems that a combination of I/O ports are used to program the chipset into the right mode, and then you can use memory-mapped I/O once everything is set up. The code that I "borrowed" took care of the hard part of writing very specific values to VGA I/O ports, and then I was able to quite simply modify the right memory locations to draw on the screen.

One other tidbit that I learned from [^6] is that VGA uses a "sequencer," among other devices in its rendering pipeline (if you could call it that). The sequencer is connected to the VGA memory space, reading it and generating colors that are fed to subsequent stages. Also, it's worth noting that there are 4 planes of VGA memory, each 64 KB in size, for a total of 256 KB.

Settings the Graphics Mode (without the BIOS)

How do you set the graphics mode in protected mode? The sage answer comes again from OSDev [^7]:

> **You don't**. Graphics programming is fun, but graphics are hardly essential for an OS. **Don't get side-tracked**

In fact, it's recommended that you avoid getting too deep into this topic unless you have "more than one life to waste" [^8]. Apparently, you can make VGA work without the BIOS and still get some low-resolution graphics working, but to move beyond it, you'll hit some serious barriers. Graphics cards would **each, separately** require their own graphics driver implementation, and there often isn't sufficient documentation on these cards [^8], meaning that you'd be reverse engineering it. That being said, at some point *far* down the line, I'm sure there's a way to obtain implementations of graphics drivers for popular cards and compile them specifically for our OS. But this is all besides the point - let's jump into the actual code of writing the VGA driver.

Writing the Code

The code that helped me get this working was found at [^9]. It's an actual example of techniques for changing the graphics mode without the BIOS. The file itself is huge, and I made no effort to build or run it. Instead, I searched for relevant code snippets that I could use in PKOS. I found `write_regs` to be a key function. This, paired with a character array named `g_320x200x256`, representing register values required to enter 320x200 VGA resolution with a color-depth of 256, allowed me to change the graphics mode. I added a command to `kernel.c` so that whenever you type `vga`, it runs the `vga_test()` function in `vga.c`, which in turn runs `write_regs(g_320x200x256)`. When we do this, our text-based interface goes away, and we see something cool!

![[Pasted image 20220502064653.png|700]]
Caption: Our first glimpse of VGA mode

Beautiful! The coolest part of this is that we seem to be unintentionally visualizing a section of memory as VGA. The little dots of yellow and stripes of gray must have had some other meaning to the computer before we entered this mode, though I'm not sure what. Maybe the buffer for our text interface that just disappeared is represented here.

Our next step is to figure out how to clear the screen. Again, I borrow some code from [^9], modifying it to compile with our OS. Specifically, I got rid of the `far` keyword - I wasn't sure what this was, and neither was our compiler! This gave us the following function to plot a pixel:

```c
void vga_plot_pixel(int x, int y, unsigned short color) {
	unsigned short offset = x + 320 * y;
	unsigned char *VGA = (unsigned char*) VGA_ADDRESS;
	VGA[offset] = color;
}
```

We simply calculate the address of the color we'd like to update based on `x` and `y`, and then change it in memory! I originally had the wrong address for `VGA_ADDRESS`, and so this code didn't seem to do anything. The correct value is `0xA0000`.

We're now free to clear the screen by plotting color 0 (black) on every pixel from 0,0 to 320,200. From that point on, we can have some fun with our `vga_plot_pixel` function. We're basically free to draw whatever we want! As for me, I drew some happy faces, a rectangle, and a pallete of colors `0x0` through `0xF`.

![[Pasted image 20220502065528.png|700]]

While we apparently have 256 colors available in this mode, I did not explore past color `0xF`.

We're Stuck in VGA Mode

Unfortunately, I was not able to find a way out of this mode. I left my various unsuccessful attempts on the `vga-text-mode` branch in the repo. Though [^9] provides `g_80x25_text` register values, writing this with `write_regs` when the user hits ESC was not enough. The actual code also writes 4096-byte font into a specific place in *virtual* memory. Unfortunately, this makes use of external dependencies to calculate, and I wasn't able to get it to work. Depending on your compiler, this would either be a `memcpy`, include some variables from `dos.h`, or something like that. Since we're running on bare-metal, we don't have `dos.h` and we'd have to roll our own `memcpy`. I took a quick-and-dirty attempt at `memcpy`:

```c
// Famous last words - how hard can memcpy be
void memcpy(void *dest, const void* src, int n) {
	for (int i = 0; i < n; i++) {
		*(int*)dest = ((int*)src)[i];
	}
}
```

Sadly, this didn't seem to help, so I gave up on it for now. The only way out of this mode is a reboot!

Other Lessons Learned

I was having trouble getting into the debugger, so I added a script for debugging named `scripts/docker_run_debug` which allows easy access to the existing debugging functionality with QEMU and GDB. It was poking around in memory and checking values that made me realize I had the wrong VGA address.

I also found out about how global variables work in C. Apparently, you should declare the global as `extern` in your header file, and then actually give it a value in your implementation file. Otherwise, you'll get yelled at for having multiple definitions of the same variable, even if you use header guards [^10].

Speaking of which, I added header guards! Without these lovely `#ifndef __HEADER_H`,  `#define __HEADER_H`, `#endif` combos, you'll get all sorts of errors for mutliple definitions of the same variable or function.

References
[^1]: https://www.britannica.com/technology/VGA
[^2]: https://computer.howstuffworks.com/monitor3.htm
[^3]: https://www.toptenreviews.com/how-hdmi-cables-work
[^4]: https://manpages.debian.org/stretch/qemu-system-x86/qemu-system-i386.1.en.html
[^5]: http://www.vgamuseum.info/index.php/cpu/item/147-cirrus-logic-cl-gd5446
[^6]: https://wiki.osdev.org/VGA_Hardware
[^7]: https://files.osdev.org/mirrors/geezer/osd/graphics/index.htm
[^8]: https://wiki.osdev.org/How_do_I_set_a_graphics_mode
[^9]: https://files.osdev.org/mirrors/geezer/osd/graphics/modes.c 
[^10]: https://stackoverflow.com/questions/8201944/multiple-definition-and-header-only-libraries

### Research
- https://www.britannica.com/technology/VGA
	- Video Graphics Array
- https://computer.howstuffworks.com/monitor3.htm
	- VGA is analog (for CRT?) - doesn't support digital monitors
	- DVI is digital
- https://www.toptenreviews.com/how-hdmi-cables-work#:~:text=HDMI%20cables%20use%20the%20same,all%20in%20a%20smaller%20connector.
	- HDMI is just DVI with audio and more color space in a smaller connector

- Scott: an interesting thing to interleave in there would be device drivers/graphics. 
	- Scott: The Linux graphics layer is a bit strange to read upon so maybe some highly primitive buffer drawing (maybe a rectangle) would be cool? 
• Qemu peripherals: [https://manpages.debian.org/stretch/qemu-system-x86/qemu-system-i386.1.en.html](https://manpages.debian.org/stretch/qemu-system-x86/qemu-system-i386.1.en.html)  
	• Cirrus CLGD 5446 PCI VGA card or dummy VGA card with Bochs VESA extensions (hardware level, including all non standard modes).  
• Per [http://www.vgamuseum.info/index.php/cpu/item/147-cirrus-logic-cl-gd5446](http://www.vgamuseum.info/index.php/cpu/item/147-cirrus-logic-cl-gd5446)  
	• it's a PCI peripheral  
• How to iterate PCI devices? 
- https://wiki.osdev.org/VGA_Hardware
	- "While... simple piece of hardware... possibly one of the more complicated devices to program for" GREAT
	- Steps: Calculate register values, write to VGA, draw
	- Uses: 
		- Port I/O: 8 bit read-writes, 16-bit writes
		- MMIO: 0xA0000-0xBFFFF
		- Read/Write VGA Registers (more regs than ports), 
		- structure containing VGA display settings, 
		- function that writes struct to device, 
		- function that fills the struct (or hardcoded struct)
	- Cannot remap VGA addresses (PCI) so can only control 1 VGA card at a time
	- Ports:
		- 0x3C0: write index and data bytes. 
			- Read from 0x3DA so that INDEX is expected. 
			- Can feed index into 0x3C0 then read from 0x3C1 to get the value
		- 0x3C2: Misc output register. 
			- 0x3C2 for write, 
			- 0x3CC for read. 
			- Bit 0 controls loc of other regs. 
				- If 0, 0x3D4->0x3B4, and 0x3Da->0x3Ba
		- 0x3C4, 0x3CE, 0x3D4: Most-used index registers. 
			- Write index to port, read data from port+1. 
			- Can use 16-bit access instead of 2 8-bit writes 
				- (but watch byte ordering)
			- 0x3D4: Extra reqts. 
				- Bit0 of Misc Output Reg 0x3C2 must be SET 
					- (otherwise, these ports appear at 0x3B4). 
				- Also, reg 0-7 of 0x3D4 are write protected by protect bit (bit 7 of index 0x11)
		- 0x3C6: Contains DAC Mask Register. 
			- Simple read/write to this port. 
			- Normal condtions, should contain 0xff
		- 0x3C8: 0x3C8, 0x3C9, 0x3C7 control the DAC. 
			- Each DAC register is 18-bits
				- 6 bits for each color component R, G, B. 
			- To write a color, 
				- write color index to 0x3C8, 
				- then 3 bytes to 0x3C9 in order R, G, B. 
			- To write multiple entires, only write index to 0x3C8 then all values to 0x3C9. 
			- To read, write index to 0x3C7, then read from 0x3C9 
				- (similar auto-increment of index applies here)
	- Video Memory Layout
		- Has four "planes" or units fo memory, each 64KB. VGA has 64\*4=256K total
		- Sequencer: Connected to VGA memory, interprets to gen colors that are fed to subsequent stages
		- Color organization in memory depends on color depth
		- Accessing the mmeory from the host -> See Graphics Controller
		- How video memory is rendered -> See Sequencer

https://forums.raspberrypi.com/viewtopic.php?t=190649
- Do a handshake with GPU to get access to a framebuffer, then directly poke pixel bytes in

https://wiki.osdev.org/How_do_I_set_a_graphics_mode
- Without BIOS or UEFI, can develop/reuse VGA driver for **LOW RESOLUTION** graphics
- For hi-res, **EACH** graphics card needs its own implementation
	- Only if you "have more than one life to waste"
	- Many graphics cards to not have official documentation

https://wiki.osdev.org/VGA_Resources

http://web.archive.org/web/20140218012818/http://atschool.eduweb.co.uk/camdean/pupils/amac/vga.htm
- VGA = Video Graphics Array
- 256-color mode is mode 13h
- Use BIOS call to set mode 13h <-- need a way to do without BIOS
	- Once in that mode, can directly edit memory instead - much faster
- "As mentioned before, the memory needed for mode 13h is 64,000 bytes. This memory is located at segment A000h in the computer's memory. Simply writing to that area in memory will also write to the screen. The color displayed depends on the byte written to memory."

https://files.osdev.org/mirrors/geezer/osd/graphics/index.htm
- 'How do I enable graphics from protected mode?'
	- "1.  **You don't**. Graphics programming is fun, but graphics are hardly essential for an OS. **Don't get side-tracked**."
- https://files.osdev.org/mirrors/geezer/osd/graphics/modes.c <- Set mode without BIOS
	- HUGE! This is all that made this lesson work. ==Main Source==

-----

More only tangentially related notes that I looked up for fun:

- https://wiki.osdev.org/Drawing_In_a_Linear_Framebuffer#Graphics_Modes
- Qemu dump memory
- https://stackoverflow.com/questions/45397607/how-to-tell-to-qemu-to-copy-the-ram-into-a-file#:~:text=You%20can%20do%20this%20by,control%2Dalt%2D2).
- Eventually needed for hard drive:
- https://wiki.osdev.org/PCI_IDE_Controller
- PCI ide controller on qemu
- Cool very basic way of writing code on the OS:
- https://youtu.be/nfVJ_lcrxh0
- Simple filesystem fat12
- https://youtu.be/WW7ZoGhMikY
- You can make an OS in PPT
- https://youtu.be/YVheW_huGLk
- https://youtu.be/L6A7IY3Qg8Q
- https://wiki.osdev.org/I/O_Ports


## OS, VGA notes
- Write raw machine code without assembly
	- <https://stackoverflow.com/questions/51032301/how-can-i-write-raw-machine-code-for-x86-without-using-assembly>
- Writing a VGA driver
	- <https://stackoverflow.com/questions/9585662/vga-driver-reference>
- Opcode table
	- <http://sparksandflames.com/files/x86InstructionChart.html>
- COVER THE STACK
	- <https://stackoverflow.com/questions/18660148/differences-between-push-eax-and-mov-esp-eax>
- <https://files.osdev.org/mirrors/geezer/os/pm.htm>
	- Don\'t worry about returning to real mode. Use the reset button :)
	- Leave interrupts disabled.
	- Don\'t use an LDT.
	- Put only four descriptors in the GDT: null, code, stack/data, and linear data (base address = 0).
	- Set the segment bases to real-mode values i.e. 16 \* real-mode segment register value. This lets you address variables in the same way in both real and protected modes.
	- Set all segment limits to their maximum.
	- Leave all privilege values set to 0 (Ring 0, highest privilege).
	- Before each step of switching to pmode, poke a character into video memory, to see (literally!) how far the code gets. Text-mode VGA memory starts at address 0B8000h.
	- How do I enter protected mode?
		- Entering protected mode is actually rather simple, and is is described in many other tutorials. You must:
		- Create a valid Global Descriptor Table (GDT), and create the 6-byte \'pseudo descriptor\' pointing to the GDT
		- Disable interrupts
		- LGDT. The operand of this instruction points to the GDT pseudo-descriptor, which in turn points to the GDT
		- Set the PE bit in the MSW register
		- Load all data segment registers with valid selectors
		- Do a far jump (load both CS and IP/EIP) to load CS and enter pmode
- <https://stackoverflow.com/questions/12853948/moving-data-from-register-into-memory-in-nasm>
	- As for moving a into memory, there are a few syntactical ways:
	- MOV \<var name>,\<value>
	- MOV \[\<var name>\],\<value>
	- Text-mode VGA memory starts at address 0B8000h.
- <https://wiki.osdev.org/Memory_Map_(x86)>
- <http://staff.ustc.edu.cn/~xyfeng/research/cos/resources/machine/mem.htm>
	- Memory map - what is what
- <https://stackoverflow.com/questions/40381594/printing-characters-to-screen-asm-in-protected-mode>
	- Print without bios
- <https://arjunsreedharan.org/post/99370248137/kernels-201-lets-write-a-kernel-with-keyboard>
	- Read from keyboard protected mode
- <https://stackoverflow.com/questions/53908872/read-the-keyboard-in-protected-mode>
- <https://wiki.osdev.org/%228042%22_PS/2_Controller#Initialising_the_PS.2F2_Controller>
	- Keyboard read - actually write x86 PS/2 driver
	- Qemu read disk
	- Qemu-system-i386 -fda boot.bin
