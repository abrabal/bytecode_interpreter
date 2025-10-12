#define __STDC_WANT_LIB_EXT2__ 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "code_parser.h"
#include "opcodes.h"
#include "vm.h"

#define NUM_OF_OPCODES sizeof(opcodes_for_parser)/sizeof(Opcode)

Opcode opcodes_for_parser[] =
{
    {"add", 0x44},
    {"and", 0x43},
    {"cp_from_input", 0xb0},
    {"cp_from_reg0", 0x80},
    {"cp_from_reg1", 0x88},
    {"cp_from_reg2", 0x90},
    {"cp_from_reg3", 0x98},
    {"cp_from_reg4", 0xa0},
    {"cp_from_reg5", 0xa8},
    {"immediate", 0x0},
    {"jgez", 0xc0},
    {"jgz", 0xc7},
    {"jlez", 0xc3},
    {"jlz", 0xc2},
    {"jnz", 0xc5},
    {"jump", 0xc4},
    {"jz", 0xc1},
    {"nand", 0x41},
    {"nop", 0xc0},
    {"nor", 0x42},
    {"or", 0x40},
    {"sub", 0x45}
};

static int instruction_stack[20];
static int instruction_stack_pointer = 0;
static Label *hashtab[HASHTAB_SIZE];

void compile_program(unsigned char *program, FILE *source_code, int max_program_size)
{
    char token_name[MAX_TOKEN_NAME];
    int instruction_counter = 0;
    char operation_flag = 0;
    int instruction_placement_pointer = 0;
    Label *label = NULL;

    memset(hashtab, 0, sizeof(hashtab) * sizeof(Label *)/sizeof(hashtab[0]));

    if(source_code == NULL){
        fprintf(stderr, "\nERROR: fail to open source code file");
        exit(1);
    }

    while (1){
        int c = get_token(token_name, source_code);

        if (is_operator(c)){
            if (operation_flag == 0){
                operation_flag = c;
            } else {
                fprintf(stderr, "FORMAT ERROR: unexpected token '%c'\n", c);
                exit(1);
            }
        }

        if (strcmp(token_name, "label") == 0 ){
            c = get_token(token_name, source_code);
            label = install(token_name, instruction_counter);
            continue;
        }

        if (isalpha(token_name[0])){
            label = lookup(token_name);
            if(label != NULL){
                push(label->value);
            } else {

                Opcode *match;
                Opcode key;

                key.name = token_name;
                match = (Opcode *)bsearch(&key, opcodes_for_parser, NUM_OF_OPCODES, sizeof(Opcode), compare_opcodes);

                if (match == NULL){
                    fprintf(stderr, "ERROR: instruction <%s> doesn't exist\n", token_name);
                    exit(1);
                } else {
                    push(match->value);
                }
            }
        }

        if(isdigit(token_name[0])){
            push(atoi(token_name));
        }

        if (c == ';'){
            instruction_counter += 1;
            int second_operand = 0;
            switch(operation_flag){
                case '+':
                    program[instruction_placement_pointer] = (pop() + pop());
                    break;
                case '-':
                    second_operand = pop();
                    program[instruction_placement_pointer] = (pop() - second_operand);
                    break;
                case '*':
                    program[instruction_placement_pointer] = (pop() * pop());
                    break;
                case '/':
                    second_operand = pop();
                    program[instruction_placement_pointer] = (pop() / second_operand);
                    break;
                case '|':
                    program[instruction_placement_pointer] = (pop() | pop());
                    break;
                case '&':
                    program[instruction_placement_pointer] = (pop() & pop());
                    break;
                default:
                    program[instruction_placement_pointer] = pop();
                    break;
        }
            operation_flag = 0;
            instruction_placement_pointer++;
        }

        if (c == EOF){
            break;
        }

        if(instruction_placement_pointer > max_program_size){
            fprintf(stderr, "\nout of memory, program can't have more then %d instructions\n", max_program_size);
            exit(1);
        }
    }

    for (int i = 0; i < HASHTAB_SIZE; i++){
        free_list(hashtab[i]);
    }
}

int get_token(char *token_name, FILE *source_code)
{
    int c = fgetc(source_code);
    memset (token_name, 0, sizeof(char) * MAX_TOKEN_NAME);

    c = skip_whitespace(source_code, c);

    while (c == '/'){
        c = skip_comments(source_code);
        c = skip_whitespace(source_code, c);
    }
    
    if (is_operator(c)){
        return c;
    }

    while (isalnum(c) || c == '_'){
        *token_name = c;
        token_name++;
        c = fgetc(source_code);
    }

    token_name = '\0';

    if(!isspace(c) && c != ';' && c != EOF && !(is_operator(c))){
        fprintf(stderr, "FORMAT ERROR: unexpected token '%c'\n", c);
        exit(1);
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

void push(int instruction){
    instruction_stack[instruction_stack_pointer] = instruction;
    instruction_stack_pointer++;
}

int pop(void){
    if(instruction_stack_pointer == 0){
        fprintf(stderr, "ERROR: can't pop from empty stack\n");
        exit(1);
    }
    instruction_stack_pointer--;

    return instruction_stack[instruction_stack_pointer];
}

int compare_opcodes(const void *p1, const void *p2)
{
    const Opcode *struct1 = (const Opcode *)p1;
    const Opcode *struct2 = (const Opcode *)p2;

    return strcmp(struct1->name, struct2->name);
}

int hash (char *str)
{
    unsigned int hashval = 0;

    for (; *str != '\0'; str++){
        hashval = *str + 31 * hashval;
    }
    return hashval % HASHTAB_SIZE;
}

Label *lookup(char *name)
{
    Label *next_page;
    
    for(next_page = hashtab[hash(name)]; next_page != NULL; next_page = next_page->next_page){
        if (strcmp(name, next_page->name) == 0){
            return next_page;
        }
    }

    return NULL;
}

Label *install(char *name, int definition)
{
    Label *next_page;
    int hashval = 0;
    
    next_page = lookup(name);

    if (next_page == NULL){
        next_page = malloc(sizeof(Label));

        next_page->name = strdup(name);
        next_page->value = definition;

        hashval = hash(name);
        next_page->next_page = hashtab[hashval];
        hashtab[hashval] = next_page;
    }

    return next_page;
}

void free_list(Label *next_page)
{
    Label *curr_p;
    if (next_page != NULL){
        curr_p = next_page;
        next_page = next_page->next_page;
        free(curr_p->name);
        free(curr_p);
        free_list(next_page);
    }
}