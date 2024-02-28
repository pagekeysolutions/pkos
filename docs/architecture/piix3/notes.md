# PIIX Notes / Research

## Wikipedia

<https://en.wikipedia.org/wiki/PIIX>
- PIIX: PCI IDE ISA Xcelerator
- aka: Intel 82371
- IDE = PATA
- Contains
    - 2 DMA (direct memory access) controllers
    - 1 PIT (programmable interval timer)
    - 2 PICs (programmable interrupt chip)
    - PCI-to-ISA bus bridge
- PIIX3: adds USB 1.0, I/O APIC

## Technical Specification

<https://pdf.datasheetcatalog.com/datasheet/Intel/mXvqwzr.pdf>
- Page 30 / Table 6: I/O registers
  - Offset from base address

## IDE on OSDev Wiki

<https://wiki.osdev.org/IDE>
- IDE controller: Class Code = 1, Subclass Code = 1
- ProgIf: determine mode
- Bit 0-1: primary channel
- Bit 2-3: secondary channel
- Bit 7: Master (DMA enabled)
- Compatibility mode: pre-set ports
  - 0x1F0 to 0x1F7
  - 0x3F6
  - IRQ14
- Native mode: read the BAR to figure out I/O addresses / IRQs

## I/O Ports on OSDev Wiki

- <https://wiki.osdev.org/I/O_Ports>
  - 0x1F0: Primary ATA controller (IDE)

## ATA Driver - RTEMS

<https://docs.rtems.org/branches/master/bsp-howto/ata.html>

## ATA Driver - OSDev

<https://github.com/levex/osdev/blob/master/drivers/ata.c>

- Note: `ATA_PRIMARY_IO` matches addr for master IDE controller in compat mode
- `ide_identify` function
  - Sets a bunch of register values up
  - Sends an IDENTIFY command
  - Reads status
  - If status is 0, done
  - Waits until "busy" bit is not set
  - Reads status again
  - Checks error bit
  - Waits for something?
  - Reads 256 words into memory at `ide_buf` - could this be the IDE Descriptor Table?

## Paul

- PIO = Slow but easy
- DMA = Performance
