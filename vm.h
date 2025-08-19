#include <stddef.h>

#define MAX_PROGRAM_LENGTH 256
#define MAX_NUM_OF_REGISTERS 6
#define MAX_SIZE_OF_INPUT_OUTPUT 100

typedef struct Reg {
    char value;
    char mode;

} Reg;


typedef struct Program{
    unsigned char *prog_body;
    int instruction_pointer;
} Program;


typedef struct State {
    Program *program;
    Reg *registers;
    char inp_mode;
    char out_mode;

} State;


typedef struct Sim_step {
    State *state;
    size_t inp_pointer;
    size_t out_pointer;
    char *input;
    char *output;

} Sim_step;


Sim_step step(Sim_step);
void sim_log(Sim_step);
