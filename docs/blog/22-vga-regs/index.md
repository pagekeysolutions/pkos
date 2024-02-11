# OS22: Fine-Tuned VGA Register Control

(Full VGA Driver)

TODO intro

Implemented in issue [#2](https://gitlab.com/pagekey/apps/pkos/pkos/-/issues/2) and MR [!2](https://gitlab.com/pagekey/apps/pkos/pkos/-/merge_requests/2).

## Motivation

TODO

### How It Looked in OS15

TODO - maybe condense this and the following into one image

[Link](https://gitlab.com/pagekey/apps/pkos/pkos/-/blob/aec21a2e2b9b481a6883ce0843a7c1bd77e537b9/src/vga/vga.c#L9) to register values in working impl

### How It's Going Now

TODO

(with/without clear screen)

(show setting pixel - long boi)


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
