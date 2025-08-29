#pragma once
#include <stddef.h>

#define MAX_PROGRAM_LENGTH 256
#define MAX_NUM_OF_REGISTERS 6
#define MAX_SIZE_OF_INPUT_OUTPUT 100

typedef struct State {
    unsigned char *program;
    char *registers;

} State;


typedef struct SimStep {
    State *state;
    size_t inp_pointer;
    size_t out_pointer;
    int instruction_pointer;
    char *input;
    char *output;

} SimStep;


SimStep step(SimStep);
