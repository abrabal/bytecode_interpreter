#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "vm.h"
#include "code_parser.h"
#include "helpers.h"

#define INPUT_LENGTH sizeof(input)/sizeof(input[0]) 

static int verbosity_flag = 0;

static int input[] = {0, 1};
static int input_pointer = 0;
static int test_res = -128;

int main(int argc, char *argv[])
{
    if (argc <= 1){
        fprintf(stderr, "\nERROR: expected path to source code file as command line argument\n");
        return 1;
    }

    if (argc < 3){
        verbosity_flag = MUTE;

    } else if (strcmp("--verbose", argv[1]) == 0){

        if (!(isdigit(*argv[2]))){
            fprintf(stderr, "\nERROR: unexpected flag \"%s\"", argv[2]);
            exit(1);
        }

        verbosity_flag = atoi(argv[2]);

        if (verbosity_flag < 0 || verbosity_flag > 2){
            fprintf(stderr, "\n<%d> verbosity value is not exist", verbosity_flag);
            exit(1);
        }
    } else {
        fprintf(stderr, "unexpected flag \"%s\"", argv[1]);
        exit(1);
    }

    FILE *source_code = fopen(argv[(argc - 1)], "r");

    if(source_code == NULL){
        fprintf(stderr, "\nERROR: source code file not found at path \"%s\"\n", argv[(argc - 1)]);
        return 1;
    }

    SimStep *sim_step = make_clear_step();

    compile_program(sim_step->state->program, source_code, MAX_PROGRAM_LENGTH);

    fclose(source_code);

    FILE *sim_info_output = fopen("sim_info.txt", "w");

    while(1){
        printf("\nto execute whole program press \"e\", to execute one instruction press \"s\", to exit press \"q\"\n");
        char c;
        scanf(" %c", &c);

        if (c == 's'){
            if (verbosity_flag != MUTE){
                sim_info(sim_step, sim_info_output, verbosity_flag, input[input_pointer]);
            }
            sim_step = step(sim_step, sim_step, input[input_pointer]);

            if (sim_step->output_mode == 1){
                input_pointer = (sim_step->output[0] > test_res) ? 1 : 0;
                if (sim_step->output[0] == test_res){
                    printf("\ntest passed");
                    exit(0);
                }
            }
        }

        if (c == 'e'){
            for (; sim_step->instruction_pointer < MAX_PROGRAM_LENGTH; ){
                if (verbosity_flag != MUTE){
                    sim_info(sim_step, sim_info_output, verbosity_flag, input[input_pointer]);
                }
                sim_step = step(sim_step, sim_step, input[input_pointer]);

                if (sim_step->output_mode == 1){
                    input_pointer = (sim_step->output[0] > test_res) ? 1 : 0;
                    if (sim_step->output[0] == test_res){
                        printf("\ntest passed\n");
                        exit(0);
                    }
            }
            }
        }

        if (c == 'q'){
            break;
        }
    }

    fclose(sim_info_output);
    free_step(sim_step);

    return 0;
}