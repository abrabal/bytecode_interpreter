#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "code_parser.h"
#include "opcodes.h"

#define NUM_INS (sizeof(opcodes_for_parser)/ sizeof(opcodes_for_parser[0]))

Opcode opcodes_for_parser[] =
{
    {"add", 68},
    {"and", 67},
    {"immediate", 0},
    {"jgez", 198},
    {"jgz", 199},
    {"jlez", 195},
    {"jlz", 194},
    {"jnz", 197},
    {"jump", 196},
    {"jz", 193},
    {"nand", 65},
    {"nop", 192},
    {"nor", 66},
    {"or", 64},
    {"sub", 69},
};

int string_cmp(const void *p1, const void *p2){
    const Opcode *struct1 = (const Opcode *)p1;
    const Opcode *struct2 = (const Opcode *)p2;

    return strcmp(struct1->name, struct2->name);
}

int main()
{
    qsort(opcodes_for_parser, NUM_INS, sizeof(Opcode), string_cmp);

    printf ("Opcode opcodes_for_parser[] =\n{\n");
    for (long unsigned int i = 0; i < NUM_INS; i++){
        printf("    {\"%s\", %d},\n", opcodes_for_parser[i].name, opcodes_for_parser[i].value);
    }
    printf ("};");

    return 0;
}