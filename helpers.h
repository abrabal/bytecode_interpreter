#pragma once

#include <stdio.h>
#include "vm.h"

typedef enum LogCodes
{
    NO_LOGS = 0,
    INFO = 1,
    DEBUG = 2
} LogCodes;

static inline void sim_log(SimStep *sim_step, FILE *log_output, int log_flag){

    if (log_output == NULL){
        log_output = stderr;
    }

    if (log_flag == DEBUG){
        fprintf(log_output, "\n==================================================================");
        fprintf(log_output, "\ninstruction: <%d>", sim_step->state->program[sim_step->instruction_pointer]);
        fprintf(log_output, "\nregisters: <%d> <%d> <%d> <%d> <%d> <%d>", sim_step->state->registers[0], sim_step->state->registers[1], sim_step->state->registers[2], sim_step->state->registers[3], sim_step->state->registers[4], sim_step->state->registers[5]);
        fprintf(log_output, "\ninput: <%d>", sim_step->input[sim_step->inp_pointer]);
        fprintf(log_output, "\noutput: <%d>", sim_step->output[sim_step->out_pointer]);
    }

    if (log_flag == INFO){
        fprintf(log_output, "\noutput: <%d>", sim_step->output[sim_step->out_pointer]);
    }
}