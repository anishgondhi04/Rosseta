#include <stdio.h>
#include <assert.h>
#include "extra.h"

int main(int argc, char **argv) {

    //checking if file is passed as an arguement
    if (argc <= 1) {
        printf("Please input the file");
        return 1;
    }

    //file pointer to binary file
    FILE *file = fopen(argv[1],"rb");
    assert(file);

    //printing the prologue
    printf(".globl test\n"
           "test:\n"
           "    push %%rbp\n"
           "    mov %%rsp, %%rbp\n");

    //calling xtra to translate the x to x86
    xtra(file);

    //printing the epilogue
    printf("    pop %%rbp\n"
           "    ret\n");

    //closing file
    fclose(file);

    return 0;
}
