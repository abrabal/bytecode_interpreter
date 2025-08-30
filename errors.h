#pragma once

typedef enum ErrorCodes 
{
    ERROR_INVALID_REGISTER = - 1,
    ERROR_INVALID_INSTRUCTION = -2,
    UNEXPECTED_BEHAVIOR = -3

} ErrorCodes;

int error_handler(int error, int source, int dest, int instruction);