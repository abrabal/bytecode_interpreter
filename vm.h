#pragma once
#include <stddef.h>

#define MAX_PROGRAM_LENGTH 256
#define MAX_NUM_OF_REGISTERS 6
#define MAX_SIZE_OF_OUTPUT 100
#define INPUT 6
#define OUTPUT 6

typedef enum ErrorCodes 
{
    ERROR_INVALID_REGISTER = - 1,
    ERROR_INVALID_INSTRUCTION = -2,
    UNEXPECTED_BEHAVIOR = -3

} ErrorCodes;

typedef struct State {
    unsigned char *program;
    char *registers;

} State;


typedef struct SimStep {
    State *state;
    size_t out_pointer;
    char *output;
    int instruction_pointer;
    int error_code;
    int input_mode;
    int output_mode;

} SimStep;


SimStep *step(SimStep *sim_step, SimStep *next_step, int input);
SimStep *deep_copy(SimStep *dest, SimStep *source);
SimStep *make_clear_step();
void free_step(SimStep *sim_step);