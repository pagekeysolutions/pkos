# OS22: Fine-Tuned VGA Register Control

TODO intro

## Motivation

TODO

### How It Looked in OS15

TODO - maybe condense this and the following into one image

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
