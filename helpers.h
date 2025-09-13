#pragma once

#include <stdio.h>
#include "vm.h"


void sim_log(SimStep);


void sim_log(SimStep sim_step){

    printf("\nSIM_LAYOUT:\n\n");
    printf("sim_step.state->program:\n");
    for (int i = 0; i < MAX_PROGRAM_LENGTH; i++){
        printf("%u ", sim_step.state->program[i]);
    }
    printf("\n\n");
    printf("registers:\n\n");
    for (int i = 0; i < MAX_NUM_OF_REGISTERS; i++){
        printf("reg %d:\nvalue = %d\n", i, sim_step.state->registers[i]);
        printf("\n");
    }
    printf("I/O:\n\n");
    printf("input step: %lu\n", sim_step.inp_pointer);
    printf("inputs arr:\n");
    for(int i = 0; i < MAX_SIZE_OF_INPUT_OUTPUT; i++){
        printf("%d ", sim_step.input[i]);
    }
    printf("\n\n");
    printf("output step: %lu\n", sim_step.out_pointer);
    printf("outputs arr:\n");
    for(int i = 0; i < MAX_SIZE_OF_INPUT_OUTPUT; i++){
        printf("%d ", sim_step.output[i]);
    }
    printf("\n\n");
    printf("instruction pointer = %d", sim_step.instruction_pointer);
    printf("\n\n");
}