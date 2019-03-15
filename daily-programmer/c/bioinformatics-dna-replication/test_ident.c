#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char src1[] = "A T G T T T C G A G G C T A A";
    char res1[sizeof src1];
    identify(src1, res1);

    if (strncmp("Met Phe Arg Gly STOP ", res1, sizeof src1)) {
        printf("got: %s", res1);
        exit(EXIT_FAILURE);
    }
}
