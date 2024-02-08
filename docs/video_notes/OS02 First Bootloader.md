# OS2: Running Our First Bootloader
Tuesday, December 24, 2019
9:21 AM

-   Installing Guest Additions

```bash
su
apt-get update && apt-get upgrade
apt-get install gcc make perl build-essential linux-headers-\$(uname -r)
```

-   Click button to insert image
```bash
sh /media/cdrom/VBoxLinuxAdditions.run
/sbin/reboot
```

-   Ignore critical error. Just shut down and restat
-   Installing build tools and QEMU
    -   Su
    -   Apt install qemu qemu-system-i386 nasm
    -   Test it out: nasm
    -   Test: qemu-system-i386
    -   Good to go!
-   Let\'s do our first bootloader - copy-paste
    -   Make clipboard bidirectional
    -   wget <https://raw.githubusercontent.com/pagekeysolutions/education/master/OS/video2/first.asm>
    -   nasm -f bin first.asm -o first.bin
    -   Qemu-system-i386 first.bin
    -   There it is!
-   Take a look at what\'s actually here
    -   Lovely raw machine code
    -   Vi first.out
    -   :%! Xxd
    -   This is where you actually see the individual instructions
    -   Doesn\'t get much lower level than this for comp sci people
    -   Note the 0 padding and the final signature:
    -   X86 processors are little endian
    -   Edit something
    -   :%! xxd -r
    -   :wq
    -   Qemu-system-i386 first.bin
-   Create ISO
```bash
dd if=/dev/zero of=floppy.img bs=1024 count=1440\
dd if=boot.bin of=floppy.img seek=0 count=1 conv=notrunc
```
- *From \<<https://stackoverflow.com/questions/34268518/creating-a-bootable-iso-image-with-custom-bootloader>\>*
```bash
mkdir iso\
cp floppy.img iso/\
genisoimage -quiet -V \'MYOS\' -input-charset iso8859-1 -o myos.iso -b floppy.img -hide floppy.img iso/
```
- *From \<<https://stackoverflow.com/questions/34268518/creating-a-bootable-iso-image-with-custom-bootloader>\>*
```bash
qemu-system-i386 -cdrom ./myos.iso
```
- *From \<<https://stackoverflow.com/questions/34268518/creating-a-bootable-iso-image-with-custom-bootloader>\>*
-   Next video: How this all works, and some fun programs for the bootloader


OS Bootloader Notes
Friday, March 27, 2020
9:00 AM

<http://mikeos.sourceforge.net/write-your-own-os.html>

<https://stackoverflow.com/questions/43668314/reading-input-in-bios-level-assembly>

<http://ctyme.com/rbrown.htm>

 

<https://html5up.net/>

<https://50linesofco.de/post/2018-02-28-writing-an-x86-hello-world-bootloader-with-assembly>

 
