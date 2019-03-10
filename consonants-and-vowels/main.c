#include "panic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char consonants[] = "bcdfghjklmnpqrstvwxyz";
const char vowels[] = "aeiou";

const size_t consonants_size = sizeof consonants - 1;
const size_t vowels_size = sizeof vowels - 1;

char gen_char(const char ch)
{
    switch (ch) {
    case 'c':
        return consonants[rand() % consonants_size];
    case 'C':
        return (char)toupper(consonants[rand() % consonants_size]);
    case 'v':
        return vowels[rand() % vowels_size];
    case 'V':
        return (char)toupper(vowels[rand() % vowels_size]);
    default:
        panic_m("Unknown char '%c' found in input", ch);
    }
}

int main()
{
    srand((unsigned int)time(NULL));

    char input_buf[255];
    if (fgets(input_buf, sizeof input_buf, stdin) == NULL)
        panic_m("Failed to acquire input");

    for (char *ch = input_buf; *ch != '\n' && *ch != '\0'; ch++)
        printf("%c", gen_char(*ch));
}
