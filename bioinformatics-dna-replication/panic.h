#ifndef PANIC_H
#define PANIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __FILENAME__                                                           \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define panic_m(S)                                                             \
    do {                                                                       \
        fprintf(stderr, "[E]: %s @ %s:%d", S, __FILENAME__, __LINE__);         \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

#endif
