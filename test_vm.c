#include <stdio.h>
#include <string.h>
#include "opcodes.h"
#include "vm.h"
#include "third_party/unity/unity.h"
#include "helpers.h"
#include "errors.h"

SimStep sim_step;

void setUp(void)
{

}

void tearDown(void)
{

}

void test_immediate_instruction_1(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(25);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(25, sim_step.state->registers[0], "IMMEDIATE test failed");
    free_step(sim_step);
}

void test_immediate_instruction_2(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(15);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(15, sim_step.state->registers[0], "IMMEDIATE test failed");
    free_step(sim_step);
}

void test_immediate_instruction_3(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(63);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(63, sim_step.state->registers[0], "IMMEDIATE test failed");
    free_step(sim_step);
}

void test_copy_instruction_1(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);

    sim_step = step(sim_step);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[1], "copy from reg0 to reg1 failed");
    free_step(sim_step);
}

void test_copy_instruction_2(void)
{   
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 2);

    sim_step = step(sim_step);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[2], "copy from reg0 to reg2 failed");
    free_step(sim_step);
}

void test_copy_instruction_3(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 3);

    sim_step = step(sim_step);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[3], "copy from reg0 to reg3 failed");
    free_step(sim_step);
}

void test_copy_instruction_4(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 4);

    sim_step = step(sim_step);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[4], "copy from reg0 to reg4 failed");
    free_step(sim_step);
}

void test_copy_instruction_5(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 5);

    sim_step = step(sim_step);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[5], "copy from reg0 to reg5 failed");
    free_step(sim_step);
}

void test_copy_instruction_6(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, OUTPUT);

    sim_step = step(sim_step);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.output[sim_step.out_pointer], "copy from reg0 to output failed");
    free_step(sim_step);
}

void test_copy_instruction_7(void)
{
    sim_step = make_clear_step();

    sim_step.input[0] = 33;
    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(INPUT, 0);

    sim_step = step(sim_step);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(33, sim_step.state->registers[sim_step.out_pointer], "copy from input to reg0 failed");
    free_step(sim_step);
}

void test_copy_instruction_8(void)
{
    sim_step = make_clear_step();

    sim_step.input[0] = 33;
    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(INPUT, OUTPUT);

    sim_step = step(sim_step);
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(33, sim_step.output[0], "copy from input to output failed");
    free_step(sim_step);
}

void test_or_instruction(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(5);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    sim_step.state->program[4] = OR;
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(15, sim_step.state->registers[3], "OR test failed");
    free_step(sim_step);

}

void test_nand_instruction(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(5);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    sim_step.state->program[4] = NAND;
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(-1, sim_step.state->registers[3], "NAND test failed");
    free_step(sim_step);
}

void test_nor_instruction(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(5);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    sim_step.state->program[4] = NOR;
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(-16, sim_step.state->registers[3], "NOR test failed");
    free_step(sim_step);
}

void test_and_instruction(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(5);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }
    sim_step.state->program[4] = AND;
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(0, sim_step.state->registers[3], "AND test failed");
    free_step(sim_step);
}

void test_add_instruction(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(5);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    sim_step.state->program[4] = ADD;
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(15, sim_step.state->registers[3], "ADD test failed");
    free_step(sim_step);
}

void test_sub_instruction(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(5);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);

    for(int i = 0; i < 4; i++){
        sim_step = step(sim_step);
    }

    sim_step.state->program[4] = SUB;
    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(-5, sim_step.state->registers[3], "SUB test failed");\
    free_step(sim_step);
}

void test_nop_instruction(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = MOV(0, 2);
    sim_step.state->program[3] = NOP;
    sim_step.state->program[4] = SUB;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
    }

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(0, sim_step.state->registers[3], "NOP test failed");
    free_step(sim_step);
}

void test_jz_instruction_1(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = MOV(0, 2);
    sim_step.state->program[3] = SUB;
    sim_step.state->program[4] = IMMEDIATE(0);
    sim_step.state->program[5] = JZ;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }  

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[0], "JZ test failed");
    free_step(sim_step);
}

