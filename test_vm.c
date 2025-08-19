#include <stdio.h>
#include <string.h>
#include "oppcodes.h"
#include "vm.h"
#include "unity.h"

//enum RegStates {OFF = 0, SAVE = 1, LOAD = 2};

/*int main()
{

    unsigned char ram[MAX_PROGRAM_LENGTH] = {5, 129, 10, 130, 68}; 
    char input[MAX_SIZE_OF_INPUT_OUTPUT] = {5};
    char output[MAX_SIZE_OF_INPUT_OUTPUT] = {0};

    Reg reg = {0, OFF};
    Reg regs_arr[MAX_NUM_OF_REGISTERS] = {{0, OFF}, {0, OFF}, {0, OFF}, {0, OFF}, {0, OFF}, {0, OFF}};
    Program program = {ram, 0};
    State state = {&program, regs_arr, OFF, OFF};
    Sim_step sim_step = {&state, 0, 0, input, output};

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
        sim_log(sim_step);
    }

    return 0;
}*/

void setUp(void)
{

}

void tearDown(void)
{

}

void test_add_instruction(void)
{
    enum RegStates {OFF = 0, SAVE = 1, LOAD = 2};

    unsigned char ram[MAX_PROGRAM_LENGTH] = {5, 129, 10, 130, 68}; 
    char input[MAX_SIZE_OF_INPUT_OUTPUT] = {5};
    char output[MAX_SIZE_OF_INPUT_OUTPUT] = {0};

    Reg reg = {0, OFF};
    Reg regs_arr[MAX_NUM_OF_REGISTERS] = {{0, OFF}, {0, OFF}, {0, OFF}, {0, OFF}, {0, OFF}, {0, OFF}};
    Program program = {ram, 0};
    State state = {&program, regs_arr, OFF, OFF};
    Sim_step sim_step = {&state, 0, 0, input, output};

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
    }

    TEST_ASSERT_EQUAL(15, step(sim_step).state->registers[3].value);

}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_add_instruction);
    return UNITY_END();
}