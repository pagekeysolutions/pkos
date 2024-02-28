#include "kernel.h"
#include "keyboard_map.h"
#include "../common/stdlib.h"
#include "../screen/screen.h"
#include "../vga/vga.h"

// ----- Global variables -----
struct IDT_entry IDT[IDT_SIZE]; // This is our entire IDT. Room for 256 interrupts

char command_buffer[COMMAND_BUFFER_SIZE];
int command_len = 0;

void disable_cursor() {
	ioport_out(0x3D4, 0x0A);
	ioport_out(0x3D5, 0x20);
}

void init_idt() {
	// Get the address of the keyboard_handler code in kernel.asm as a number
	unsigned int kb_handler_offset = (unsigned long)keyboard_handler;
	// Populate the first entry of the IDT

	// why 0x21 and not 0x0? first 32 interrupts (up to 0x20)
	// are reserved for the CPU.
	// These include special interrupts such as divide-by-zero exception.

	// 0x21, or 33 decimal, is the first available interrupt
	// that we can set to whatever we want.
	IDT[0x21].offset_lowerbits = kb_handler_offset & 0x0000FFFF; // lower 16 bits
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = IDT_INTERRUPT_GATE_32BIT;
	IDT[0x21].offset_upperbits = (kb_handler_offset & 0xFFFF0000) >> 16;
	// Program the PICs - Programmable Interrupt Controllers
	// Background:
		// In modern architectures, the PIC is not a separate chip.
		// It is emulated in the CPU for backwards compatability.
		// The APIC (Advanced Programmable Interrupt Controller)
		// is the new version of the PIC that is integrated into the CPU.
		// Default vector offset for PIC is 8
		// This maps IRQ0 to interrupt 8, IRQ1 to interrupt 9, etc.
		// This is a problem. The CPU reserves the first 32 interrupts for
		// CPU exceptions such as divide by 0, etc.
		// In programming the PICs, we move this offset to 0x2 (32) so that
		// we can handle all interrupts coming to the PICs without overlapping
		// with any CPU exceptions.

	// Send ICWs - Initialization Command Words
	// PIC1: IO Port 0x20 (command), 0xA0 (data)
	// PIC2: IO Port 0x21 (command), 0xA1 (data)
	// ICW1: Initialization command
	// Send a fixed value of 0x11 to each PIC to tell it to expect ICW2-4
	// Restart PIC1
	ioport_out(PIC1_COMMAND_PORT, 0x11);
	ioport_out(PIC2_COMMAND_PORT, 0x11);
	// ICW2: Vector Offset (this is what we are fixing)
	// Start PIC1 at 32 (0x20 in hex) (IRQ0=0x20, ..., IRQ7=0x27)
	// Start PIC2 right after, at 40 (0x28 in hex)
	ioport_out(PIC1_DATA_PORT, 0x20);
	ioport_out(PIC2_DATA_PORT, 0x28);
	// ICW3: Cascading (how master/slave PICs are wired/daisy chained)
	// Tell PIC1 there is a slave PIC at IRQ2 (why 4? don't ask me - https://wiki.osdev.org/8259_PIC)
	// Tell PIC2 "its cascade identity" - again, I'm shaky on this concept. More resources in notes
	ioport_out(PIC1_DATA_PORT, 0x0);
	ioport_out(PIC2_DATA_PORT, 0x0);
	// ICW4: "Gives additional information about the environemnt"
	// See notes for some potential values
	// We are using 8086/8088 (MCS-80/85) mode
	// Not sure if that's relevant, but there it is.
	// Other modes appear to be special slave/master configurations (see wiki)
	ioport_out(PIC1_DATA_PORT, 0x1);
	ioport_out(PIC2_DATA_PORT, 0x1);
	// Voila! PICs are initialized

	// Mask all interrupts (why? not entirely sure)
	// 0xff is 16 bits that are all 1.
	// This masks each of the 16 interrupts for that PIC.
	ioport_out(PIC1_DATA_PORT, 0xff);
	ioport_out(PIC2_DATA_PORT, 0xff);

	// Last but not least, we fill out the IDT descriptor
	// and load it into the IDTR register of the CPU,
	// which is all we need to do to make it active.
	struct IDT_pointer idt_ptr;
	idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
	idt_ptr.base = (unsigned long) &IDT;
	// Now load this IDT
	load_idt(&idt_ptr);
}

void kb_init() {
	// 0xFD = 1111 1101 in binary. enables only IRQ1
	// Why IRQ1? Remember, IRQ0 exists, it's 0-based
	ioport_out(PIC1_DATA_PORT, 0xFD);
}

void handle_keyboard_interrupt() {
	// Write end of interrupt (EOI)
	ioport_out(PIC1_COMMAND_PORT, 0x20);

	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
	// Lowest bit of status will be set if buffer not empty
	// (thanks mkeykernel)
	if (status & 0x1) {
		char keycode = ioport_in(KEYBOARD_DATA_PORT);
		if (keycode < 0 || keycode >= 128) return;
		if (keycode == 28) {
			// ENTER : Newline
			newline();
			// null terminate command buffer
			command_buffer[command_len] = '\0';
			// Handle command
			if (streq(command_buffer, "ls")) {
				println("Filesystem not yet implemented.");
			} else if (streq(command_buffer, "clear")) {
				clear_screen();
			} else if (streq(command_buffer, "vga")) {
				vga_enter();
			} else if (streq(command_buffer, "vgainfo")) {
				vga_info();
			} else if (streq(command_buffer, "vgafont")) {
				vga_font();
			} else if (streq(command_buffer, "lspci")) {
				lspci();
			} else if (streq(command_buffer, "ide")) {
				idetest();
			} else if (streq(command_buffer, "help")) {
				println("clear: Clear screen");
				println("ls: List files");
				println("lspci: Enumerate PCI devices");
				println("ide: Run ide test");
				println("vga: Run VGA test");
				println("vgainfo: Print VGA info");
			} else if (command_len < 1) {
				// do nothing
			} else {
				print("Command not found: ");
				println(command_buffer);
				println("Write `help` to see commands.");
			}
			command_len = 0;
			print_prompt();
		} else if (keycode == 14) {
			// BACKSPACE: Move back one unless on prompt
			backspace();
			if (command_len > 0) {
				command_len--;
			}
		} else if (keycode == 1) {
			// ESCAPE
			vga_exit();
		} else {
			if (command_len >= COMMAND_BUFFER_SIZE) return;
			command_buffer[command_len++] = keyboard_map[keycode];
			printchar(keyboard_map[keycode]);
		}
	}
}

// ----- Entry point -----
int main() {
	print_message();
	print_prompt();
	disable_cursor();
	init_idt();
	kb_init();
	enable_interrupts();
	// Finish main execution, but don't halt the CPU. Same as `jmp $` in assembly
	while(1);
}
