#ifndef __SCREEN_H
#define __SCREEN_H

#define ROWS 25
#define COLS 80
#define VIDMEM 0xb8010
#define PROMPT "pkos> "
#define PROMPT_LENGTH 6

void println(char* string);
void print(char* string);
void safe_println(char* string, int len);
void safe_print(char* string, int len);
void printchar(char c);
void printchar_at(char c, int row, int col);
extern void print_char_with_asm(char c, int row, int col);
void clear_screen();
void print_prompt();
void print_message();
void newline();
void backspace();

#endif