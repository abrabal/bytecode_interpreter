#pragma once

#include <stdio.h>
#include "vm.h"

typedef enum VerbosityCodes
{
    MUTE = 0,
    MIN_VERBOSITY = 1,
    FULL_INFO = 2
} VerbosityCodes;

static inline void sim_info(SimStep *sim_step, FILE *sim_info_output, int log_flag, int input){

    if (sim_info_output == NULL){
        sim_info_output = stderr;
    }

    int instruction = (sim_step->instruction_pointer >= MAX_PROGRAM_LENGTH) ? 0 : sim_step->instruction_pointer;

    if (log_flag == FULL_INFO){
        fprintf(sim_info_output, "\n==================================================================");
        fprintf(sim_info_output, "\ninstruction: <0x%x>", sim_step->state->program[instruction]);
        fprintf(sim_info_output, "\nregisters: <%d> <%d> <%d> <%d> <%d> <%d>", sim_step->state->registers[0], sim_step->state->registers[1], sim_step->state->registers[2], sim_step->state->registers[3], sim_step->state->registers[4], sim_step->state->registers[5]);
        fprintf(sim_info_output, "\ninput: <%d>", input);
        fprintf(sim_info_output, "\noutput: <%d>", sim_step->output[sim_step->out_pointer]);
    }

    if (log_flag == MIN_VERBOSITY){
        fprintf(sim_info_output, "\noutput: <%d>", sim_step->output[sim_step->out_pointer]);
    }
}