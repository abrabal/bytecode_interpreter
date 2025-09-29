#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "code_parser.h"
#include "vm.h"
#include "opcodes.h"

int main(int argc, char *argv[])
{
    if (argc <= 1){
        fprintf(stderr, "\nERROR: expected path to source code file as command line argument\n");
        return 1;
    }

    FILE *source_code = fopen(argv[1], "r");

    if(source_code == NULL){
        fprintf(stderr, "\nERROR: source code file not found at path \"%s\"\n", argv[1]);
        return 1;
    }

    SimStep *sim_step = make_clear_step();

    compile_program(sim_step->state->program, source_code, MAX_PROGRAM_LENGTH);

    fclose(source_code);

    FILE *out = fopen("utilities/program.hex", "wb");

    fwrite(sim_step->state->program, sizeof(sim_step->state->program[0]), MAX_PROGRAM_LENGTH, out);

    free_step(sim_step);

    fclose(out);

    return 0;
}