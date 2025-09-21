#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../code_parser.h"
#include "../vm.h"
#include "../opcodes.h"

int main()
{
    SimStep *sim_step = make_clear_step();

    compile_program(sim_step->state->program, "code.asm", MAX_PROGRAM_LENGTH);

    FILE *out = fopen("utilities/program.hex", "wb");

    fwrite(sim_step->state->program, sizeof(sim_step->state->program[0]), MAX_PROGRAM_LENGTH, out);

    free_step(sim_step);

    fclose(out);

    return 0;
}