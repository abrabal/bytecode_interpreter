#include <stdio.h>
#include <string.h>
#include "opcodes.h"
#include "vm.h"
#include "third_party/unity/unity.h"
#include "helpers.h"

static unsigned char program[MAX_PROGRAM_LENGTH] = {0}; 
static char input[MAX_SIZE_OF_INPUT_OUTPUT] = {0};
static char output[MAX_SIZE_OF_INPUT_OUTPUT] = {0};
static char regs_arr[MAX_NUM_OF_REGISTERS] = {0};
    
State state = {program, regs_arr};
SimStep sim_step = {&state, 0, 0, 0, input, output};

void setUp(void)
{

}

void tearDown(void)
{

}

void test_immediate_instruction_1(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(25);
    TEST_ASSERT_EQUAL_MESSAGE(25, step(sim_step).state->registers[0], "IMMEDIATE test failed");
}

void test_immediate_instruction_2(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(15);
    TEST_ASSERT_EQUAL_MESSAGE(15, step(sim_step).state->registers[0], "IMMEDIATE test failed");
}

void test_immediate_instruction_3(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(63);
    TEST_ASSERT_EQUAL_MESSAGE(63, step(sim_step).state->registers[0], "IMMEDIATE test failed");
}

void test_copy_instruction_1(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[1], "copy from reg0 to reg1 failed");
}

void test_copy_instruction_2(void)
{   
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 2);

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[2], "copy from reg0 to reg2 failed");
}

void test_copy_instruction_3(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 3);

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[3], "copy from reg0 to reg3 failed");
}

void test_copy_instruction_4(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 4);

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[4], "copy from reg0 to reg4 failed");
}

void test_copy_instruction_5(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 5);

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[5], "copy from reg0 to reg5 failed");
}

void test_or_instruction(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(5);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    program[4] = OR;
    TEST_ASSERT_EQUAL_MESSAGE(15, step(sim_step).state->registers[3], "OR test failed");

}

void test_nand_instruction(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(5);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    program[4] = NAND;
    TEST_ASSERT_EQUAL_MESSAGE(-1, step(sim_step).state->registers[3], "NAND test failed");
}

void test_nor_instruction(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(5);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    program[4] = NOR;
    TEST_ASSERT_EQUAL_MESSAGE(-16, step(sim_step).state->registers[3], "NOR test failed");
}

void test_and_instruction(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(5);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }
    program[4] = AND;
    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[3], "AND test failed");
}

void test_add_instruction(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(5);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    program[4] = ADD;
    TEST_ASSERT_EQUAL_MESSAGE(15, step(sim_step).state->registers[3], "ADD test failed");
}

void test_sub_instruction(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(5);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    program[4] = SUB;
    TEST_ASSERT_EQUAL_MESSAGE(-5, step(sim_step).state->registers[3], "SUB test failed");
}

void test_nop_instruction(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = MOV(0, 2);
    program[3] = NOP;
    program[4] = SUB;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[3], "NOP test failed");
}

void test_jz_instruction_1(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = MOV(0, 2);
    program[3] = SUB;
    program[4] = IMMEDIATE(0);
    program[5] = JZ;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "JZ test failed");
}

void test_jz_instruction_2(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = MOV(0, 2);
    program[3] = ADD;
    program[4] = IMMEDIATE(0);
    program[5] = JZ;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[0], "JZ test failed");
}

void test_jlz_instruction_1(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(20);
    program[3] = MOV(0, 2);
    program[4] = SUB;
    program[5] = IMMEDIATE(2);
    program[6] = JLZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(20, step(sim_step).state->registers[0], "JLZ test failed");
}

void test_jlz_instruction_2(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);
    program[4] = SUB;
    program[5] = IMMEDIATE(2);
    program[6] = JLZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[0], "JLZ test failed");
}

void test_jlez_instruction_1(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(20);
    program[3] = MOV(0, 2);
    program[4] = SUB;
    program[5] = IMMEDIATE(2);
    program[6] = JLEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(20, step(sim_step).state->registers[0], "JLEZ test failed");

}

void test_jlez_instruction_2(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);
    program[4] = SUB;
    program[5] = IMMEDIATE(2);
    program[6] = JLEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "JLEZ test failed");

}

