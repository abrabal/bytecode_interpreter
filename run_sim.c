#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vm.h"
#include "code_parser.h"
#include "helpers.h"

static int log_flag = 0;

int main(int argc, char *argv[])
{
    if (argc <= 1){
        fprintf(stderr, "\nERROR: expected path to source code file as command line argument\n");
        return 1;
    }

    if (argc < 3){
        log_flag = NO_LOGS;

    } else if (strcmp("--info", argv[1]) == 0){
        log_flag = INFO;

    }else if (strcmp("--debug", argv[1]) == 0){
        log_flag = DEBUG;

    }else{
        fprintf(stderr, "\nERROR: unexpected flag \"%s\"", argv[1]);
        exit(1);
    }

    FILE *source_code = fopen(argv[(argc - 1)], "r");

    if(source_code == NULL){
        fprintf(stderr, "\nERROR: source code file not found at path \"%s\"\n", argv[1]);
        return 1;
    }

    SimStep *sim_step = make_clear_step();

    compile_program(sim_step->state->program, source_code, MAX_PROGRAM_LENGTH);

    fclose(source_code);

    FILE *log_output = fopen("logs.txt", "w");

    while(1){
        if (sim_step->instruction_pointer == MAX_PROGRAM_LENGTH){
            sim_step->instruction_pointer = 0;
        }

        printf("\nto execute whole program press \"e\", to execute one instruction press \"s\", to exit press \"q\"\n");
        char c;
        scanf(" %c", &c);

        if (c == 's'){
            if (log_flag != NO_LOGS){
                sim_log(sim_step, log_output, log_flag);
            }
            sim_step = step(sim_step, sim_step);
        }

        if (c == 'e'){
            for (; sim_step->instruction_pointer < MAX_PROGRAM_LENGTH; ){
                if (log_flag != NO_LOGS){
                    sim_log(sim_step, log_output, log_flag);
                }
                sim_step = step(sim_step, sim_step);
            }
        }

        if (c == 'q'){
            break;
        }
    }

    fclose(log_output);
    free_step(sim_step);

    return 0;
}