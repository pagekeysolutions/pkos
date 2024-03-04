#include "debug.h"

#include <stdarg.h>
#include <stdbool.h>

#define QEMU_BOCHS_DEBUG_SERIAL_PORT 0xE9

void debug_console_putc(char c)
{
    ioport_out(QEMU_BOCHS_DEBUG_SERIAL_PORT, c);
}

void debug_console_puts(const char *s)
{
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		debug_console_putc(s[i]);
	}
}


// Helper function to print integers
void debug_console_putint(int value, int base) {
    char num_str[16];
    const char *digits = "0123456789ABCDEF";
    bool is_negative = false;
    int i = 15;
    num_str[i--] = '\0';

    if (value == 0) {
        num_str[i--] = '0';
    } else {
        if (base == 10 && value < 0) {
            is_negative = true;
            value = -value;
        }

        while (value > 0 && i) {
            num_str[i--] = digits[value % base];
            value /= base;
        }

        if (is_negative) {
            num_str[i--] = '-';
        }
    }

    debug_console_puts(&num_str[i + 1]);
}

// Helper function to print unsigned integers
void debug_console_putuint(unsigned int value, int base) {
    char num_str[16];
    const char *digits = "0123456789ABCDEF";
    int i = 15;
    num_str[i--] = '\0';

    if (value == 0) {
        num_str[i--] = '0';
    } else {
        while (value > 0 && i) {
            num_str[i--] = digits[value % base];
            value /= base;
        }
    }

    debug_console_puts(&num_str[i + 1]);
}

// Helper function to print unsigned integers with optional padding
void debug_console_putuint_padded(unsigned int value, int base, int pad, char pad_char) {
    char num_str[16];
    const char *digits = "0123456789ABCDEF";
    int i = 15;
    num_str[i--] = '\0';

    if (value == 0) {
        // Handle zero specially
        while (pad-- > 1) {
            num_str[i--] = pad_char;
        }
        num_str[i--] = '0';
    } else {
        int len = 0;
        unsigned int value_copy = value;
        // First pass: calculate the length
        while (value_copy > 0) {
            len++;
            value_copy /= base;
        }
        // Apply padding
        while (pad-- > len) {
            num_str[i--] = pad_char;
        }
        // Second pass: populate the number string
        while (value > 0) {
            num_str[i--] = digits[value % base];
            value /= base;
        }
    }

    debug_console_puts(&num_str[i + 1]);
}

void debug_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == '0') {
                // Handle zero padding
                int pad = 0;
                format++;  // Skip '0'
                pad = *format - '0';  // Get the width (currently supports only single digit width)
                format++;
                if (*format == 'x' || *format == 'X') {
                    unsigned int num = va_arg(args, unsigned int);
                    debug_console_putuint_padded(num, 16, pad, '0');
                }
                // Handle other padding cases as needed
            } else {
                switch (*format) {
                    // Existing cases...
                    case 'x':
                    case 'X': {
                        unsigned int num = va_arg(args, unsigned int);
                        debug_console_putuint(num, 16);
                        break;
                    }
                    // Other cases...
                }
            }
        } else {
            debug_console_putc(*format);
        }
        format++;
    }

    va_end(args);
}