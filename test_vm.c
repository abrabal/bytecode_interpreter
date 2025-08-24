#include <stdio.h>
#include <string.h>
#include "oppcodes.h"
#include "vm.h"
#include "third_party/unity/unity.h"

static unsigned char ram[MAX_PROGRAM_LENGTH] = {0}; 
static char input[MAX_SIZE_OF_INPUT_OUTPUT] = {0};
static char output[MAX_SIZE_OF_INPUT_OUTPUT] = {0};
static char regs_arr[MAX_NUM_OF_REGISTERS] = {0};
    
Program program = {ram, 0};
State state = {&program, regs_arr};
SimStep sim_step = {&state, 0, 0, input, output};

SimStep clear_program(SimStep);
void sim_log(SimStep);

void setUp(void)
{

}

void tearDown(void)
{

}

void test_immediate_instruction(void)
{
    sim_step = clear_program(sim_step);

    ram[0] = 25;
    TEST_ASSERT_EQUAL_MESSAGE(25, step(sim_step).state->registers[0], "IMMEDIATE test failed");
    ram[1] = 15;
    TEST_ASSERT_EQUAL_MESSAGE(15, step(sim_step).state->registers[0], "IMMEDIATE test failed");
    ram[2] = 63;
    TEST_ASSERT_EQUAL_MESSAGE(63, step(sim_step).state->registers[0], "IMMEDIATE test failed");
}

void test_copy_instruction(void)
{
    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 130;
    ram[3] = 131;
    ram[4] = 132;
    ram[5] = 133;

    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "copy from program to reg0 failed");
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[1], "copy from reg0 to reg1 failed");
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[2], "copy from reg0 to reg2 failed");
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[3], "copy from reg0 to reg3 failed");
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[4], "copy from reg0 to reg4 failed");
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[5], "copy from reg0 to reg5 failed");
}

void test_compute_mode_instructions(void)
{
    sim_step = clear_program(sim_step);

    ram[0] = 5;
    ram[1] = 129;
    ram[2] = 10;
    ram[3] = 130;

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    ram[4] = OR;
    TEST_ASSERT_EQUAL_MESSAGE(15, step(sim_step).state->registers[3], "OR test failed");

    ram[5] = NAND;
    TEST_ASSERT_EQUAL_MESSAGE(-1, step(sim_step).state->registers[3], "NAND test failed");

    ram[6] = NOR;
    TEST_ASSERT_EQUAL_MESSAGE(-16, step(sim_step).state->registers[3], "NOR test failed");

    ram[7] = AND;
    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[3], "AND test failed");

    ram[8] = ADD;
    TEST_ASSERT_EQUAL_MESSAGE(15, step(sim_step).state->registers[3], "ADD test failed");

    ram[9] = SUB;
    TEST_ASSERT_EQUAL_MESSAGE(-5, step(sim_step).state->registers[3], "SUB test failed");

}

void test_never_instruction(void) 
{
    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 130;
    ram[3] = NEVER;

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }   

    ram[4] = ADD;
    TEST_ASSERT_EQUAL_MESSAGE(20, step(sim_step).state->registers[3], "NEVER test failed");
}

void test_equal_zero_instruction(void) 
{
    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 130;
    ram[3] = SUB;
    ram[4] = 0;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
    }   

    ram[5] = EQUAL_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "first EQUAL_ZERO test failed");

    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 130;
    ram[3] = ADD;
    ram[4] = 0;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
    }   

    ram[5] = EQUAL_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[0], "second EQUAL_ZERO test failed");
}

void test_less_then_zero_instruction(void) 
{
    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 20;
    ram[3] = 130;
    ram[4] = SUB;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = LESS_THEN_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(20, step(sim_step).state->registers[0], "first LESS_THEN_ZERO test failed");

    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 10;
    ram[3] = 130;
    ram[4] = SUB;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = LESS_THEN_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(2, step(sim_step).state->registers[0], "second LESS_THEN_ZERO test failed");
}

void test_less_equal_zero_instruction(void) 
{
    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 20;
    ram[3] = 130;
    ram[4] = SUB;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = LESS_EQUAL_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(20, step(sim_step).state->registers[0], "first LESS_EQUAL_ZERO test failed");

    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 10;
    ram[3] = 130;
    ram[4] = SUB;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = LESS_EQUAL_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "second LESS_EQUAL_ZERO test failed");

    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 10;
    ram[3] = 130;
    ram[4] = ADD;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = LESS_EQUAL_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(2, step(sim_step).state->registers[0], "third LESS_EQUAL_ZERO test failed");
}

void test_always_instruction(void) 
{
    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 130;
    ram[3] = 0;

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }   

    ram[4] = ALWAYS;
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "ALWAYS test failed");
}

void test_not_equal_zero_instruction(void) 
{
    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 130;
    ram[3] = ADD;
    ram[4] = 0;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
    }   

    ram[5] = NOT_EQUAL_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "first NOT_EQUAL_ZERO test failed");

    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 130;
    ram[3] = SUB;
    ram[4] = 0;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
    }   

    ram[5] = NOT_EQUAL_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[0], "second NOT_EQUAL_ZERO test failed");
}

void test_greater_equal_zero_instruction(void) 
{
    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 20;
    ram[3] = 130;
    ram[4] = ADD;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = GREATER_EQUAL_THEN_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(20, step(sim_step).state->registers[0], "first GREATER_EQUAL_ZERO test failed");

    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 10;
    ram[3] = 130;
    ram[4] = SUB;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = GREATER_EQUAL_THEN_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "second GREATER_EQUAL_ZERO test failed");

    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 20;
    ram[3] = 130;
    ram[4] = SUB;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = GREATER_EQUAL_THEN_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(2, step(sim_step).state->registers[0], "third GREATER_EQUAL_ZERO test failed");
}

void test_greater_then_zero_instruction(void) 
{
    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 20;
    ram[3] = 130;
    ram[4] = ADD;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = GREATER_THEN_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(20, step(sim_step).state->registers[0], "first GREATER_THEN_ZERO test failed");

    sim_step = clear_program(sim_step);

    ram[0] = 10;
    ram[1] = 129;
    ram[2] = 10;
    ram[3] = 130;
    ram[4] = SUB;
    ram[5] = 2;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    ram[6] = LESS_THEN_ZERO;
    TEST_ASSERT_EQUAL_MESSAGE(2, step(sim_step).state->registers[0], "second GREATER_THEN_ZERO test failed");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_immediate_instruction);
    RUN_TEST(test_copy_instruction);
    RUN_TEST(test_compute_mode_instructions);
    RUN_TEST(test_never_instruction);
    RUN_TEST(test_equal_zero_instruction);
    RUN_TEST(test_less_then_zero_instruction);
    RUN_TEST(test_less_equal_zero_instruction);
    RUN_TEST(test_always_instruction);
    RUN_TEST(test_not_equal_zero_instruction);
    RUN_TEST(test_greater_equal_zero_instruction);
    RUN_TEST(test_greater_then_zero_instruction);
    return UNITY_END();
}

void sim_log(SimStep sim_step){

    printf("\nSIM_LAYOUT:\n\n");
    printf("program:\n");
    for (int i = 0; i < MAX_PROGRAM_LENGTH; i++){
        printf("%u ", sim_step.state->program->prog_body[i]);
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
}

SimStep clear_program(SimStep sim_step)
{
    for (int i = 0; i < MAX_PROGRAM_LENGTH; i++){
        sim_step.state->program->prog_body[i] = 0;
    }

    sim_step.state->program->instruction_pointer = 0;

    return sim_step;
}