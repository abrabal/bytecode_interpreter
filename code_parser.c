#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "code_parser.h"
#include "opcodes.h"
#include "vm.h"

#define NUM_OF_OPCODES sizeof(opcodes_for_parser)/sizeof(Opcode)

static Opcode opcodes_for_parser[] =
{
    {"add", 68},
    {"and", 67},
    {"immediate", 0},
    {"jgez", 198},
    {"jgz", 199},
    {"jlez", 195},
    {"jlz", 194},
    {"jnz", 197},
    {"jump", 196},
    {"jz", 193},
    {"nand", 65},
    {"nop", 192},
    {"nor", 66},
    {"or", 64},
    {"sub", 69}
};

static char buf[BUFSIZE];
static int bufp = 0;
static int instruction_stack[20];
static int instruction_stack_pointer = 0;

SimStep *generate_code(SimStep *sim_step, char *source_code_file)
{
    FILE *source_code = fopen(source_code_file, "r");
    char token_name[MAX_TOKEN_NAME];
    int instruction_counter = 0;
    char operation_flag = 0;

    while (1){
        int c = get_token(token_name, source_code);

        if (is_operator(c)){
            operation_flag = c;
            continue;
        }

        if (isalpha(token_name[0])){
            for (unsigned long int i = 0; i < NUM_OF_OPCODES; i++){
                if (strcmp(token_name, opcodes_for_parser[i].name) == 0){
                    push(opcodes_for_parser[i].value);
                    break;
                }
            }
        }

        if(isdigit(token_name[0])){
            push(atoi(token_name));
        }

        if (c == ';'){
            instruction_counter += 1;
            switch(operation_flag){
                case '+':
                    printf("\ninstruction = %d\n", pop() + pop());
                    break;
                case '-':
                    break;
                case '*':
                    printf("instruction = %d\n", pop() * pop());
                    break;
                case '/':
                    break;
                case '|':
                    printf("\ninstruction = %d\n", pop() | pop());
                    break;
                case '&':
                    printf("instruction = %d\n", pop() & pop());
                    break;
                default:
                    printf("instruction = %d", pop());
                    break;
        }
            operation_flag = 0;
        }

        if (c == EOF){
            break;
        }
    }
    printf("\nnumber of instructions = %d\n", instruction_counter);

    fclose(source_code);
    return sim_step;
}

int get_token(char *token_name, FILE *source_code)
{
    int c = fgetc(source_code);
    memset (token_name, 0, sizeof(char) * MAX_TOKEN_NAME);

    c = skip_whitespace(source_code, c);
    
    if (c == '/'){
        c = skip_comments(source_code);
        c = skip_whitespace(source_code, c);
    }
    
    if (is_operator(c)){
        return c;
    }

    while (isalnum(c)){
        *token_name = c;
        token_name++;
        c = fgetc(source_code);
    }

    token_name = '\0';
    if (c != ';'){
        ungetch(c);
    }
    return c;
}

int skip_comments(FILE *source_code){
    int c = fgetc(source_code);

    switch(c){
        case '/':
            while(1){
                c = fgetc(source_code);
                if (c == '\n' || c == EOF){
                    break;
                }
            }
            break;
        case '*':
            while (1){
                c = fgetc(source_code);
                if (c == '*'){
                    c = fgetc(source_code);
                    if (c == '/'){
                        c = fgetc(source_code);
                        break;
                    }
                }
            }
            break;
    }

    return c;
}

int skip_whitespace(FILE *source_code, int c){
    
    while (isspace(c)){
        c = fgetc(source_code);
    }

    return c;
}

int is_operator(int c)
{
    switch(c){
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 1;
        case '/':
            return 1;
        case '|':
            return 1;
        case '&':
            return 1;
    }
    
    return 0;
}

int fgetch(FILE *source_code)
{
    return (bufp > 0) ? buf[--bufp] : fgetc(source_code);
}

void ungetch(int c)
{
        buf[bufp++] = c;
}

void push(int instruction){
    instruction_stack[instruction_stack_pointer] = instruction;
    instruction_stack_pointer++;
}

int pop(void){
    instruction_stack_pointer--;

    return instruction_stack[instruction_stack_pointer];
}