//
// Created by anish gondhi on 2024-03-25.
//

#include <stdio.h>
#include "xis.h"
#include "extra.h"


void xtra(FILE *file) {

    //this is register mapping
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
    char *reg_map8[] = {
            "%al",
            "%bl",
            "%cl",
            "%dl"
    };

    //instruction array is used to read instruction in binary from the given file
    //flag takes care of the debug function call
    //offset is used to set the labels before each instruction
    char instruction[2];
    int flag = 0;
    int offset = 0x0000;

    //This loop runs until the there is no bits left in the file.
    while (fread(instruction, sizeof(char), 2, file) >= 2) {

        //word is used to read word for extended instructions
        //source is the first 4 bits in second byte which encodes source register
        //dest is the last 4 bits in second byte which encodes dest register
        char word[2];
        int source, dest, inst_f, inst_l, val;

        //filtering the encoding storing first and last byte separately
        inst_f = instruction[0] & 0xff;
        inst_l = instruction[1] & 0xff;

        //printing the label
        printf(".L%04x:\n", offset);
        offset += 2;

        //checking if debug is set
        if (flag) {
            printf("    call debug\n");
        }
        //checking if first and last byte are 0
        if (inst_f == 0x00 && inst_l == 0x00) {
            break;
        }

        //checking if extended
        if (((inst_f >> 6) & 0x03) == XIS_EXTENDED) {
            fread(word, sizeof(char), 2, file);
            val = word[0] & 0xff;
            val = val << 8;
            val |= (word[1] & 0xff);
            offset += 2;
        }

        source = (inst_l >> 4) & 0xf;
        dest = inst_l & 0x0f;


        //switch covers all the encoding for 30 instruction in x
        switch (inst_f) {
            case I_RET:
                printf("    ret\n");
                break;
            case I_CLD:
                flag = 0;
                break;
            case I_STD:
                flag = 1;
                break;
            case I_BR:
                printf("    cmpb $0x01, %%r15b\n");
                printf("    je .L%04x\n", (offset + inst_l - 2));
                break;
            case I_JR:
                printf("    jmp .L%04x\n", (offset + inst_l - 2));
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
                printf("    push %%rdi\n");
                printf("    mov %s, %%rdi\n", reg_map64[source]);
                printf("    call outchar\n");
                printf("    pop %%rdi\n");
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
                printf("    and %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_OR:
                printf("    or %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_XOR:
                printf("    xor %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_TEST:
                printf("    test %s, %s\n", reg_map64[source], reg_map64[dest]);
                printf("    setnz %sb\n", reg_map64[13]);
                break;
            case I_CMP:
                printf("    cmp %s, %s\n", reg_map64[source], reg_map64[dest]);
                printf("    setg %sb\n", reg_map64[13]);
                break;
            case I_EQU:
                printf("    cmp %s, %s\n", reg_map64[source], reg_map64[dest]);
                printf("    sete %sb\n", reg_map64[13]);
                break;
            case I_MOV:
                printf("    mov %s, %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_LOAD:
                printf("    mov (%s), %s\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_STOR:
                printf("    mov %s, (%s)\n", reg_map64[source], reg_map64[dest]);
                break;
            case I_LOADB:
                printf("    movb (%s), %s\n", reg_map64[source], reg_map8[dest]);
                break;
            case I_STORB:
                printf("    movb %s, (%s)\n", reg_map8[source], reg_map64[dest]);
                break;
            case I_JMP:
                printf("    jmp .L%04x\n", val);
                break;
            case I_CALL:
                printf("    call .L%04x\n", val);
                break;
            case I_LOADI:
                printf("    mov $%d, %s\n", val, reg_map64[source]);
                break;
            default:
                break;
        }

    }

}