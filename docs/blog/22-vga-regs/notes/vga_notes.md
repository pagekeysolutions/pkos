## BIOS VGA Mode 13h

https://en.wikipedia.org/wiki/Mode_13h

## Open BIOS VGA Driver

https://github.com/openbios/openbios/blob/master/drivers/vga_load_regs.c#L408

## QEMU Card Docs

Per [here](https://www.qemu.org/docs/master/system/i386/pc.html), qemu-system-i386 has a Cirrus CLGD 5446 PCI VGA card.

Manual for that card: [here](https://theretroweb.com/chip/documentation/cl-gd5446technical-6456556f945a1573066314.pdf)

See 9.14.3 setting text mode (has code snippet)

## Linux Kernel: `save_vga_text`

Headers: https://github.com/torvalds/linux/blob/master/include/video/vga.h

Implementation: https://github.com/torvalds/linux/blob/master/drivers/video/vgastate.c#L48

## VESA Tutorial

https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial

## VGA Hardware Guide (OSDev)

https://wiki.osdev.org/VGA_Hardware
