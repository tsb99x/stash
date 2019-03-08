#include "main.h"

#include <stdlib.h>
#include <string.h>

int main()
{
    char src1[] = "A T A A G C";
    char res1[sizeof(src1)];
    complement(src1, res1);

    if (strncmp("T A T T C G", res1, sizeof(src1)) != 0)
        return -1;

    char src2[] = "A A T G C C T A T G G C";
    char res2[sizeof(src2)];
    complement(src2, res2);

    if (strncmp("T T A C G G A T A C C G", res2, sizeof(src2)) != 0)
        return -1;
}
