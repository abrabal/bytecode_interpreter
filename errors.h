#ifndef ERROR
#define ERROR

#include <stdio.h>
#include "vm.h"

#define MUTE_ERRORS

typedef enum ErrorCodes 
{
    ERROR_INVALID_REGISTER = - 1,
    ERROR_INVALID_INSTRUCTION = -2,
    UNEXPECTED_BEHAVIOR = -3

} ErrorCodes;

static inline int error(int error, int source, int dest, int instruction)
{
    if (error == ERROR_INVALID_REGISTER){
        if (source > MAX_NUM_OF_REGISTERS){
            #ifndef MUTE_ERRORS
            fprintf(stderr, "\nERROR: MOV from %d register is impossible, %d register doesn't exist\n\n", source, source);
            #endif
        }
        if (dest > MAX_NUM_OF_REGISTERS){
            #ifndef MUTE_ERRORS
            fprintf(stderr, "\nERROR: MOV to %d register is impossible, %d register doesn't exist\n\n", dest, dest);
            #endif
        }
        return ERROR_INVALID_REGISTER;
    }
    if (error == ERROR_INVALID_INSTRUCTION){
        #ifndef MUTE_ERRORS
        fprintf(stderr, "\nERROR: %d instruction doesn't exist\n\n", instruction);
        #endif
        return ERROR_INVALID_INSTRUCTION;
    }
}
#endif