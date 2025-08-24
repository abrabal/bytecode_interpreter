#include "vm.h"
#include "oppcodes.h"
#include <stdio.h>

int is_mode(int instruction, int mode);

SimStep step(SimStep sim_step)
{
    int instruction = sim_step.state->program->prog_body[sim_step.state->program->instruction_pointer];
    int source;
    int dest;

    switch(instruction){
        case ADD:
            sim_step.state->registers[3] = sim_step.state->registers[1] + sim_step.state->registers[2];
            break;

        case OR:
            sim_step.state->registers[3] = sim_step.state->registers[1] | sim_step.state->registers[2];
            break;

        case NAND:
            sim_step.state->registers[3] = ~(sim_step.state->registers[1] & sim_step.state->registers[2]);
            break;

        case NOR:
            sim_step.state->registers[3] = ~(sim_step.state->registers[1] | sim_step.state->registers[2]);
            break;

        case AND:
            sim_step.state->registers[3] = sim_step.state->registers[1] & sim_step.state->registers[2];
            break;

        case SUB:
            sim_step.state->registers[3] = sim_step.state->registers[1] - sim_step.state->registers[2];
            break;


        case NEVER:
            sim_step.state->program->instruction_pointer += 1;
            return sim_step;
            break;

        case EQUAL_ZERO:
            if (sim_step.state->registers[3] == 0){
                sim_step.state->program->instruction_pointer = sim_step.state->registers[0];
                step(sim_step);
            }
            break;

        case LESS_THEN_ZERO:
            if (sim_step.state->registers[3] < 0){
                sim_step.state->program->instruction_pointer = sim_step.state->registers[0];
                step(sim_step);
            }
            break;

        case LESS_EQUAL_ZERO:
            if (sim_step.state->registers[3] <= 0){
                sim_step.state->program->instruction_pointer = sim_step.state->registers[0];
                step(sim_step);
            }
            break;

        case ALWAYS:
            sim_step.state->program->instruction_pointer = sim_step.state->registers[0];
            step(sim_step);
            break;

        case NOT_EQUAL_ZERO:
            if (sim_step.state->registers[3] != 0){
                sim_step.state->program->instruction_pointer = sim_step.state->registers[0];
                step(sim_step);
            }
            break;

        case GREATER_EQUAL_THEN_ZERO:
            if (sim_step.state->registers[3] >= 0){
                sim_step.state->program->instruction_pointer = sim_step.state->registers[0];
                step(sim_step);
            }
            break;

        case GREATER_THEN_ZERO:
            if (sim_step.state->registers[3] > 0){
                sim_step.state->program->instruction_pointer = sim_step.state->registers[0];
                step(sim_step);
            }
            break;
    }
    if (is_mode(instruction, COPY_MODE)){
        source = (instruction >> 3) & 7;
        dest = (instruction & 7);
        sim_step.state->registers[dest] = sim_step.state->registers[source];

    } else if (is_mode(instruction, IMMEDIATE_MODE)){
        sim_step.state->registers[0] = instruction;
    }

    sim_step.state->program->instruction_pointer += 1;
    return sim_step;
}

int is_mode(int instruction, int mode)
{
    return ((instruction >> 6) ^ (mode >> 6)) == 0;
}