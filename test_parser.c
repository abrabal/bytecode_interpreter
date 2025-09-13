#include <stdio.h>
#include <stdlib.h>
#include "code_parser.h"
#include "vm.h"
#include "opcodes.h"

int main()
{
    SimStep *sim_step = make_clear_step();

    sim_step = generate_code(sim_step, "code.txt");

    free_step(sim_step);

    return 0;
}