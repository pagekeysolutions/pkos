#include "screen.h"

int cursor_row = 0;
int cursor_col = 0;

void println(char* string) {
	print(string);
	newline();
}

void print(char* string) {
	int i = 0;
	while (string[i] != '\0') {
		printchar(string[i]);
		i++;
	}
}

void safe_println(char* string, int len) {
	safe_print(string, len);
	cursor_col = 0;
	cursor_row++;
}

void safe_print(char* string, int len) {
	for (int i = 0; i < len; i++) {
		printchar_at(string[i], cursor_row, cursor_col);
		cursor_col++;
	}
}

void printchar(char c) {
	if (cursor_row >= ROWS) {
		cursor_row = cursor_row % ROWS;
		// clear the row before we print
		for (int i = 0; i < COLS; i++) {
			printchar_at(' ', cursor_row, i);
		}
	}
    printchar_at(c, cursor_row, cursor_col++);
    if (cursor_col >= COLS) {
        cursor_col = cursor_col % COLS;
        cursor_row++;
    }
}

void printchar_at(char c, int row, int col) {
	// OFFSET = (ROW * 80) + COL
	char* offset = (char*) (VIDMEM + 2*((row * COLS) + col));
	// Character value:
	*offset = c;
	// Attribute (color):
	*(offset+1) = 0x06;
}

void clear_screen() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printchar_at(' ', i, j);
		}
	}
    cursor_row = 0;
}

void newline() {
    cursor_row++;
    cursor_col = 0;
}

void backspace() {
    if (cursor_col > PROMPT_LENGTH) {
        printchar_at(' ', cursor_row, --cursor_col);
    }
}

void print_prompt() {
	cursor_col = 0;
	print(PROMPT);
	cursor_col = PROMPT_LENGTH;
}

void print_message() {
	// Fill the screen with 'x'
	int i, j;
	for (i = 0; i < COLS; i++) {
		for (j = 0; j < ROWS; j++) {
			if (j < 4) {
				printchar_at('*',j,i);
			} else {
				printchar_at(' ',j,i);
			}
		}
	}
	print("-PKOS-");
	cursor_row = 4;
}
