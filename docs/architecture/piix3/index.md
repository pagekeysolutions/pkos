---
status: proposed
creation-date: "2024-02-27"
authors: [ "@stephengrice" ]
coach: "n/a"
approvers: [ "@jonstrong", "@tonyprogrammer" ]
---

# IDE Hard Drive Driver

## Summary

In order to store persistent data, we need a hard drive driver. The QEMU i386 system contains a PIIX3 hard drive, so we'll start by writing some code to interface with it directly. Once this driver is available, we can use it for higher level abstractions such as filesystems. Also, we can use what we learn from this to add support for other hard drive models.

## Motivation

We need to store persistent data or else this is really boring and useless.

### Goals

- Be able to write a string to the QEMU-provided hard drive
- Be able to read the string back from the hard drive (even after shutdown if same drive is attached)

### Non-Goals

Out of scope:

- Filesystem development
- Any other device except for the PIIX3 that comes with `qemu-system-i386`

## Proposal

Hard-code the exact messages that need to be sent to the IDE controller. Then, generalize them into a driver that will work with more devices and in more modes.

## Design and implementation details

### Detecting IDE Devices

(class code, blah)

### Detecting Mode

(compatibility vs native mode)

### Command Ports for Compatibility Mode

When in compatibility mode, `0x1F0` is the start address for the master IDE controller [^1].

Offset 0 from the start address is the command I/O port [^2].

Therefore, in compatibility mode, `IDE_MASTER_COMMAND` port is `0x1F0`.

The status port is at offset `0x2` [^2]. Therefore, `IDE_MASTER_STATUS` is `0x1F2` in compatibility mode.

### Sending Commands

TODO

## Alternative Solutions

Cry.


[^1]: <https://wiki.osdev.org/IDE>
[^2]: [PIIX3 Technical Manual](https://pdf.datasheetcatalog.com/datasheet/Intel/mXvqwzr.pdf). See page 30 for I/O ports.
