# OS10: Running on Real Hardware (Boot from ISO)

Saturday, June 27, 2020
9:19 PM
 
<https://www-uxsup.csx.cam.ac.uk/pub/doc/suse/suse9.2/suselinux-adminguide_en/ch07s07.html>
<https://www.gnu.org/software/grub/manual/grub/html_node/Making-a-GRUB-bootable-CD_002dROM.html>

sudo apt-get install grub-pc-bin
*From \<<https://askubuntu.com/questions/928550/grub-mkrescue-not-creating-iso-file>\>*
 
apt-get install xorriso
*From \<<https://stackoverflow.com/questions/45991142/os-programming-using-grub>\>*
 
You can easily create a bootable CD-ROM image containing the GRUB bootloader and your kernel using the program grub-mkrescue. You may need to install the GRUB utility programs and the program xorriso (version 0.5.6 or higher). First you should create a file called grub.cfg containing the contents:

menuentry \"myos\" {\
        multiboot /boot/myos.bin\
}

Note that the braces must be placed as shown here. You can now create a bootable image of your operating system by typing these commands:
```bash
**mkdir** -p isodir**/**boot**/**grub\
**cp** myos.bin isodir**/**boot**/**myos.bin\
**cp** grub.cfg isodir**/**boot**/**grub**/**grub.cfg\
grub-mkrescue -o myos.iso isodir
```

*From \<<https://wiki.osdev.org/Bare_Bones>\>*

qemu-system-i386 -cdrom myos.iso
*From \<<https://wiki.osdev.org/Bare_Bones>\>*

**You must publish the GRUB Source Code for that exact version if you redistribute your OS that uses it. (You don\'t have to publish your OS source code)**
 
**Linux USB burn:**

sudo dd bs=4M if=path/to/input.iso of=/dev/sd\<?> conv=fdatasync status=progress\
Mac USB Burn:

sudo dd if=inputfile.img of=/dev/disk\<?> bs=4m && sync

*From \<<https://askubuntu.com/questions/372607/how-to-create-a-bootable-ubuntu-usb-flash-drive-from-terminal>\>*

Windows USB Burn: use Universal USB Installer or rufus

## Script

 What\'s up! This is going to be an exciting - and hopefully short - video. Emulators are great and all, but it\'s about time we put our operating system on some real hardware!

What we\'ll be doing is installing all the tools we need to install grub into an ISO file. That ISO can then be burned onto a USB or a CDROM, which will serve as our bootable medium for our OS.

**Repo Changes**

The only changes from the last video are in the Makefile. (...)

**New Dependencies**

Blah

**Burning the Image**

I use this little tool. On Linux you can probably just dd it onto the device
