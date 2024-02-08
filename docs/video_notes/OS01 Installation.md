# OS1: Installation

## Script, etc
OS1 - Installing VirtualBox & Debian on Windows
Tuesday, December 17, 2019
5:33 PM
 
-   Original idea:
-   Audience: Anyone with some programming knowledge and curiosity about low-level computing
-   Learning outcomes:
    -   Understand what a bootloader is, what it does, and where it lives in computer architecture
    -   Install all necessary software to build an i386 bootloader and emulate its execution
    -   Write and understand every line of code for your simple bootloader! Tweak it for yourself!
-   What is a bootloader? What does it do?
    -   Bootloader: a program that loads an operating system when a computer is turned on.
        -   Source: Oxford (<https://www.lexico.com/en/definition/bootloader>)
    -   Bootloader will load your operating system into memory, and pass it off.
    -   Also: Enable real/protected mode?
-   Where does the bootloader live?
-   Installing Software
    -   VirtualBox approach. See my other video
    -   Other ways:
        -   WSL -- Windows Subsystem Linux
        -   Dual Boot Linux
        -   Raspberry Pi server
        -   Take the plunge and do all your personal computing on Linux :)
-   The \"Hello World\" of bootloaders
-   Wrap-up
-   Sources:
    -   Oxford (<https://www.lexico.com/en/definition/bootloader>)

-   Actual notes:
-   Hey guys it\'s Steve. Hope you\'re having a great day today. What you probably didn\'t know when you woke up this morning or even when you clicked on this video is that we\'re going on a journey. Right now we are taking the first step on a beautiful journey, one involving careful thought, low level programming, and tons of learning. If you haven\'t guessed already we\'re taking the first steps to writing our own operating system.
-   Now I\'m not saying that I can make it through this whole journey. But what I can promise is that I\'ll take you along as I make the attempt. I\'ll share what works and what doesn\'t, and if I burn out, I\'m relying on you to pick up the pieces and carry the torch just a little bit further. I\'m no professor, so I\'m not making discoveries or expanding the field. I\'m just dipping into technology that everyone uses daily, but very few understand. Let\'s hope we make it out alive!
-   This video is all about setting up an environment for us to do our programming in. Windows is great for checking your email and writing reports, but Linux has the down and dirty tools we need to get this dirty job done, with or without Mike Rowe. I\'m sure there\'s a way to get this all to work on Windows too, but I\'m really not interested. As in, I don\'t care. If you\'re interested, you can pick up your Dot Net framework and take it somewhere else, my friend.
-   Advanced users. Feel free to roll your eyes. Feel free to skip this video. If you know enough to have an opinion on my choices, you probably also know enough to figure out how to do it your way. Which coincidentally may be better than my way
-   For everyone else, we\'re going to set up our computers with a virtual machine for developing our OS. If we all follow the exact same steps, with any luck, we will all run into the exact same problems, and so we can help each other out.
-   As no educational video is complete without some PowerPoint slides, take a gander at what I threw together.
-   Audience: People who have never used any kind of VMs
-   Learning outcomes:
    -   Understand what a VM is and how it works at a high level
    -   Know the process for installing Ubuntu on VirtualBox for Windows 10
-   What is a Virtual Machine?
    -   Virtual Machine: emulation of a computer system (Wikipedia)
-   How does VirtualBox work?
    -   X?
-   Process
    -   Download VirtualBox
    -   Download your image. Could be Ubuntu, CentOS, Arch Linux (advanced), Gentoo (also advanced), and many, many more.
        -   For this tutorial, we will use Ubuntu, which is very user friendly. It comes \"batteries included\" for many details that beginners may not know or care about.
    -   Quickly go through the VirtualBox install wizard
    -   Open VirtualBox
    -   Create Ubuntu machine
    -   Boot the machine
    -   Select the Ubuntu ISO we downloaded earlier.
        -   Using an ISO is the same as inserting a CD into the virtual computer. The ISO is \"bootable,\" meaning that it is of a format that tells any computer that reads it which code to execute on boot.
        -   Booting from the Ubuntu ISO kicks off the installer
    -   Go through the install wizard.
    -   Done! We now have a working virtual machine. Open terminal -- working Linux system
-   Wrap-Up: Review Learning outcomes
-   Coming Soon (check description): Networking types with VirtualBox


## Original Idea for Series
OS Series: A Saga
Wednesday, December 18, 2019
11:05 PM

- Tell the story of how I\'m setting out from day zero to build PKOS.
- Explain why.
- You\'re invited to come along - I\'ll show you the way, assuming I find it myself.
- Robert Frost, the road less traveled.
- Why such a thrilling topic you may ask?
- Outline of topics\... For now! My understanding may change.
- Let\'s approach with humility. Quote site as being hardest programming task. Am I a master programmer? No. But if I fail, as long as I learn something, it\'s worth it. Watch on, and I think you and I will both learn a lot.
- Expert or noob, please tune into the community on Gitter.
- I\'ll do my best to keep videos short and (relatively speaking) entertaining. Will also try to post the code so you can dive in on your own.
- Because we\'re in this together!!
- I\'ll try to tag the source branch for PKOS by each video.
- May try to stay away from PowerPoint\.... But may also be a necessary evil for explaining some concepts.
- In today\'s information age, we have access to all the knowledge. The challenge, and the journey, is to find the knowledge, absorb it, and apply it. I\'m no PhD. I won\'t be expanding the field here, but I may undercover something we both didn\'t know before and inspire you to dive in deeper. Then, maybe YOU can be the one to make the next big leap!
- I\'m Steve G, owner and operator of PageKey Solutions. I used to pretend it\'s an actual business, but let\'s be honest here - it\'s a YouTube channel and some random articles I wrote. Maybe someday it will be something more, but for now, it\'s just a catchy nombre
- It\'s so infrequent for anyone to dive so low. We are all using processors. They are everywhere. And we build abstractions on abstractions. There are apps to help you build apps and technology stacks the size of Mount Rushmore. But if you strip away all the abstractions and mountains of software, what\'s left? This is what fascinates me.
- My current view, which could change, is that you\'re left with a very fast, very fancy circuit that takes instructions as input, uses memory and cache for scratch paper, and coordinates inputs from a diverse array of devices at lightning speed, juggling hArd drives, monitors, mouse twitches, and keyboard mashes, all at thousands of times in the blink of an eye.
- Breakdown what a gigahertz is and how fast that clock is running
- I challenge each and every one of you to find something newbyou can do in my code and share it at (Gitter link). There are probably infinite ways of doing this, from hey look Steve I figured out how to change the terminal color to I just made up my own scheduling algorithm. All of it matters and you\'re going above and beyond what I\'ve done. You\'re learning and that\'s what counts. So thanks in advance for your contributions. Enough talk, let\'s get technical. Watch on.
- When series is done, ask someone not technical to go through. Where they have issues, make a sub video (2.1, 2.2) to clear it up. Continue ad infinitum
- Important! I want the viewer to feel SMART and EMPOWERED at the start and finish of the video.
- Remind them what they can do, that they\'re on a learning path, and what they will be able to do!

## More Series Ideas
OS Dev Article
Wednesday, July 8, 2020
7:32 PM

![[07_OS Dev Article_image001.jpg]]

![[07_OS Dev Article_image002.jpg]]

![[07_OS Dev Article_image003.jpg]]
 
Here\'s what we do! 8/9 idea
-   Write the article about why study OS Dev
    -   Start with question: have you ever thought about what happens when you strip away all the abstraction / what\'s really going on under the hood?
    -   Talk about things you\'ll learn. Assembly. C. How they work together. What the processor does for you and what it doesn\'t. How everything you\'ve ever used is built from the hardware up

## Google Keep OS Notes
Google Keep OS Notes
Saturday, June 27, 2020
7:20 PM

Writing a VGA driver
<https://stackoverflow.com/questions/9585662/vga-driver-reference>

Opcode table
<http://sparksandflames.com/files/x86InstructionChart.html>

COVER THE STACK
<https://stackoverflow.com/questions/18660148/differences-between-push-eax-and-mov-esp-eax>

<https://files.osdev.org/mirrors/geezer/os/pm.htm>
Don\'t worry about returning to real mode. Use the reset button :)
Leave interrupts disabled.
Don\'t use an LDT.
Put only four descriptors in the GDT: null, code, stack/data, and linear data (base address = 0).
Set the segment bases to real-mode values i.e. 16 \* real-mode segment register value. This lets you address variables in the same way in both real and protected modes.
Set all segment limits to their maximum.
Leave all privilege values set to 0 (Ring 0, highest privilege).
Before each step of switching to pmode, poke a character into video memory, to see (literally!) how far the code gets. Text-mode VGA memory starts at address 0B8000h.

How do I enter protected mode?
Entering protected mode is actually rather simple, and is is described in many other tutorials. You must:
Create a valid Global Descriptor Table (GDT), and create the 6-byte \'pseudo descriptor\' pointing to the GDT
Disable interrupts
LGDT. The operand of this instruction points to the GDT pseudo-descriptor, which in turn points to the GDT
Set the PE bit in the MSW register
Load all data segment registers with valid selectors
Do a far jump (load both CS and IP/EIP) to load CS and enter pmode
<https://stackoverflow.com/questions/12853948/moving-data-from-register-into-memory-in-nasm>

As for moving a into memory, there are a few syntactical ways:
MOV \<var name>,\<value>
MOV \[\<var name>\],\<value>
Text-mode VGA memory starts at address 0B8000h.

<https://wiki.osdev.org/Memory_Map_(x86)>

<http://staff.ustc.edu.cn/~xyfeng/research/cos/resources/machine/mem.htm>

Memory map - what is what
 
<https://stackoverflow.com/questions/40381594/printing-characters-to-screen-asm-in-protected-mode>
Print without bios

<https://arjunsreedharan.org/post/99370248137/kernels-201-lets-write-a-kernel-with-keyboard>
Read from keyboard protected mode

<https://stackoverflow.com/questions/53908872/read-the-keyboard-in-protected-mode>

<https://wiki.osdev.org/%228042%22_PS/2_Controller#Initialising_the_PS.2F2_Controller>

Keyboard read - actually write x86 PS/2 driver

Qemu read disk
Qemu-system-i386 -fda boot.bin
