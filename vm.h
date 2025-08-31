#pragma once
#include <stddef.h>

#define MAX_PROGRAM_LENGTH 256
#define MAX_NUM_OF_REGISTERS 6
#define MAX_SIZE_OF_INPUT_OUTPUT 100
#define INPUT 6
#define OUTPUT 6

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
    int error_code;

} SimStep;


SimStep step(SimStep);
SimStep deep_copy(SimStep);
SimStep make_clear_step();
void free_step(SimStep sim_step);