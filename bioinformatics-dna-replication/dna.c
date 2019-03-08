#include "main.h"

#include <stdio.h>

void complement(const char *const src_strand, char *dst_strand)
{
    const char *src_ptr = src_strand;
    char *dst_ptr = dst_strand;

    while (*src_ptr != '\0') {
        *dst_ptr = lookup_base_compl(*src_ptr);

        src_ptr++;
        dst_ptr++;
    }

    *dst_ptr = '\0';
}

char lookup_base_compl(const char base)
{
    switch (base) {
    case 'A':
        return 'T';
    case 'T':
        return 'A';
    case 'G':
        return 'C';
    case 'C':
        return 'G';
    case ' ':
        return ' ';
    default:
        char res_msg[255];
        sprintf_s(res_msg, 255, "%s '%c'", "Failed to complement base of",
                  base);
        panic_m(res_msg);
    }
}