void test_jz_instruction_2(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = MOV(0, 2);
    sim_step.state->program[3] = ADD;
    sim_step.state->program[4] = IMMEDIATE(0);
    sim_step.state->program[5] = JZ;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(0, sim_step.state->registers[0], "JZ test failed");
    free_step(sim_step);
}

void test_jlz_instruction_1(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(20);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = SUB;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JLZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(20, sim_step.state->registers[0], "JLZ test failed");
    free_step(sim_step);
}

void test_jlz_instruction_2(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = SUB;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JLZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(0, sim_step.state->registers[0], "JLZ test failed");
    free_step(sim_step);
}

void test_jlez_instruction_1(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(20);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = SUB;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JLEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(20, sim_step.state->registers[0], "JLEZ test failed");
    free_step(sim_step);

}

void test_jlez_instruction_2(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = SUB;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JLEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[0], "JLEZ test failed");
    free_step(sim_step);

}

void test_jlez_instruction_3(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = ADD;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JLEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(0, sim_step.state->registers[0], "JLEZ test failed");
    free_step(sim_step);
}

void test_jump_instruction(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = MOV(0, 2);
    sim_step.state->program[3] = IMMEDIATE(0);
    sim_step.state->program[4] = JUMP;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[0], "JUMP test failed");
    free_step(sim_step);
}

void test_jnz_instruction_1(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = MOV(0, 2);
    sim_step.state->program[3] = ADD;
    sim_step.state->program[4] = IMMEDIATE(0);
    sim_step.state->program[5] = JNZ;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[0], "JNZ test failed");
    free_step(sim_step);

}

void test_jnz_instruction_2(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = MOV(0, 2);
    sim_step.state->program[3] = SUB;
    sim_step.state->program[4] = IMMEDIATE(0);
    sim_step.state->program[5] = JNZ;

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(0, sim_step.state->registers[0], "JNZ test failed");
    free_step(sim_step);
}

void test_jgez_instruction_1(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(20);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = ADD;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JGEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(20, sim_step.state->registers[0], "JGEZ test failed");
    free_step(sim_step);

}

void test_jgez_instruction_2(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = SUB;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JGEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(10, sim_step.state->registers[0], "JGEZ test failed");
    free_step(sim_step);

}

void test_jgez_instruction_3(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(20);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = SUB;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JGEZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(0, sim_step.state->registers[0], "JGEZ test failed");
    free_step(sim_step);
}

void test_jgz_instruction_1(void) 
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(20);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = ADD;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JGZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(20, sim_step.state->registers[0], "JGZ test failed");
    free_step(sim_step);

}

void test_jgz_instruction_2(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = IMMEDIATE(10);
    sim_step.state->program[1] = MOV(0, 1);
    sim_step.state->program[2] = IMMEDIATE(10);
    sim_step.state->program[3] = MOV(0, 2);
    sim_step.state->program[4] = SUB;
    sim_step.state->program[5] = IMMEDIATE(2);
    sim_step.state->program[6] = JLZ;

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step);
    }   

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(0, sim_step.state->registers[0], "JGZ test failed");
    free_step(sim_step);
}

void test_error_invalid_instruction(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = 70;

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(ERROR_INVALID_INSTRUCTION, sim_step.error_code, "ERROR_INVALID_INSTRUCTION test failed");
    free_step(sim_step);
}

void test_error_out_of_range(void)
{
    sim_step = make_clear_step();

    sim_step.state->program[0] = 191;

    sim_step = step(sim_step);
    TEST_ASSERT_EQUAL_MESSAGE(ERROR_INVALID_REGISTER, sim_step.error_code, "ERROR_OUT_OF_RANGE test failed");
    free_step(sim_step);
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
    RUN_TEST(test_copy_instruction_6);
    RUN_TEST(test_copy_instruction_7);
    RUN_TEST(test_copy_instruction_8);
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
    RUN_TEST(test_error_invalid_instruction);
    RUN_TEST(test_error_out_of_range);
    return UNITY_END();
}