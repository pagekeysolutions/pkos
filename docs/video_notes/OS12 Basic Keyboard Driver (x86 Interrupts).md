# OS12: Interrupts
Saturday, June 27, 2020
7:33 PM
 
> [interrupt instructions of 8086](https://www.youtube.com/watch?v=KkMEpwDHRO4)
-   Interrupt - stop execution of CPU for a short time
-   Microprocessor responds to interrupt signal using ISR - Interrupt Service Routine
    -   This is a short program to indicate how to handle the interrupt
-   Keyboard, mouse produce interrupts
-   Types of Interrupt
    -   HW interrupts
        -   Maskable - You can mask the interrupt (?) and continue main program
        -   Non-maskable - you must stop and handle it (?)
        -   Other types (?)
            -   NMT
            -   INTR
            -   INTA
    -   SW interrupts
        -   256 types
        -   Can be inserted to test hardware interrupts (?)
        -   Types
            -   INT - interrupt instruction with type \#
            -   INT3 - Breakpoint of interrupt instruction
>
> ![[17_OS12 Interrupts_image001.png]]
>
> <https://en.wikipedia.org/wiki/Interrupt_descriptor_table#Protected_mode>
-   IDTR register: special register to hold base address and length of Interrupt Descriptor Table (IDT)
-   Entries (vectors) can be Interrupt Gates, Trap Gates, or (32-bit protected only) Task Gates
    -   Interrupt Gate: Point to executable code (segment/offset). Disable handling further HW interrupts.
    -   Trap Gate: Point to executable code (segment/offset). Do not disable handling further HW interrupts.
        -   Mainly for SW interrupts and exceptions
    -   Task Gate: Switch current task-state segment
        -   Use HW mechanism to hand over process to another program/thread/process
-   Vectors 0-31 are reserved for Intel processor exceptions
>  
>
> <https://www.qemu.org/docs/master/system/monitor.html>
>
> QEMU DEBUGGING
-   Add to command launching qemu: \`-monitor stdio\`
    -   Use \"info registers\" to see em all
    -   You can all do print \$eax and so forth
    -   x/10hx 0xb8000: print 10 bytes of video memory starting at 0xb8000
    -   x/10i 0xb8000: print 10 instructions at 0xb8000
>  
>
> running QEMU with the additional options -d int -no-reboot -no-shutdown may help you track down the issue. -d int will display interrupts and exception that occur and -no-reboot -no-shutdown prevents QEMU from rebooting or shutting down.
>
>  
>
> *From \<<https://stackoverflow.com/questions/54027271/how-do-i-catch-the-cause-of-my-x86-cpu-reset>\>*
>
>  
>
>  
>
> <http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html#:~:text=The%20GDT%20and%20the%20IDT,it'll%20be%20over%20soon!>
-   GDT vs IDT (theory and practical)
>  
> <https://c9x.me/x86/html/file_module_x86_id_139.html>
-   IN command for x86 processor
-   Copies value from IO port to destination
-   This instruction is only useful for accessing I/O ports located in the processor\'s I/O address space
>  
>
> <https://c9x.me/x86/html/file_module_x86_id_222.html>
-   OUT command for x86 processor
>  
> <https://wiki.osdev.org/I/O_Ports>
-   Many architectures: ONLY use memory mapped IO to communicate with hardware
>  
> <https://arjunsreedharan.org/post/99370248137/kernels-201-lets-write-a-kernel-with-keyboard>
-   Code on <https://github.com/arjun024/mkeykernel>
>  
>
> <https://stackoverflow.com/questions/3215878/what-are-in-out-instructions-in-x86-used-for>
>
> Explanation of what IN and OUT instructions do
>
> For some CPU models including the xxx86 series as found in most \"modern\" PCs, I/O devices share the address space with memory. Both RAM/ROM and IO devices are connected to the same address, data and control lines.
>
>  
>
> NOTE. controlling the PS2 chip is like controlling the old old old PS2 jacked keyboards and mouse. See this <https://www.google.com/url?sa=t&source=web&rct=j&url=https://www.amazon.com/Sanoxy-Keyboard-Converter-Adapter-Splitter-built/dp/B075X3HHFQ&ved=2ahUKEwisrY35kKrqAhXtdN8KHYBrBRoQFjAAegQIBhAB&usg=AOvVaw3yyTQB4aq1Vlt4dvjS2CpE>
>
>  
>
> Does this also apply to built in keyboard and mouse on laptop?? Will likely need a USB driver soon
>
>  
>
>  
>
> <https://www.felixcloutier.com/x86/iret:iretd>
>
>  
>
> We are programming the PIC: more info <https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller>
-   This is where the mkeykernel code comes from
> <https://wiki.osdev.org/8259_PIC>
-   Excellent def of x86 PIC, which is 8259, either real (very old arch) or emulated in newer CPUs
>  
>
> <https://wiki.osdev.org/Interrupts>
>
>  
>
> Really good article for exactly this:
>
> <https://alex.dzyoba.com/blog/os-interrupts/>
>
>  
>
>  
>
>  
>
> When you enter protected mode (or even before hand, if you\'re not using [GRUB](https://wiki.osdev.org/GRUB)) the first command you will need to give the two PICs is the initialise command (code 0x11). This command makes the PIC wait for 3 extra \"initialisation words\" on the data port. These bytes give the PIC:
-   Its vector offset. (ICW2)
-   Tell it how it is wired to master/slaves. (ICW3)
-   Gives additional information about the environment. (ICW4)
>  
>
> *From \<<https://wiki.osdev.org/PIC#Initialisation>\>*
>
>  
>
> ![[17_OS12 Interrupts_image002.png]]
>
>  
>
>  
>
> Figuring out what\'s going on for IDT intialization
>
> *\"The **initial vector offset of PIC1 is 8, so it raises interrupt numbers 8 to 15**. Unfortunately, s**ome of the low 32 interrupts are used by the CPU for exceptions** (divide-by-zero, page fault, etc.), **causing a conflict** between hardware and software interrupts. The **usual solution** to this is **remapping** the **PIC1** to start at **32**, and often the **PIC2** right after it **at 40**. This requires a complete restart of the PICs, but is not actually too difficult, requiring just eight outs\"*
>
> mov al, 0x11\
> out 0x20, al *;restart PIC1*\
> out 0xA0, al *;restart PIC2*
-   *0x11 is referred to the initialization command in some places. I think it\'s actually the reset command*
-   ***This is ICW1***
> mov al, 0x20\
> out 0x21, al *;PIC1 now starts at 32*
-   0x20 is 32 in base 10
-   **This is ICW2: Vector Offset**
-   I think this means that IRQ0 is at 0x20
-   IRQ0 to 7
-   IRQ7=0x27
> mov al, 0x28\
> out 0xA1, al *;PIC2 now starts at 40*
-   *0x28 = 40 in base 10*
-   *This means that IRQ8-15 will start at 40*
-   *IRQ8 = 0x28, IRQ9 = 0x29, etc.*
> mov al, 0x04\
> out 0x21, al *;setup cascading*
-   ***This is ICW3***
-   *\"*Tell it how it is wired to master/slaves\"
-   \"*tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)\"* From \<<https://wiki.osdev.org/8259_PIC>\>
> mov al, 0x02\
> out 0xA1, al
-   *\"ICW3: tell Slave PIC its cascade identity (0000 0010)\"* From \<<https://wiki.osdev.org/8259_PIC>\>
> mov al, 0x01\
> out 0x21, al
>
> out 0xA1, al *;done!*
-   \"Gives additional information about the environment. (ICW4)\" From \<<https://wiki.osdev.org/8259_PIC>\>
-   Both ports get the same value: 0x1
-   What are some other values for ICW4??
> #define ICW4_8086        0x01                /\* 8086/88 (MCS-80/85) mode \*/\
> #define ICW4_AUTO        0x02                /\* Auto (normal) EOI \*/\
> #define ICW4_BUF_SLAVE        0x08                /\* Buffered mode/slave \*/\
> #define ICW4_BUF_MASTER        0x0C                /\* Buffered mode/master \*/\
> #define ICW4_SFNM        0x10                /\* Special fully nested (not) \*/
>
>  
>
> *From \<<https://wiki.osdev.org/8259_PIC>\>*
>
>  
>
> *Assembly Snippet From \<<https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller>\>*
>
>  
>
>  
>
> Intel Manual
>
> <https://software.intel.com/content/www/us/en/develop/download/intel-64-and-ia-32-architectures-sdm-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html>
-   Chapter 10 Advanced Programmable Interrupt Controller (APIC)
    -   This is way too dense
>  
> Old intel manual archived on Csail.edu:
-   <https://pdos.csail.mit.edu/archive/6.097/readings/intelv2.pdf>
>  
>
> CSAIL hosts a PIC manual:
-   <https://pdos.csail.mit.edu/6.828/2008/readings/hardware/8259A.pdf>
>  
>
> TutorialsPoint about ICW3 and ICW4
>
> <https://www.tutorialspoint.com/programming-the-8259-with-slaves>
>
>
> \-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--
>
> Okay, we can program the PIC. Now how about this IDT thing?
>
>  
>
> <https://wiki.osdev.org/Interrupt_Descriptor_Table>
-   IDTR register holds the interrupt descriptor table
    -   Change this with the \`lidt\` instruction
    -   Structure is:
        -   Bits 0-15: Limit. Length of the IDT in bytes minus one.
        -   Bits 16-47: Base. This is the 32-bit starting address for the first IDT entry
-   IDT Entry structure
    -   These populate the IDT
    -   Offset: 32-bit address representing entry-point of ISR (interrupt service routine) that will service the interrupt. Split into two parts (upper and lower bits
    -   Fields:
        -   (16 bits) Offset_lowerbits: Bits 0-15 of the offset.
        -   (16 bits) Selector: Code segment selector; must point to a valid code sector in GDT or LDT (global/local descriptor table)
        -   (8 bits) zero: 8 unused bits that should be set to 0
        -   (8 bits) type_attr: Type and attribute bits
        -   (16 bits) offset_upperbits: Bits 16-31 of the offset
    -   Type and attribute bits
        -   Bit 0: P.
        -   Bits 1-2: DPL.
            -   Descriptor Privilege Level
            -   Called Descriptor must have at least this privilege level
            -   I believe this ties into Ring 0, Ring 1, etc.
        -   Bit 3: S. Storage segment. 0 for interrupt and trap gates
        -   Bits 4-7: Gate Type
            -   0x5: 32-bit task gate
            -   0x6: 16-bit interrupt gate
            -   0x7: 16-bit trap gate
            -   0x14: 32-bit interrupt gate
            -   0x15: 32-bit trap gate
    -   Code segment
        -   This should be set to the kernel\'s selector in our case (Ring 0). Simplest version will have only one code segment entry in GDT anyway
>  
> Breaking down the mkeykernel code:

keyboard_address = (unsigned long)keyboard_handler;
-   > We use 'extern' to grab a reference to the keyboard_handler as a FUNCTION from our ASM file
-   > This line converts that function reference to an actual number - unsigned long means it will be 32 bits for x86 32-bit
    -   > For 32-bit, unsigned long and unsigned int appear to both be 32-bits

IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
-   > Grab the lower bits of our keyboard address. AND with 0xffff to get ONLY the bottom 32 bits
-   > In other words, we are ANDing with 0x0000FFFF for the long. This is then stored as 16 bits

IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
-   > 0x8 is the first entry in the GDT following the null entry. Did a deep dive to figure this out below

IDT[0x21].zero = 0;
-   > This is just zeros!

IDT[0x21].type_attr = INTERRUPT_GATE;
-   > Interrupt gates and trap gates
-   > [https://stackoverflow.com/questions/3425085/the-difference-between-call-gate-interrupt-gate-trap-gate](https://stackoverflow.com/questions/3425085/the-difference-between-call-gate-interrupt-gate-trap-gate)
-   > Seems that interrupt gates are typically kernel-space and hardware interrupts
-   > Trap gates are typically user-space and CPU instructions (maybe SW interrupts?)

IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

-   Self explanatory, grab the upper bits of keyboard address and shift them down 16 bits to get JUST those upper bits in a 16 bit integer.

- *From \<<https://github.com/arjun024/mkeykernel/blob/master/kernel.c>\>*

>  
>
> \'CS\'\
> Must be a 32-bit read/execute code segment with an offset of \'0\'\
> and a limit of \'0xFFFFFFFF\'. The exact value is undefined.

-   Multiboot spec? says the above
>  
>
> *From \<<https://www.gnu.org/software/grub/manual/multiboot/multiboot.txt>\>*
>
>  
>
> What is the GDT by default out of grub?

-   Find out with QEMU
-   Running \'make run\' on commit d03720c from pkos repo
    -   Print registers: \"info registers\"
    -   GDT= 000caa68 00000027
        -   Let\'s figure out what this means: <https://en.wikibooks.org/wiki/X86_Assembly/Global_Descriptor_Table>
        -   Limit (size) is 16 bits or 2 bytes
        -   Base (starting address) is 32 bits or 4 bytes
        -   GDTR from QEMU appears to have 8 bytes. So there must be some padding (GDT is only 6)
        -   This leads me to:
        -   00c = ??
        -   Aa68 = Limit?
        -   00000027 = Base?
-   What about when we set this up ourselves in OS? Checking out os7 to try it. Commit 7f9bf3c
    -   Have to add -monitor stdio to qemu command in Makefile
    -   Print registers: \"info registers\"
    -   GDT= 00007c05 00000017
        -   In our code we set the following (<https://github.com/stephengrice/pkos/blob/7f9bf3c8370e5316c5f8219c73eaac53d4c474c9/src/inc/gdt.asm>)
        -   Actually, the GDT descriptor stored in GDTR was dynamically defined:

| gdt_descriptor: |                                                           |
|-----------------|-----------------------------------------------------------|
|                 | dw gdt_end - gdt_start - 1 ; Size of GDT, always less one |
|                 | dd gdt_start                                              |

> *From \<<https://github.com/stephengrice/pkos/blob/7f9bf3c8370e5316c5f8219c73eaac53d4c474c9/src/inc/gdt.asm>\>*
>
-   Dang it.
> ![[17_OS12 Interrupts_image003.png|700]]
>
> From \<<https://alex.dzyoba.com/blog/os-segmentation/>\>
>
> Somehow Alex Dzyoba figured out the legacy GRUB values. But he\'s right, it\'s silly to rely on GRUB to set these
> 
> Let\'s clench our teeth and set up our own dang code segments.
>
> We still have the original GDT in the inc folder. For now this will work.

-   Can confirm the GDT is now different as of commit xxxx
    -   GDT= 00100010 00000017
-   Per Alex\'s post, selector 0 is the null entry, 0x8 is the first entry, 0x10 the second, etc.
    -   SO we could have just used the mkeykernel constant of 0x8, but now at least we know where it came from :)
-   <https://docs.oracle.com/cd/E18752_01/html/817-6223/chp-typeopexpr-2.html>
    -   This show the number of bytes in each datatype for C
> **Why is IDT_SIZE 256?**
-   Arjun Sreedharan answers this question on his blog and cites <https://wiki.osdev.org/Interrupts>
> There are 256 interrupt vectors on x86 CPUs, numbered from 0 to 255 which act as entry points into the kernel. The number of interrupt vectors or entry points supported by a CPU differs based on the CPU architecture.
> *From \<<https://wiki.osdev.org/Interrupts>\>*
>
> The Interrupt Gate is used to specify an [interrupt service routine](https://wiki.osdev.org/Interrupt_Service_Routines). When you do [INT](https://wiki.osdev.org/INT) 50 in assembly, running in protected mode, the CPU looks up the 50th entry (located at 50 \* 8) in the IDT.
>
> *From \<<https://wiki.osdev.org/Interrupt_Descriptor_Table#I386_Interrupt_Gate>\>*
>
>
> You can set a breakpoint and then debug state at that line by just infinitely looping on that line. Then you can use si to step through
>
> ![[17_OS12 Interrupts_image004.png|700]]
>
> <https://wiki.osdev.org/Kernel_Debugging#Use_GDB_with_QEMU>
>
>
> There are two basic ways to set breakpoints in your code.
>
> The first, more common, type is a "software breakpoint". When you ask the debugger to set a breakpoint at a certain statement, it will find the first assembly instruction associated with that statement. It will then replace this instruction with a different, special instruction, that when executed will cause control to be transferred from the debugee (the program being debugged) to the debugger.
>
> The second type is a "hardware breakpoint". This requires more specialized hardware support. With hardware breakpoints, the debugger configures the CPU to transfer control to the debugger when an instruction at a certain address is executed. Note that this means we don't need to change the instruction itself, we only need to know the address.
>
> gdb's "break" command will set a breakpoint - but it doesn't commit to the type of breakpoint that will be set. "hbreak", on the other hand, will always use a hardware breakpoint. So, you really ought to always use break, unless you know you specifically need a hardware breakpoint, and also know gdb won't be able to figure this out on its own.
>
> When would you need one? For most people, the answer is probably never. But there is an exception. We just said that using a hardware breakpoint means the code doesn't have to be changed. So if for some reason the code simply can not be changed - for instance, if it resides in read-only memory - a hardware breakpoint is pretty much your only option.
>
> Note that there is a related concept called [hardware watchpoints](https://sourceware.org/gdb/onlinedocs/gdb/Set-Watchpoints.html) which is much more useful. But those are not set with hbreak. Rather, like with break - you should use the "watch" command, and gdb will decide what kind of watchpoint it will use, hardware or software.
>
>  
>
> *From \<<https://www.quora.com/What-is-the-difference-between-hbreak-and-break-command-in-gdb>\>*
>
>  
>
> <https://sourceware.org/gdb/onlinedocs/gdb/Output-Formats.html>
>
> p/x prints as hex
>
> p/u prints as unsigned int
>
>  
>
> Potentially found the solution to triple fault. Padding of IDT. See answer:
>
> <https://stackoverflow.com/questions/37618111/keyboard-irq-within-an-x86-kernel>
