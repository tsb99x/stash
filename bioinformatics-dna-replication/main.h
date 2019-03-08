#ifndef MAIN_H
#define MAIN_H

#include <string.h>

#ifdef _WIN32
#define __FILENAME__                                                           \
    (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__                                                           \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define panic_m(S) invoke_panic(S, __FILENAME__, __LINE__)

void invoke_panic(const char *const msg, const char *const file, int line);

void complement(const char *const src_strand, char *dst_strand);

char lookup_base_compl(const char base);

#endif
