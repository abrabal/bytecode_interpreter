typedef struct Reg {
    char value;
    char mode;

} Reg;


typedef struct Program{
    unsigned char *prog_body;
    int prog_step;
} Program;


typedef struct State {
    Program *program;
    Reg *registers;
    char inp_mode;
    char out_mode;

} State;


typedef struct Sim_step {
    State *state;
    size_t inp_step;
    size_t out_step;
    char *input;
    char *output;

} Sim_step;


Sim_step step(Sim_step);
Sim_step get_operation(Sim_step);
void sim_log(Sim_step);
