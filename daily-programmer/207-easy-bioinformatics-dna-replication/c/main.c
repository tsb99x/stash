#include "main.h"

#include "panic.h"

#define BUF_SIZE 255

enum mode { compl, ident };

enum mode parse_mode(const char *const arg)
{
    if (!strcmp(arg, "-c")) {
        return compl;
    } else if (!strcmp(arg, "-i")) {
        return ident;
    } else {
        panic_m("Failed to parse mode of '%s'", arg);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
        panic_m("Failed to obtain mode arg, use:\n"
                "\t'-c' to complement\n"
                "\t'-i' to identify");

    enum mode mode = parse_mode(argv[1]);

    printf("SRC> ");
    char input_buf[BUF_SIZE];
    if (!fgets(input_buf, sizeof input_buf, stdin))
        panic_m("Failed to acquire input");
    input_buf[strcspn(input_buf, "\n")] = 0;

    char dst_buf[BUF_SIZE];
    if (mode == compl) {
        complement(input_buf, dst_buf);
    } else {
        identify(input_buf, dst_buf);
    }
    printf("RES> %s", dst_buf);
}
