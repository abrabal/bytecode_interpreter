#include <stdio.h>
#include <string.h>
#include "opcodes.h"
#include "vm.h"
#include "third_party/unity/unity.h"
#include "helpers.h"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_immediate_instruction_1(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(25);

    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(25, test_value, "IMMEDIATE test failed");
}

void test_immediate_instruction_2(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(15);

    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->state->registers[0];

    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(15, test_value, "IMMEDIATE test failed");
}

void test_immediate_instruction_3(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(63);

    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->state->registers[0];

    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(63, test_value, "IMMEDIATE test failed");
}

void test_copy_instruction_1(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);

    sim_step = step(sim_step, sim_step, 33);
    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->state->registers[1];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "copy from reg0 to reg1 failed");
}

void test_copy_instruction_2(void)
{   
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 2);

    sim_step = step(sim_step, sim_step, 33);
    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->state->registers[2];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "copy from reg0 to reg2 failed");
}

void test_copy_instruction_3(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 3);

    sim_step = step(sim_step, sim_step, 33);
    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->state->registers[3];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "copy from reg0 to reg3 failed");
}

void test_copy_instruction_4(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 4);

    sim_step = step(sim_step, sim_step, 33);
    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->state->registers[4];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "copy from reg0 to reg4 failed");
}

void test_copy_instruction_5(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 5);

    sim_step = step(sim_step, sim_step, 33);
    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->state->registers[5];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "copy from reg0 to reg5 failed");
}

void test_copy_instruction_6(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, OUTPUT);

    sim_step = step(sim_step, sim_step, 33);
    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->output[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "copy from reg0 to output failed");
}

void test_copy_instruction_7(void)
{
    SimStep *sim_step = make_clear_step();
    
    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(INPUT, 0);

    sim_step = step(sim_step, sim_step, 33);
    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(33, test_value, "copy from input to reg0 failed");
}

void test_copy_instruction_8(void)
{
    SimStep *sim_step = make_clear_step();
    
    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(INPUT, OUTPUT);

    sim_step = step(sim_step, sim_step, 33);
    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->output[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(33, test_value, "copy from input to output failed");
}

void test_or_instruction(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(5);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = OR;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step, sim_step, 33);
    }

    int test_value = sim_step->state->registers[3];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(15, test_value, "OR test failed");
}

void test_nand_instruction(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(5);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = NAND;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step, sim_step, 33);
    }

    int test_value = sim_step->state->registers[3];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(-1, test_value, "NAND test failed");
}

void test_nor_instruction(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(5);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = NOR;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step, sim_step, 33);
    }

    int test_value = sim_step->state->registers[3];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(-16, test_value, "NOR test failed");
}

void test_and_instruction(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(5);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = AND;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step, sim_step, 33);
    }

    int test_value = sim_step->state->registers[3];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(0, test_value, "AND test failed");
}

void test_add_instruction(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(5);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = ADD;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step, sim_step, 33);
    }

    int test_value = sim_step->state->registers[3];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(15, test_value, "ADD test failed");
}

void test_sub_instruction(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(5);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = SUB;

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step, sim_step, 33);
    }

    int test_value = sim_step->state->registers[3];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(-5, test_value, "SUB test failed");
}

void test_nop_instruction(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = MOV(0, 2);
    sim_step->state->program[3] = NOP;
    sim_step->state->program[4] = SUB;
    sim_step->state->program[5] = IMMEDIATE(0);

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step, sim_step, 33);
    }

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(0, test_value, "NOP test failed");
}

void test_jz_instruction_1(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = MOV(0, 2);
    sim_step->state->program[3] = SUB;
    sim_step->state->program[4] = IMMEDIATE(0);
    sim_step->state->program[5] = JZ;
    sim_step->state->program[6] = IMMEDIATE(0);

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step, sim_step, 33);
    }  

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "JZ test failed");
}

void test_jz_instruction_2(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = MOV(0, 2);
    sim_step->state->program[3] = ADD;
    sim_step->state->program[4] = IMMEDIATE(0);
    sim_step->state->program[5] = JZ;
    sim_step->state->program[6] = IMMEDIATE(0);

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(0, test_value, "JZ test failed");
}

void test_jlz_instruction_1(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(20);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = SUB;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JLZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(20, test_value, "JLZ test failed");
}

void test_jlz_instruction_2(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = SUB;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JLZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(0, test_value, "JLZ test failed");
}

void test_jlez_instruction_1(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(20);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = SUB;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JLEZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(20, test_value, "JLEZ test failed");
}

void test_jlez_instruction_2(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = SUB;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JLEZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "JLEZ test failed");
}

void test_jlez_instruction_3(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = ADD;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JLEZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(0, test_value, "JLEZ test failed");
}

void test_jump_instruction(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = MOV(0, 2);
    sim_step->state->program[3] = IMMEDIATE(0);
    sim_step->state->program[4] = JUMP;
    sim_step->state->program[5] = IMMEDIATE(0);

    for(int i = 0; i < 6; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "JUMP test failed");
}

void test_jnz_instruction_1(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = MOV(0, 2);
    sim_step->state->program[3] = ADD;
    sim_step->state->program[4] = IMMEDIATE(0);
    sim_step->state->program[5] = JNZ;
    sim_step->state->program[6] = IMMEDIATE(0);

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "JNZ test failed");
}

void test_jnz_instruction_2(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = MOV(0, 2);
    sim_step->state->program[3] = SUB;
    sim_step->state->program[4] = IMMEDIATE(0);
    sim_step->state->program[5] = JNZ;
    sim_step->state->program[6] = IMMEDIATE(0);

    for(int i = 0; i < 7; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(0, test_value, "JNZ test failed");
}

void test_jgez_instruction_1(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(20);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = ADD;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JGEZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(20, test_value, "JGEZ test failed");
}

void test_jgez_instruction_2(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = SUB;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JGEZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(10, test_value, "JGEZ test failed");

}

void test_jgez_instruction_3(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(20);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = SUB;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JGEZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(0, test_value, "JGEZ test failed");
}

void test_jgz_instruction_1(void) 
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(20);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = ADD;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JGZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(20, test_value, "JGZ test failed");

}

void test_jgz_instruction_2(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = IMMEDIATE(10);
    sim_step->state->program[1] = MOV(0, 1);
    sim_step->state->program[2] = IMMEDIATE(10);
    sim_step->state->program[3] = MOV(0, 2);
    sim_step->state->program[4] = SUB;
    sim_step->state->program[5] = IMMEDIATE(2);
    sim_step->state->program[6] = JGZ;
    sim_step->state->program[7] = IMMEDIATE(0);

    for(int i = 0; i < 8; i++){
        sim_step = step(sim_step, sim_step, 33);
    }   

    int test_value = sim_step->state->registers[0];
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(0, test_value, "JGZ test failed");
}

void test_error_invalid_instruction(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = 70;

    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->error_code;
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(ERROR_INVALID_INSTRUCTION, test_value, "ERROR_INVALID_INSTRUCTION test failed");
}

void test_error_out_of_range(void)
{
    SimStep *sim_step = make_clear_step();
    

    sim_step->state->program[0] = 191;

    sim_step = step(sim_step, sim_step, 33);

    int test_value = sim_step->error_code;
    free_step(sim_step);

    TEST_ASSERT_EQUAL_MESSAGE(ERROR_INVALID_REGISTER, test_value, "ERROR_OUT_OF_RANGE test failed");
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