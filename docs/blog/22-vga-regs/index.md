# OS22: The VGA Rabbit Hole

If you've been watching for the past few days you'd notice that we've been grinding on VGA. Thankfully, it's not just me - this stuff is tough! (cite article)

Thankfully, with the help of people who joined the stream, we were able to get to the point where we can draw on *most* of the screen using memory-mapped I/O, and can escape the mode by hitting escape without ruining the text-mode graphics.

At the end, I threw in a quick rectangle animation just for fun (which cannot be interrupted).

See issue [#2](https://gitlab.com/pagekey/apps/pkos/pkos/-/issues/2) and MR [!2](https://gitlab.com/pagekey/apps/pkos/pkos/-/merge_requests/2) on GitLab for the code discussed in this post.

## Contents

1. [Motviation](#motivation)

   1. [How It Looked in OS15](#how-it-looked-in-os15)

   1. [Before](#how-its-going-now)

   1. [After](#how-its-going-now)

1. [Lessons Learned](#lessons-learned)

   1. [Not a State Machine](#not-a-state-machine)

   1. [Text Mode Attribute Byte](#text-mode-attribute-byte)

   1. [VGA Font Basics](#vga-font-basics)

   1. [Memcpy Woes - Jon's Address Breakthrough](#memcpy-woes---jons-address-breakthrough)

1. [The "Fix" - Beating Around the Bush](#the-fix---beating-around-the-bush)

1. [Overview of VGA Registers](#overview-of-vga-registers)

   1. [Getting and Settings Values](#getting-and-settings-values)

      1. [Address and Data Registers](#address-and-data-registers)

      1. [I/O Select Bit (Mono/Color)](#io-select-bit-monocolor)

1. [Next Steps](#next-steps)

   1. [Brute Forcing the Font Back](#brute-forcing-the-font-back)

   1. [VESA: More modern, better docs?](#vesa-more-modern-better-docs)

   1. [Other Projects, eventually Filesystem](#other-projects-eventually-filesystem)

## Motivation

TODO

### How It Looked in OS15

TODO - maybe condense this and the following into one image

[Link](https://gitlab.com/pagekey/apps/pkos/pkos/-/blob/aec21a2e2b9b481a6883ce0843a7c1bd77e537b9/src/vga/vga.c#L9) to register values in working impl

### Before

(completely messed up screen pointed out by Dominik Szasz on Discord)

### After

(after we made the updates in this MR)

## Lessons Learned

TODO

### Not a State Machine

TODO

### Text Mode Attribute Byte

TODO

### VGA Font Basics

TODO

### Memcpy Woes - Jon's Address Breakthrough

TODO

## The "Fix" - Beating Around the Bush

TODO

## Overview of VGA Registers

TODO

### Getting and Settings Values

TODO

#### Address and Data Registers

TODO

#### I/O Select Bit (Mono/Color)

TODO

## Next Steps

TODO

### Brute Forcing the Font Back

TODO

### VESA: More modern, better docs?

TODO

### Other Projects, eventually Filesystem

TODO

---


## `get_reg`, `set_reg`

## Programming each subsystem

### Graphics Controller Registers

TODO

- Started here - convert existing VGA code to use our drivers

### Attribute Controller Registers

TODO

- Very similar to GC but has palette

### External/General (MISC) Registers

TODO

- Had to do before CRTC b/c CRTC reg #'s dependent on this one
- First exposure to conditional register #'s

### CRT Controller (CRTC) Registers

TODO

- See EXT, needed an input bit from it to tell mono vs color

### Sequencer (SEQ) Registers

TODO

- Short, similar to GC approach

## Determining Register Values

STarting point: OS15 mysterious register code

### Strange Sequencer Behavior

Setting sequencer at all seems to cause crash.
This makes no sense if sequencer behaves in isolation.
But it turns out, modifying registers for one subsystem of VGA can affect all the others.
We need an easy way to look at all the values across the board. VGA rollup.

### Debugging with GDB

(add VGA rollup to be able to check all values at once)
(set breakpoint, check VGA rollup values)
(print entire structure, diff in vscode)
(set the register values for vga_exit)
