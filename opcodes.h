#pragma once

typedef enum InstructionSet 
{
    OR   = 0x40, 
    NAND = 0x41, 
    NOR  = 0x42, 
    AND  = 0x43, 
    ADD  = 0x44, 
    SUB  = 0x45, 

    NOP  = 0xC0, // JUMP_NEVER 
    JZ   = 0xC1, // JUMP_ZERO             
    JLZ  = 0xC2, // JUMP_LESS_ZERO
    JLEZ = 0xC3, // JUMP_LESS_EQUAL_ZERO
    JUMP = 0xC4, // JUMP_ALWAYS
    JNZ  = 0xC5, // JUMP_NOT_EQUAL_ZERO
    JGEZ = 0xC6, // JUMP_GREATER_EQUAL_ZERO
    JGZ  = 0xC7  // JUMP_GREATER_ZERO
} InstructionSet;

#define COPY_MODE 0x80
#define IMMEDIATE_MODE 0x00
#define IMMEDIATE(const) (IMMEDIATE_MODE + const)
#define MOV(source, dest) (((source << 3) + (dest)) | 128)

typedef struct Opcode {
    char *name;
    int value;

} Opcode;