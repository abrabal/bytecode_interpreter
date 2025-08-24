#include <stddef.h>

#define MAX_PROGRAM_LENGTH 256
#define MAX_NUM_OF_REGISTERS 6
#define MAX_SIZE_OF_INPUT_OUTPUT 100

typedef struct Program{
    unsigned char *prog_body;
    int instruction_pointer;
} Program;


typedef struct State {
    Program *program;
    char *registers;

} State;


typedef struct SimStep {
    State *state;
    size_t inp_pointer;
    size_t out_pointer;
    char *input;
    char *output;

} SimStep;


SimStep step(SimStep);
