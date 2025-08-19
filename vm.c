#include "vm.h"
#include "oppcodes.h"
#include <stdio.h>

#define COPY_MODE 128
#define IMMEDIATE_MODE 0

int is_mode(int instruction, int mode);

void sim_log(Sim_step sim_step){

    printf("\nSIM_LAYOUT:\n\n");
    printf("program:\n");
    for (int i = 0; i < MAX_PROGRAM_LENGTH; i++){
        printf("%u ", sim_step.state->program->prog_body[i]);
    }
    printf("\n\n");
    printf("registers:\n\n");
    for (int i = 0; i < MAX_NUM_OF_REGISTERS; i++){
        printf("reg %d:\nvalue = %d\nmode = %d\n", i, sim_step.state->registers[i].value, sim_step.state->registers[i].mode);
        printf("\n");
    }
    /*printf("I/O:\n\n");
    printf("input mode: %d\n", sim_step.state->inp_mode);
    printf("input step: %lu\n", sim_step.inp_pointer);
    printf("inputs arr:\n");
    for(int i = 0; i < MAX_SIZE_OF_INPUT_OUTPUT; i++){
        printf("%d ", sim_step.input[i]);
    }
    printf("\n\n");
    printf("output mode: %d\n", sim_step.state->out_mode);
    printf("output step: %lu\n", sim_step.out_pointer);
    printf("outputs arr:\n");
    for(int i = 0; i < MAX_SIZE_OF_INPUT_OUTPUT; i++){
        printf("%d ", sim_step.output[i]);
    }
    printf("\n\n");*/
}

Sim_step step(Sim_step sim_step)
{
    int instruction = sim_step.state->program->prog_body[sim_step.state->program->instruction_pointer];
    int source;
    int dest;

    switch(instruction){
        case ADD:
            sim_step.state->registers[3].value = sim_step.state->registers[1].value + sim_step.state->registers[2].value;
            break;
    }
    if (is_mode(instruction, COPY_MODE)){
        source = (instruction >> 3) & 7;
        dest = instruction & 7;
        sim_step.state->registers[dest].value = sim_step.state->registers[source].value;

    } else if (is_mode(instruction, IMMEDIATE_MODE)){
        sim_step.state->registers[0].value = instruction;
    }

    sim_step.state->program->instruction_pointer += 1;
    return sim_step;
}

int is_mode(int instruction, int mode)
{
    return ((instruction >> 6) ^ mode >> 6) == 0;
}