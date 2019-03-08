#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 255

int main()
{
    printf("SRC> ");
    char input_buf[BUF_SIZE];
    if (!gets_s(input_buf, sizeof(input_buf)))
        panic_m("Failed to acquire input");

    char dst_strand[BUF_SIZE];
    complement(input_buf, dst_strand);
    printf("DST> %s", dst_strand);
}
