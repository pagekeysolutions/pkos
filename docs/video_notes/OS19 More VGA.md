# OS19: More VGA

title:
OS19: More VGA + stdlib/memory improvements

- Only waste multiple lifetimes if you want hi res! Low res VGA is not too hard  
- VGA resources osdev  
	- [http://www.osdever.net/FreeVGA/vga/vga.htm](http://www.osdever.net/FreeVGA/vga/vga.htm)  
- Can fix up the cursor:  
	- [http://www.osdever.net/FreeVGA/vga/textcur.htm](http://www.osdever.net/FreeVGA/vga/textcur.htm)  
- Absolutely need a better way of analyzing memory - VGA and regular mem
- Installed ghex for exploring `dump-guest-memory`
	- In qemu: 
		- `dump-guest-memory mem.bin`
		- `ghex mem.bin`, CTL-F for stuff
- https://qemu.readthedocs.io/en/latest/system/monitor.html
	- `info ramblock`
		- Has a vga ramblock etc
	- `memsave addr size file`
	- `pmemsave addr size file`
	- `info mtree`
- https://qemu.readthedocs.io/en/latest/devel/memory.html
	- QEMU models:
		- Regular RAM
		- Memory-mapped IO (MMIO)
		- Rerouting physical memory
- Acyclic graph of MemoryRegion objects
- Types of regions
	- RAM
	- MMIO
	- ROM
	- ROM device
	- IOMMU
	- container (of other memory regions, for grouping)
	- alias
	- reservation
- https://www.qemu.org/2018/02/09/understanding-qemu-devices/
	- Understanding QEMU Devices
	- "Most bare-metal machines are basically giant memory maps, where software poking at a particular address will have a particular side effect"
	- x86 has two memory spaces - main and I/O
	- Relevant to future video:
		- "how to manage an IDE disk - the driver is merely software that is programmed to make specific I/O requests to a specific subset of the memory map (wherever the IDE bus lives, which is specific to the hardware board)."
		- More on this in [[OSxx Hard Drive Interface]]
- http://www.osdever.net/FreeVGA/vga/vgamem.htm
	- Accessing VGA memory
	- RAM Enable: Do we listen to the CPU?
	- Memory Map Select: Where do we read from?
	- 00 -- A0000h-BFFFFh -- 128K
		- `pmemsave 0xa0000 128000 00.bin`
	- 01 -- A0000h-AFFFFh -- 64K
		- `pmemsave 0xa0000 64000 01.bin`
	- 10 -- B0000h-B7FFFh -- 32K
		- `pmemsave 0xa0000 32000 10.bin`
	- 11 -- B8000h-BFFFFh -- 32K
		- `pmemsave 0xa0000 32000 11.bin`
- https://www.kraxel.org/blog/2019/09/display-devices-in-qemu/
	- Display Devices in QEMU
- https://blog.reds.ch/?p=1379
	- Accessing the RAM of a QEMU Emulated System from another Process
	- Can map qemu to /dev/shm file
- How do we check RAM enable, Memory Map Select fields on VGA?
- Which parts of memory can we save stuff in without breaking everything?
- https://wiki.osdev.org/Memory_Map_(x86)
	- Memory Map (x86)
	- "The region of RAM above 1 MiB is not standardized, well-defined, or contiguous."
	- I guess that means we just go for it??
	- 0x00100000-0x00EFFFFF: RAM - free for use if it exists
- `info mtree` seems to have various named regions (a DAG)
```
(qemu) info mtree
address-space: memory
  0000000000000000-ffffffffffffffff (prio 0, i/o): system
    0000000000000000-0000000007ffffff (prio 0, i/o): alias ram-below-4g @pc.ram 0000000000000000-0000000007ffffff
```
- Trying to access fields
- http://www.osdever.net/FreeVGA/vga/graphreg.htm#06
	- Graphics Address Register, Graphics Data Register
	- Address reg: 0x3CE
	- Data reg: 0x3CF
	- Misc graphics reg: Index 0x06
- http://www.osdever.net/FreeVGA/vga/vgareg.htm
	- Accessing Graphics Registers: each have two unique read/write ports
		- First: Address Register. Second: Data Register
		- Best to save/restore address register (in case you're in an ISR)
		- Steps
			- 1. Input the value of address register, save it (inb)
			- 2. Output index of desired data reg to addr reg
			- 3. Read value of data reg, save if needed
			- 4-5 only apply if writing
			- 6. Restore addr reg value
	- Accessing external registers
		- Simpler - just read/write to their ports
- So for us that looks like:
	- RAM Enable - External Register / General Register
		- Read port 0x3CC
	- Memory Map Select - Graphics Register
		- Read port 0x3CE, save this value
		- Write 0x06 to 0x3CE
		- Read 0x3CF - this is misc graphics reg value
		- Write 0x3CE with original value
- Okay - RAM Enable is 1, Memory Select is 11, which is 0xB8000 - MAKES SENSE!
- http://www.osdever.net/FreeVGA/vga/seqreg.htm
	- Can select various character sets
- https://wiki.osdev.org/VGA_Hardware#The_Sequencer
	- "The Sequencer either operates in text (alphanumeric) mode or graphics mode"
- https://www.ardent-tool.com/video/VGA_Video_Modes.html
> There are five tasks you must perform to coordinate the different components of the VGA subsystem:
> - Program the CRTC.
> - Program the sequencer.
> - Select a dot-clock frequency.
> - Specify the displayed character height.
> - Update relevant ROM BIOS variables.
-  Control components
	- CRT controller (CRTC)
	- Sequencer
	- Attribute controller
	- Graphics controller
- Create your own video modes!
- Video mode characteristics
	- Vertical resolution: rows of pixels (scan lines) on screen
	- Horizontal resolution: number of characters or pixels per row
	- Data representation in buffer
	- Attribute decoding: colors, blinking, etc.
- Horizontal/vertical resolution is flexible; data rep/attributes are constrained by hardware
- Resolution is a matter of timing
	- VGA output signal timing controls electron beam in video monitor
- Character clock = unit of time. Corresponds to 8 pixels in graphics mode, 8 or 9 in alphanumeric mode
- Three rates to consider
	- Dot rate: rate at which video subsystem displays pixels. Established by dot clock
	- Horizontal scan rate: number of scan lines displayed per second
	- Vertical scan rate: refresh rate. Number of times per second screen refreshes
- Bits 0 through 4 of CRTC register 0x09 control displayed height of alphanum chars
- http://www.osdever.net/FreeVGA/vga/vgaseq.htm
	- "When the Alphanumeric Mode Disable field is set to 1, the sequencer operates in graphics mode where data in memory references pixel values, as opposed to the character map based operation used for alphanumeric mode."
- https://files.osdev.org/mirrors/geezer/osd/graphics/modes.c
	- (copied code for writing regs, etc)
- https://forum.osdev.org/viewtopic.php?f=1&t=10910
	- Discussion about how to implement memcpy
- https://sites.google.com/site/microprocessorsbits/string-instructions/rep
	- Explanation of REP assembly
- https://docs.oracle.com/cd/E19620-01/805-4693/instructionset-64/index.html
	- Explanation of variations of REP
	- rep movsb: Copy byte from esi to edi
	- repz stosl: copy eax to edl
- https://medium.com/@ophirharpaz/a-summary-of-x86-string-instructions-87566a28c20c
	- Has a nice cheat sheet of x86 string instructions
	- rep
		- `movsb`: move byte from `*ESI` to `*EDI`
		- `lodsb`: load a byte from `*ESI` to `EAX`
		- stosb: store a byte from EAX into \*EDI
- https://members.tripod.com/vitaly_filatov/ng/asm/asm_000.115.html
	- stosb: copy al to di