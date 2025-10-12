#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "vm.h"
#include "code_parser.h"
#include "helpers.h"
#include "unity.h"

#define INPUT_LENGTH sizeof(input)/sizeof(input[0]) 
#define NUMBER_OF_STEPS_BEFORE_ABORTION 20000

static int verbosity_flag = 0;

static size_t step_num = 0;
static SimStep *sim_step = NULL;
static FILE *sim_info_output = NULL;
static FILE *source_code = NULL;

void setUp(void)
{
    sim_step = make_clear_step();

    step_num = 0;

    fseek(source_code, 0, SEEK_SET);

    compile_program(sim_step->state->program, source_code, MAX_PROGRAM_LENGTH);
}

void tearDown(void)
{
    free_step(sim_step);
}

void test_1(void)
{
    char valid_output = 127;
    char input = 0;
    char output = 0;

    fprintf(sim_info_output, "\n-------------test 1 init\n");

    for (; sim_step->instruction_pointer < MAX_PROGRAM_LENGTH; ){
        if (verbosity_flag != MUTE){
            sim_info(sim_step, sim_info_output, verbosity_flag, input, step_num);
        }

        sim_step = step(sim_step, sim_step, input);
        step_num += 1;  

        if(step_num > NUMBER_OF_STEPS_BEFORE_ABORTION){
            fprintf(stderr, "ERROR: program fell into infinite loop, forced exit");
            exit(1);
        } 

        if(sim_step->output_mode == 1){                  
            input = (sim_step->output[0] > valid_output) ? 1 : 0;

            if (sim_step->output[0] == valid_output){
                output = sim_step->output[0];
                sim_info(sim_step, sim_info_output, verbosity_flag, input, step_num);
                break;
            }
        }
    }
    TEST_ASSERT_EQUAL_MESSAGE(valid_output, output, "test_1 failed");
}

void test_2(void)
{
    char valid_output = -128;
    char input = 0;
    char output = 0;

    fprintf(sim_info_output, "\n-------------test 2 init\n");

    for (; sim_step->instruction_pointer < MAX_PROGRAM_LENGTH; ){
        if (verbosity_flag != MUTE){
            sim_info(sim_step, sim_info_output, verbosity_flag, input, step_num);
        }

        sim_step = step(sim_step, sim_step, input);
        step_num += 1;   

        if(step_num > NUMBER_OF_STEPS_BEFORE_ABORTION){
            fprintf(stderr, "ERROR: program fell into infinite loop, forced exit");
            exit(1);
        } 

        if(sim_step->output_mode == 1){                  
            input = (sim_step->output[0] > valid_output) ? 1 : 0;

            if (sim_step->output[0] == valid_output){
                output = sim_step->output[0];
                sim_info(sim_step, sim_info_output, verbosity_flag, input, step_num);
                break;
            }
        }
    }
    TEST_ASSERT_EQUAL_MESSAGE(valid_output, output, "test_2 failed");
}

void test_3(void)
{
    char valid_output = 56;
    char input = 0;
    char output = 0;

    fprintf(sim_info_output, "\n-------------test 3 init\n");

    for (; sim_step->instruction_pointer < MAX_PROGRAM_LENGTH; ){
        if (verbosity_flag != MUTE){
            sim_info(sim_step, sim_info_output, verbosity_flag, input, step_num);
        }

        sim_step = step(sim_step, sim_step, input);
        step_num += 1;   

        if(step_num > NUMBER_OF_STEPS_BEFORE_ABORTION){
            fprintf(stderr, "ERROR: program fell into infinite loop, forced exit");
            exit(1);
        } 

        if(sim_step->output_mode == 1){                  
            input = (sim_step->output[0] > valid_output) ? 1 : 0;

            if (sim_step->output[0] == valid_output){
                output = sim_step->output[0];
                sim_info(sim_step, sim_info_output, verbosity_flag, input, step_num);
                break;
            }
        }
    }
    TEST_ASSERT_EQUAL_MESSAGE(valid_output, output, "test_3 failed");
}

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

    source_code = fopen(argv[(argc - 1)], "r");

    if(source_code == NULL){
        fprintf(stderr, "\nERROR: source code file not found at path \"%s\"\n", argv[(argc - 1)]);
        return 1;
    }

    sim_info_output = fopen("tasks/task_2_find_match/sim_info.txt", "w");

    UNITY_BEGIN();
    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);

    fclose(source_code);
    fclose(sim_info_output);

    return UNITY_END();
    
}