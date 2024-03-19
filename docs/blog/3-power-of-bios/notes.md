# OS3: Hone the Power of the BIOS
Tuesday, December 24, 2019
5:56 PM

-   ~~Learning Outcomes~~
    -   ~~What is the BIOS?~~
        -   ~~Basic Input Output System~~
        -   ~~Firmware~~
    -   ~~How do I use the BIOS?~~
        -   ~~Instead of function calls, use interrupts~~
        -   ~~Arguments go in registers (or in stack, eventually)~~
        -   ~~AH register typically designates which function~~
        -   ~~Al, cx, dx, etc. can contain arguments~~
        -   ~~Consult reference for more information~~
    -   ~~Where is the reference guide for BIOS calls?~~
        -   ~~Link to the dude\'s online ref~~
        -   ~~Also link to the dude\'s zip file / download page~~
-   ~~Also:~~
    -   ~~Go over original bootloader line-by-line~~
    -   ~~Modify: Write something to read char and re-print~~
    -   ~~Challenge: Do more (next vid can be fun programs)~~
        -   ~~Ideas:~~
            -   ~~X~~
            -   ~~X~~
            -   ~~X~~
-   Go through the slides
	 - Make sure you apt install vim
 - **Why org 0x7c00?**
 > A bootloader runs under certain conditions that the programmer must appreciate in order to make a successful bootloader. The following pertains to bootloaders initiated by the PC BIOS:
-   The first sector of a drive contains its boot loader.
-   One sector is 512 bytes --- the last two bytes of which must be 0xAA55 (i.e. 0x55 followed by 0xAA), or else the BIOS will treat the drive as unbootable.
-   If everything is in order, said first sector will be placed at RAM address 0000:7C00, and the BIOS\'s role is over as it transfers control to 0000:7C00. (I.e. it JMPs to that address)
-   <https://stackoverflow.com/questions/5611047/why-do-we-give-org-7c00-at-the-start-of-a-boot-program>

> Setting a graphics mode through BIOS (int 10h with AH=0) will clear the screen.

*From \<<https://stackoverflow.com/questions/8239143/how-can-i-clear-the-screen-without-having-to-fill-it>\>*

```asm
mov ah, 0x00\
mov al, 0x03 ; text mode 80x25 16 colours

mov al, 0x13 ; vga mode

int 0x10
```

*From \<<https://stackoverflow.com/questions/8239143/how-can-i-clear-the-screen-without-having-to-fill-it>\>*

- What's left?
	- Chop up the audio
	- Create the video w/ slides
	- (maybe) re-record the screen to match the audio
	- Watch the whole thing to double check
	- Export, upload, and schedule
