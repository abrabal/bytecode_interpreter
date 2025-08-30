#include <stdio.h>
#include "errors.h"
#include "vm.h"

int error_handler(int error, int source, int dest, int instruction)
{
    if (error == ERROR_INVALID_REGISTER){
        if (source > MAX_NUM_OF_REGISTERS){
            //fprintf(stderr, "\nERROR: MOV from %d register is impossible, %d register doesn't exist\n\n", source, source);
        }
        if (dest > MAX_NUM_OF_REGISTERS){
            //fprintf(stderr, "\nERROR: MOV to %d register is impossible, %d register doesn't exist\n\n", dest, dest);
        }
        return ERROR_INVALID_REGISTER;
    }
    if (error == ERROR_INVALID_INSTRUCTION){
        //fprintf(stderr, "\nERROR: %d instruction doesn't exist\n\n", instruction);
        return ERROR_INVALID_INSTRUCTION;
    }
}