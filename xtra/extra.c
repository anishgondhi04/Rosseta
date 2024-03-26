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
        if(instruction[0] == 0x00 && instruction[1] == 0x00){
            break;
        }

        int no_of_operands, bit, reg, source, dest;
        no_of_operands = (instruction[0] >> 6) & 3;

        if (flag) {
            printf("    call debug\n");
        }
        switch (no_of_operands) {
            case 0:
                switch ((int)instruction[0]) {
                    case I_RET:
                        break;
                    case I_CLD:
                        flag = 0;
                        break;
                    case I_STD:
                        flag = 1;
                        break;
                }
                break;
            case 1:

                bit = (instruction[0] >> 5) & 1;
                if (bit) {
                    switch ((int)instruction[0]) {
                        case I_BR:
                            break;
                        case I_JR:
                            break;
                    }
                } else {
                    reg = (instruction[1] >> 4) & 0xf;
                    switch ((int)instruction[0]) {
                        case I_NEG:
                            printf("neg %s\n", reg_map64[reg]);
                            break;
                        case I_NOT:
                            printf("neg %s\n", reg_map64[reg]);
                            break;
                        case I_INC:
                            printf("inc %s\n", reg_map64[reg]);
                            break;
                        case I_DEC:
                            printf("dec %s\n", reg_map64[reg]);
                            break;
                        case I_PUSH:
                            printf("push %s\n", reg_map64[reg]);
                            break;
                        case I_POP:
                            printf("pop %s\n", reg_map64[reg]);
                            break;
                        case I_OUT:
                            break;
                    }
                }
                break;
            case 2:
                source = (instruction[1] >> 4) & 0xf;
                dest = (instruction[1] & 0x0f);

                switch ((int)instruction[0]) {
                    case I_ADD:
                        printf("add %s, %s\n", reg_map64[source], reg_map64[dest]);
                        break;
                    case I_SUB:
                        printf("sub %s, %s\n", reg_map64[source], reg_map64[dest]);
                        break;
                    case I_MUL:
                        printf("imul %s, %s\n", reg_map64[source], reg_map64[dest]);
                        break;
                    case I_AND:
                        printf("add %s, %s\n", reg_map64[source], reg_map64[dest]);
                        break;
                    case I_OR:
                        printf("or %s, %s\n",reg_map64[source],reg_map64[dest]);
                        break;
                    case I_XOR:
                        printf("xor %s, %s\n",reg_map64[source],reg_map64[dest]);
                        break;
                    case I_TEST:
                        if((source & dest) != 0 ){
                            printf("mov $0x1, %s\n",reg_map64[13]);
                        }else{
                            printf("mov $0x0, %s\n",reg_map64[13]);
                        }
                        break;
                    case I_CMP:
                        if(source < dest){
                            printf("mov $0x1, %s\n",reg_map64[13]);
                        }else{
                            printf("mov $0x0, %s\n",reg_map64[13]);
                        }
                        break;
                    case I_EQU:
                        if(source == dest){
                            printf("mov $0x1, %s\n",reg_map64[13]);
                        }else{
                            printf("mov $0x0, %s\n",reg_map64[13]);
                        }
                        break;
                    case I_MOV:
                        printf("mov %s, %s\n",reg_map64[source],reg_map64[dest]);
                        break;
                    case I_LOAD:
                        break;
                    case I_STOR:
                        break;
                    case I_LOADB:
                        break;
                    case I_STORB:
                        break;
                }
                break;
            case 3:
                switch ((int)instruction[0]) {
                    case I_JMP:
                        break;
                    case I_CALL:
                        break;
                    case I_LOADI:
                        break;
                }

                break;
            default:
                break;
        }
    }

}