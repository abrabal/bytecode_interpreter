#pragma once

typedef enum InstructionSet 
{
    OR = 64, 
    NAND = 65, 
    NOR = 66, 
    AND = 67, 
    ADD = 68, 
    SUB = 69, 
    NOP = 192, //JUMP_NEVER 
    JZ = 193, //JUMP_ZERO             
    JLZ = 194, //JUMP_LESS_ZERO
    JLEZ = 195, //JUMP_LESS_EQUAL_ZERO
    JUMP = 196, //JUMP_ALWAYS
    JNZ = 197, //JUMP_NOT_EQUAL_ZERO
    JGEZ = 198, //JUMP_GREATER_EQUAL_ZERO
    JGZ = 199 //JUMP_GREATER_ZERO
} InstructionSet;

#define COPY_MODE 128
#define IMMEDIATE_MODE 0
#define IMMEDIATE(const) (IMMEDIATE_MODE + const)
#define MOV(source, dest) (((source << 3) + (dest)) | 128)

typedef struct Opcode {
    char *name;
    int value;

} Opcode;