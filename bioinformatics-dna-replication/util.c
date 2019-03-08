#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void invoke_panic(const char *const msg, const char *const file, int line)
{
    fprintf(stderr, "E: %s @ %s:%d", msg, file, line);
    exit(EXIT_FAILURE);
}
