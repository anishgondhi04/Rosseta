//
// Created by anish gondhi on 2024-03-26.
//

#ifndef XTRA_XTRA_H
#define XTRA_XTRA_H


char *reg_map64[] = {
        "%rax",
        "%rbx",
        "%rcx",
        "%rdx",
        "%rsi",
        "%rdi",
        "%r8 ",
        "%r9 ",
        "%r10",
        "%r11",
        "%r12",
        "%r13",
        "%r14",
        "%r15",  // flags
        "%rbp",  // r14  frame pointer
        "%rsp",  // r15  stack pointer
        "%rip"
};


void xtra(FILE *file);

#endif //XTRA_XTRA_H
