#include <stdio.h>
#include <assert.h>
#include "xtra.h"

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("Please input the file");
        return 1;
    }

    FILE *file = fopen(argv[1],"rb");
    assert(file);

    printf(".globl test\n"
           "test:\n"
           "    push %%rbp\n"
           "    mov %%rsp, %%rbp\n");
    xtra(file);

    printf("    pop %%rbp\n"
           "    ret\n");

    fclose(file);

    return 0;
}
