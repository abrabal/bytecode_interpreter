#include <stdio.h>
#include <string.h>
#include "vm.h"
enum Reg_states {OFF = 0, SAVE = 1, LOAD = 2};
enum Global_ins_mode {IMMEDIATE = 0x0, COMPUTE = 0x1, COPY = 0x2, COND = 0x3};
enum Local_compute_mode {OR = 0x0, NAND = 0x1, NOR = 0x2, AND = 0x3, ADD = 0x4, SUB = 0x5};
#define RAM_SIZE 256
#define REG_NUM 6
#define MAX_I_O 100
#define INS_NUM 4
#define COMP_INS_NUM 6

enum Global_ins_mode ins_mode[INS_NUM] = {IMMEDIATE, COMPUTE, COPY, COND};
enum Local_compute_mode comp_mode[COMP_INS_NUM] = {OR, NAND, NOR, AND, ADD, SUB};

int main()
{
    Reg reg;
    Program program;
    State state;
    Sim_step sim_step;

    unsigned char ram[RAM_SIZE] = {5, 129, 10, 130, 68}; 
    Reg regs_arr[REG_NUM];
    char input[MAX_I_O] = {5};
    char output[MAX_I_O] = {0};

    reg.mode = OFF;
    reg.value = 0;

    program.prog_body = ram;
    program.prog_step = 0;

    state.program = &program;
    state.registers = regs_arr;
    state.inp_mode = OFF;
    state.out_mode = OFF;

    sim_step.state = &state;
    sim_step.inp_step = 0;
    sim_step.out_step = 0;
    sim_step.input = input;
    sim_step.output = output;

    for (int i = 0; i < REG_NUM; i++){
        regs_arr[i] = reg;
    };

    for(int i = 0; i < 5; i++){
        sim_step = step(sim_step);
        sim_log(sim_step);
    }

    return 0;
}

void sim_log(Sim_step sim_step){

    printf("\nSIM_LAYOUT:\n\n");
    printf("program:\n");
    for (int i = 0; i < RAM_SIZE; i++){
        printf("%u ", sim_step.state->program->prog_body[i]);
    }
    printf("\n\n");
    printf("registers:\n\n");
    for (int i = 0; i < REG_NUM; i++){
        printf("reg %d:\nvalue = %d\nmode = %d\n", i, sim_step.state->registers[i].value, sim_step.state->registers[i].mode);
        printf("\n");
    }/*
    printf("I/O:\n\n");
    printf("input mode: %d\n", sim_step.state->inp_mode);
    printf("input step: %lu\n", sim_step.inp_step);
    printf("inputs arr:\n");
    for(int i = 0; i < MAX_I_O; i++){
        printf("%d ", sim_step.input[i]);
    }
    printf("\n\n");
    printf("output mode: %d\n", sim_step.state->out_mode);
    printf("output step: %lu\n", sim_step.out_step);
    printf("outputs arr:\n");
    for(int i = 0; i < MAX_I_O; i++){
        printf("%d ", sim_step.output[i]);
    }
    printf("\n\n");
    */
}

Sim_step step(Sim_step sim_step)
{
    get_operation(sim_step);
    sim_step.state->program->prog_step += 1;

}

Sim_step get_operation(Sim_step sim_step)
{
    int instruction = sim_step.state->program->prog_body[sim_step.state->program->prog_step];
    printf("\n-------------------------------------");
        printf("\ninstruction = %d", instruction);
        printf("\n-------------------------------------");
    int global_ins_flag;
    int local_ins_flag;
    int source;
    int dest;

    for (int i = 0; i < INS_NUM; i++){
        if (((instruction >> 6) ^ ins_mode[i]) == 0){
            global_ins_flag = ins_mode[i];
            break;
        };
    }
        printf("\n-------------------------------------");
        printf("\n%d", global_ins_flag);
        printf("\n-------------------------------------");
    switch(global_ins_flag){
        case COMPUTE:
            for(int i = 0; i < COMP_INS_NUM; i++){
                if (((instruction & 7) ^ comp_mode[i]) == 0){
                    local_ins_flag = comp_mode[i];
                    printf("\n-------------------------------------");
                    printf("\n%d", local_ins_flag);
                    printf("\n-------------------------------------");
                    break;
                }
            }
            break;
        case COPY:
            source = (instruction >> 3) & 7;
            dest = instruction & 7;
            sim_step.state->registers[dest].value = sim_step.state->registers[source].value;
            break;
        case IMMEDIATE:
            sim_step.state->registers[0].value = instruction;
            break;
        default:
            break;
    }

    switch(local_ins_flag){
        case ADD:
            sim_step.state->registers[3].value = sim_step.state->registers[1].value + sim_step.state->registers[2].value;
            break;
        default:
            break;
    }
    return sim_step;

}