//
// Created by anish gondhi on 2024-03-25.
//

#include <stdio.h>
#include "xis.h"
#include "extra.h"


void xtra(FILE *file) {

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


    char instruction[2];
    int flag = 0;

    while (fread(instruction, sizeof(char), 2, file) >= 2) {
        char word[2];
        int source, dest,inst_f,inst_l,val;

        inst_f = instruction[0] & 0xff;
        inst_l = instruction[1] & 0xff;

        if (flag) {
            printf("    call debug\n");
        }
        if (inst_f == 0x00 && inst_l == 0x00) {
            break;
        }
        if (((inst_f >> 6) & 0x03) == XIS_EXTENDED) {
            fread(word, sizeof(char),2,file);
            val = word[0] & 0xff;
            val = val << 8;
            val |= (word[1] & 0xff);
        }

        source = (inst_l >> 4) & 0xf;
        dest = inst_l & 0x0f;

        switch (inst_f) {
            case I_RET:
                break;
            case I_CLD:
                flag = 0;
                break;
            case I_STD:
                flag = 1;
                break;
            case I_BR:
                break;
            case I_JR:
                break;
            case I_NEG:
                printf("    neg %s\n", reg_map64[source]);
                break;
            case I_NOT:
                printf("    not %s\n", reg_map64[source]);
                break;
            case I_INC:
                printf("    inc %s\n", reg_map64[source]);
                break;
            case I_DEC:
                printf("    dec %s\n", reg_map64[source]);
                break;
            case I_PUSH:
                printf("    push %s\n", reg_map64[source]);
                break;
            case I_POP:
                printf("    pop %s\n", reg_map64[source]);
                break;
            case I_OUT:
                break;
            case I_ADD:
                printf("    add %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_SUB:
                printf("    sub %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_MUL:
                printf("    imul %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_AND:
                printf("    add %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_OR:
                printf("    or %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_XOR:
                printf("    xor %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_TEST:
                printf("    test %s, %s\n", reg_map64[source], reg_map64[dest]);
                printf("    setnz %s\n", reg_map64[13]);
                break;
            case I_CMP:
                printf("    cmp %s, %s\n", reg_map64[source], reg_map64[dest]);
                printf("    setg %s\n", reg_map64[13]);
                break;
            case I_EQU:
                printf("    cmp %s, %s\n", reg_map64[source], reg_map64[dest]);
                printf("    sete %s\n", reg_map64[13]);
                break;
            case I_MOV:
                printf("    mov %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_LOAD:
                break;
            case I_STOR:
                break;
            case I_LOADB:
                break;
            case I_STORB:
                break;
            case I_JMP:
                printf("    jmp %d\n", val);
                break;
            case I_CALL:
                printf("    call %d\n", val);
                break;
            case I_LOADI:
                printf("    mov $%d, %s\n",val,reg_map64[source]);
                break;
        }

    }

}