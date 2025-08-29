#include "vm.h"
#include "opcodes.h"
#include <stdio.h>

int is_mode(int instruction, int mode);

SimStep step(SimStep sim_step)
{
    int instruction = sim_step.state->program[sim_step.instruction_pointer];
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


        case NOP:
            sim_step.instruction_pointer += 1;
            return sim_step;
            break;

        case JZ:
            if (sim_step.state->registers[3] == 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            break;

        case JLZ:
            if (sim_step.state->registers[3] < 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            break;

        case JLEZ:
            if (sim_step.state->registers[3] <= 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            break;

        case JUMP:
            sim_step.instruction_pointer = sim_step.state->registers[0];
            return sim_step;
            break;

        case JNZ:
            if (sim_step.state->registers[3] != 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            break;

        case JGEZ:
            if (sim_step.state->registers[3] >= 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            break;

        case JGZ:
            if (sim_step.state->registers[3] > 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
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

    sim_step.instruction_pointer += 1;
    return sim_step;
}

int is_mode(int instruction, int mode)
{
    return ((instruction >> 6) ^ (mode >> 6)) == 0;
}