void test_jlez_instruction_3(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);
    program[4] = ADD;
    program[5] = IMMEDIATE(2);
    program[6] = JLEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[0], "JLEZ test failed");
}

void test_jump_instruction(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = MOV(0, 2);
    program[3] = IMMEDIATE(0);
    program[4] = JUMP;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "JUMP test failed");
}

void test_jnz_instruction_1(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = MOV(0, 2);
    program[3] = ADD;
    program[4] = IMMEDIATE(0);
    program[5] = JNZ;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "JNZ test failed");

}

void test_jnz_instruction_2(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = MOV(0, 2);
    program[3] = SUB;
    program[4] = IMMEDIATE(0);
    program[5] = JNZ;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[0], "JNZ test failed");
}

void test_jgez_instruction_1(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(20);
    program[3] = MOV(0, 2);
    program[4] = ADD;
    program[5] = IMMEDIATE(2);
    program[6] = JGEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(20, step(sim_step).state->registers[0], "JGEZ test failed");

}

void test_jgez_instruction_2(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);
    program[4] = SUB;
    program[5] = IMMEDIATE(2);
    program[6] = JGEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(10, step(sim_step).state->registers[0], "JGEZ test failed");

}

void test_jgez_instruction_3(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(20);
    program[3] = MOV(0, 2);
    program[4] = SUB;
    program[5] = IMMEDIATE(2);
    program[6] = JGEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[0], "JGEZ test failed");
}

void test_jgz_instruction_1(void) 
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(20);
    program[3] = MOV(0, 2);
    program[4] = ADD;
    program[5] = IMMEDIATE(2);
    program[6] = JGZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(20, step(sim_step).state->registers[0], "JGZ test failed");

}

void test_jgz_instruction_2(void)
{
    sim_step = clear_program(sim_step);

    program[0] = IMMEDIATE(10);
    program[1] = MOV(0, 1);
    program[2] = IMMEDIATE(10);
    program[3] = MOV(0, 2);
    program[4] = SUB;
    program[5] = IMMEDIATE(2);
    program[6] = JLZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    TEST_ASSERT_EQUAL_MESSAGE(0, step(sim_step).state->registers[0], "JGZ test failed");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_immediate_instruction_1);
    RUN_TEST(test_immediate_instruction_2);
    RUN_TEST(test_immediate_instruction_3);
    RUN_TEST(test_copy_instruction_1);
    RUN_TEST(test_copy_instruction_2);
    RUN_TEST(test_copy_instruction_3);
    RUN_TEST(test_copy_instruction_4);
    RUN_TEST(test_copy_instruction_5);
    RUN_TEST(test_or_instruction);
    RUN_TEST(test_nand_instruction);
    RUN_TEST(test_nor_instruction);
    RUN_TEST(test_and_instruction);
    RUN_TEST(test_add_instruction);
    RUN_TEST(test_sub_instruction);
    RUN_TEST(test_nop_instruction);
    RUN_TEST(test_jz_instruction_1);
    RUN_TEST(test_jz_instruction_2);
    RUN_TEST(test_jlz_instruction_1);
    RUN_TEST(test_jlz_instruction_2);
    RUN_TEST(test_jlez_instruction_1);
    RUN_TEST(test_jlez_instruction_2);
    RUN_TEST(test_jlez_instruction_3);
    RUN_TEST(test_jump_instruction);
    RUN_TEST(test_jnz_instruction_1);
    RUN_TEST(test_jnz_instruction_2);
    RUN_TEST(test_jgez_instruction_1);
    RUN_TEST(test_jgez_instruction_2);
    RUN_TEST(test_jgez_instruction_3);
    RUN_TEST(test_jgz_instruction_1);
    RUN_TEST(test_jgz_instruction_2);
    return UNITY_END();
}

void sim_log(SimStep sim_step){

    printf("\nSIM_LAYOUT:\n\n");
    printf("program:\n");
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

SimStep clear_program(SimStep sim_step)
{
    for (int i = 0; i < MAX_PROGRAM_LENGTH; i++){
        sim_step.state->program[i] = 0;
    }

    for(int i = 0; i < MAX_NUM_OF_REGISTERS; i++){
        sim_step.state->registers[i] = 0;
    }

    sim_step.instruction_pointer = 0;

    return sim_step;
}