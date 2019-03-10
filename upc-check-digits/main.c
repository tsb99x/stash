#include "panic.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int upc(const char *const str, const size_t pad_size)
{
    bool is_pad_even = pad_size % 2;

    int sum = 0;
    for (size_t i = 0; i < 11 - pad_size; i++) {
        if (!isdigit(str[i]))
            panic_m("Failed to convert non-digit char of '%c' to int", str[i]);

        int digit = str[i] - '0';
        sum += (i % 2 == is_pad_even) ? digit * 3 : digit;
    }

    int m = sum % 10;
    return (m == 0) ? 0 : 10 - m;
}

#define INPUT_BUF_SIZE 255

int main()
{
    char input_buf[INPUT_BUF_SIZE];
    if (fgets(input_buf, sizeof input_buf, stdin) == NULL)
        panic_m("Failed to acquire input");

    size_t input_len = strnlen(input_buf, INPUT_BUF_SIZE) - 1; // -1 for '\n'
    if (input_len == 0 || input_len > 11)
        panic_m("Input str length must be from 1 to 11 chars");

    printf("%d", upc(input_buf, 11 - input_len));
}
