#ifndef LIB_PANIC_H
#define LIB_PANIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __FILENAME__                                                           \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define panic_m(...)                                                           \
    do {                                                                       \
        fprintf(stderr, "[E]: ");                                              \
        fprintf(stderr, __VA_ARGS__);                                          \
        fprintf(stderr, " @ %s:%d", __FILENAME__, __LINE__);                   \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

#endif
