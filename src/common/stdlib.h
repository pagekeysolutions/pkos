#ifndef __STDLIB_H
#define __STDLIB_H

#include "types.h"

#include <stdbool.h>

char* itoa(int integer);
char* itoah(int integer);
char* itoab(int integer);

int strlen(const char* string);
bool streq(char* string1, char* string2);
bool safe_streq(char* string1, int str1len, char* string2, int str2len);

void terrible_sleep_impl(int ticks);

#endif