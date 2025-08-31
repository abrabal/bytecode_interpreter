#include "vm.h"
#include "opcodes.h"
#include "errors.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_mode(int instruction, int mode);

SimStep step(SimStep sim_step)
{
    int instruction = sim_step.state->program[sim_step.instruction_pointer];
    int source;
    int dest;
    SimStep next_step = deep_copy(sim_step);
    next_step.instruction_pointer += 1;


    switch(instruction){
        case ADD:
            next_step.state->registers[3] = sim_step.state->registers[1] + sim_step.state->registers[2];
            free_step(sim_step);
            return next_step;

        case OR:
            next_step.state->registers[3] = sim_step.state->registers[1] | sim_step.state->registers[2];
            free_step(sim_step);
            return next_step;

        case NAND:
            next_step.state->registers[3] = ~(sim_step.state->registers[1] & sim_step.state->registers[2]);
            free_step(sim_step);
            return next_step;

        case NOR:
            next_step.state->registers[3] = ~(sim_step.state->registers[1] | sim_step.state->registers[2]);
            free_step(sim_step);
            return next_step;

        case AND:
            next_step.state->registers[3] = sim_step.state->registers[1] & sim_step.state->registers[2];
            free_step(sim_step);
            return next_step;

        case SUB:
            next_step.state->registers[3] = sim_step.state->registers[1] - sim_step.state->registers[2];
            free_step(sim_step);
            return next_step;


        case NOP:
            free_step(sim_step);
            return next_step;

        case JZ:
            if (next_step.state->registers[3] == 0){
                next_step.instruction_pointer = sim_step.state->registers[0];
                free_step(sim_step);
                return next_step;
            }
            free_step(sim_step);
            return next_step;

        case JLZ:
            if (next_step.state->registers[3] < 0){
                next_step.instruction_pointer = sim_step.state->registers[0];
                free_step(sim_step);
                return next_step;
            }
            free_step(sim_step);
            return next_step;

        case JLEZ:
            if (next_step.state->registers[3] <= 0){
                next_step.instruction_pointer = sim_step.state->registers[0];
                free_step(sim_step);
                return next_step;
            }
            free_step(sim_step);
            return next_step;

        case JUMP:
            next_step.instruction_pointer = sim_step.state->registers[0];
            free_step(sim_step);
            return next_step;

        case JNZ:
            if (next_step.state->registers[3] != 0){
                next_step.instruction_pointer = sim_step.state->registers[0];
                free_step(sim_step);
                return next_step;
            }
            free_step(sim_step);
            return next_step;

        case JGEZ:
            if (next_step.state->registers[3] >= 0){
                next_step.instruction_pointer = sim_step.state->registers[0];
                free_step(sim_step);
                return next_step;
            }
            free_step(sim_step);
            return next_step;

        case JGZ:
            if (next_step.state->registers[3] > 0){
                next_step.instruction_pointer = sim_step.state->registers[0];
                free_step(sim_step);
                return next_step;
            }
            free_step(sim_step);
            return next_step;
    }

    if(instruction < COPY_MODE && instruction > 63){
        next_step.error_code = error(ERROR_INVALID_INSTRUCTION, 0, 0, instruction);
        free_step(sim_step);
        return next_step;
    }

    if (is_mode(instruction, COPY_MODE)){
        source = (instruction >> 3) & 7;
        dest = (instruction & 7);

        if (source < MAX_NUM_OF_REGISTERS && dest < MAX_NUM_OF_REGISTERS){
            next_step.state->registers[dest] = sim_step.state->registers[source];
            free_step(sim_step);
            return next_step;
        }
        if (source == INPUT && dest == OUTPUT){
            next_step.output[sim_step.out_pointer] = sim_step.input[sim_step.inp_pointer];
            next_step.inp_pointer += 1;
            free_step(sim_step);
            return next_step;
        }
        if (source == INPUT && dest < MAX_NUM_OF_REGISTERS){
            next_step.state->registers[dest] = sim_step.input[sim_step.inp_pointer];
            next_step.inp_pointer += 1;
            free_step(sim_step);
            return next_step;
        }
        if (source < MAX_NUM_OF_REGISTERS && dest == OUTPUT){
            next_step.output[sim_step.out_pointer] = sim_step.state->registers[source];
            free_step(sim_step);
            return next_step;
        }

        next_step.error_code = error(ERROR_INVALID_REGISTER, source, dest, 0);
        free_step(sim_step);
        return next_step;
        

    } else if (is_mode(instruction, IMMEDIATE_MODE)){
        next_step.state->registers[0] = instruction;
        free_step(sim_step);
        return next_step;
    }

    

    next_step.error_code = UNEXPECTED_BEHAVIOR;
    free_step(sim_step);
    return next_step;
}

int is_mode(int instruction, int mode)
{
    return ((instruction >> 6) ^ (mode >> 6)) == 0;
}

SimStep deep_copy(SimStep sim_step)
{
    SimStep new_sim_step = make_clear_step(sim_step);

    memcpy(new_sim_step.state->program, sim_step.state->program, MAX_PROGRAM_LENGTH * sizeof(unsigned char));
    memcpy(new_sim_step.input, sim_step.input, MAX_SIZE_OF_INPUT_OUTPUT * sizeof(char));
    memcpy(new_sim_step.output, sim_step.output, MAX_SIZE_OF_INPUT_OUTPUT * sizeof(char));
    memcpy(new_sim_step.state->registers, sim_step.state->registers, MAX_NUM_OF_REGISTERS * sizeof(char));

    new_sim_step.inp_pointer = sim_step.inp_pointer;
    new_sim_step.out_pointer = sim_step.out_pointer;
    new_sim_step.instruction_pointer = sim_step.instruction_pointer;
    new_sim_step.error_code = sim_step.error_code;

    return new_sim_step;
}

SimStep make_clear_step()
{
    unsigned char *program = malloc(MAX_PROGRAM_LENGTH * sizeof(unsigned char));
    char *input = malloc(MAX_SIZE_OF_INPUT_OUTPUT * sizeof(char));
    char *output = malloc(MAX_SIZE_OF_INPUT_OUTPUT * sizeof(char));
    char *regs_arr = malloc(MAX_NUM_OF_REGISTERS * sizeof(char));

    memset(program, 0, MAX_PROGRAM_LENGTH * sizeof(unsigned char));
    memset(input, 0, MAX_SIZE_OF_INPUT_OUTPUT * sizeof(unsigned char));
    memset(output, 0, MAX_SIZE_OF_INPUT_OUTPUT * sizeof(char));
    memset(regs_arr, 0, MAX_NUM_OF_REGISTERS * sizeof(char));

    State *new_clear_state = malloc(sizeof(State));
    new_clear_state->program = program;
    new_clear_state->registers = regs_arr;

    SimStep new_clear_sim_step = {new_clear_state, 0, 0, 0, input, output, 0};

    return new_clear_sim_step;
}

void free_step(SimStep sim_step)
{
    free(sim_step.state->program);
    free(sim_step.state->registers);
    free(sim_step.input);
    free(sim_step.output);
    free(sim_step.state);
}