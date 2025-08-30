#include "vm.h"
#include "opcodes.h"
#include "errors.h"
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
            sim_step.instruction_pointer += 1;
            return sim_step;

        case OR:
            sim_step.state->registers[3] = sim_step.state->registers[1] | sim_step.state->registers[2];
            sim_step.instruction_pointer += 1;
            return sim_step;

        case NAND:
            sim_step.state->registers[3] = ~(sim_step.state->registers[1] & sim_step.state->registers[2]);
            sim_step.instruction_pointer += 1;
            return sim_step;

        case NOR:
            sim_step.state->registers[3] = ~(sim_step.state->registers[1] | sim_step.state->registers[2]);
            sim_step.instruction_pointer += 1;
            return sim_step;

        case AND:
            sim_step.state->registers[3] = sim_step.state->registers[1] & sim_step.state->registers[2];
            sim_step.instruction_pointer += 1;
            return sim_step;

        case SUB:
            sim_step.state->registers[3] = sim_step.state->registers[1] - sim_step.state->registers[2];
            sim_step.instruction_pointer += 1;
            return sim_step;


        case NOP:
            sim_step.instruction_pointer += 1;
            return sim_step;

        case JZ:
            if (sim_step.state->registers[3] == 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            sim_step.instruction_pointer += 1;
            return sim_step;

        case JLZ:
            if (sim_step.state->registers[3] < 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            sim_step.instruction_pointer += 1;
            return sim_step;

        case JLEZ:
            if (sim_step.state->registers[3] <= 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            sim_step.instruction_pointer += 1;
            return sim_step;

        case JUMP:
            sim_step.instruction_pointer = sim_step.state->registers[0];
            return sim_step;

        case JNZ:
            if (sim_step.state->registers[3] != 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            sim_step.instruction_pointer += 1;
            return sim_step;

        case JGEZ:
            if (sim_step.state->registers[3] >= 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            sim_step.instruction_pointer += 1;
            return sim_step;

        case JGZ:
            if (sim_step.state->registers[3] > 0){
                sim_step.instruction_pointer = sim_step.state->registers[0];
                return sim_step;
            }
            sim_step.instruction_pointer += 1;
            return sim_step;
    }

    if(instruction < COPY_MODE && instruction > 63){
        sim_step.error_code = error_handler(ERROR_INVALID_INSTRUCTION, 0, 0, instruction);
        return sim_step;
    }

    if (is_mode(instruction, COPY_MODE)){
        source = (instruction >> 3) & 7;
        dest = (instruction & 7);

        if (source < MAX_NUM_OF_REGISTERS && dest < MAX_NUM_OF_REGISTERS){
            sim_step.state->registers[dest] = sim_step.state->registers[source];
            sim_step.instruction_pointer += 1;
            return sim_step;
        }
        if (source == INPUT && dest == OUTPUT){
            sim_step.output[sim_step.out_pointer] = sim_step.input[sim_step.inp_pointer];
            sim_step.inp_pointer += 1;
            sim_step.out_pointer += 1;
            sim_step.instruction_pointer += 1;
            return sim_step;
        }
        if (source == INPUT && dest < MAX_NUM_OF_REGISTERS){
            sim_step.state->registers[dest] = sim_step.input[sim_step.inp_pointer];
            sim_step.instruction_pointer += 1;
            return sim_step;
        }
        if (source < MAX_NUM_OF_REGISTERS && dest == OUTPUT){
            sim_step.output[sim_step.out_pointer] = sim_step.state->registers[source];
            sim_step.instruction_pointer += 1;
            return sim_step;
        }

        sim_step.error_code = error_handler(ERROR_INVALID_REGISTER, source, dest, 0);
        return sim_step;
        

    } else if (is_mode(instruction, IMMEDIATE_MODE)){
        sim_step.state->registers[0] = instruction;
        sim_step.instruction_pointer += 1;
        return sim_step;
    }

    sim_step.error_code = UNEXPECTED_BEHAVIOR;
    return sim_step;
}

int is_mode(int instruction, int mode)
{
    return ((instruction >> 6) ^ (mode >> 6)) == 0;
}

