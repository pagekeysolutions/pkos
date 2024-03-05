#ifndef __DEBUG_H__
#define __DEBUG_H__

#define QEMU_BOCHS_DEBUG_SERIAL_PORT 0xE9

void debug_console_putc(char c);

void debug_console_puts(const char *s);

// Helper function to print integers
void debug_console_putint(int value, int base);

// Helper function to print unsigned integers
void debug_console_putuint(unsigned int value, int base) ;

void debug_printf(const char *format, ...);

#endif // __DEBUG_H__