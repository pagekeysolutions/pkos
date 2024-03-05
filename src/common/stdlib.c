#include "stdlib.h"


// Base method for itoa
char* _itoa(int integer, char* result, int base) {
	int num_digits = 0;
	int val = 0;
    // Push each digit
	while (integer > 0) {
        // Mod 10 gets just the last digit
        // Adding '0' turns it into an ASCII character
		val = integer % base;
		if (val < 10) {
			result[num_digits] = val + '0';
		} else {
			result[num_digits] = val + 'a';
		}
		num_digits++;
        // Divide by 10 to get the next character in line
		integer /= base;
	}

    // Reverse it and return it
    char tmp = 0;
    for (int i = 0; i < num_digits/2; i++) {
        // Swap at each end of the array
        tmp = result[i];
        result[i] = result[num_digits-i-1];
        result[num_digits-i-1] = tmp;
    }
    // Null terminate the string
	if (num_digits == 0) {
		num_digits = 1;
		result[0] = '0';
	}
    result[num_digits] = '\0';
	return result;
}

// Integer to ASCII
char itoa_buffer[256];

char* itoa(int integer) {
	return _itoa(integer, *itoa_buffer, 10);
}
// Integer to ASCII HEX
char* itoah(int integer) {
	return _itoa(integer, *itoa_buffer, 16);
}
// Integer to ASCII Binary
char* itoab(int integer) {
	return _itoa(integer, *itoa_buffer, 2);
}

bool streq(char* string1, char* string2) {
	int i = 0;
	while (true) {
		// Char mismatch? false
		if (string1[i] != string2[i]) {
			return false;
		}
		// They're equal, AND it's null char? We're done
		if (string1[i] == '\0') {
			break;
		}
		i++;
	}
	return true;
}

bool safe_streq(char* string1, int str1len, char* string2, int str2len) {
	if (str1len != str2len) return false;
	for (int i = 0; i < str1len; i++) {
		if (string1[i] != string2[i]) return false;
	}
	return true;
}

void terrible_sleep_impl(int ticks) {
	volatile int i = 0;
	while (i < ticks*100000) i++;
}

// needs to be in string.c for stdlib compatibility
int strlen(const char *s)
{
	int len = 0;
	while (s[len])
	{
		len++;
	}
	return len;
}
