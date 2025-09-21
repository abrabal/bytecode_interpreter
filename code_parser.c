#define __STDC_WANT_LIB_EXT2__ 1

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
    {"add", 0x44},
    {"and", 0x43},
    {"immediate", 0x00},
    {"jgez", 0xC0},
    {"jgz", 0xC7},
    {"jlez", 0xC3},
    {"jlz", 0xC2},
    {"jnz", 0xC5},
    {"jump", 0xC4},
    {"jz", 0xC1},
    {"nand", 0x41},
    {"nop", 0xC0},
    {"nor", 0x42},
    {"or", 0x40},
    {"sub", 0x45}
};

static char buf[BUFSIZE];
static int bufp = 0;
static int instruction_stack[20];
static int instruction_stack_pointer = 0;
static Label *hashtab[HASHTAB_SIZE];

void compile_program(unsigned char *program, char *source_code_file, int max_program_size)
{
    FILE *source_code = fopen(source_code_file, "r");
    char token_name[MAX_TOKEN_NAME];
    int instruction_counter = 0;
    char operation_flag = 0;
    int instruction_placement_pointer = 0;
    Label *label = NULL;

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
    printf("number of instructions = %d\n", instruction_counter);

    for (int i = 0; i < HASHTAB_SIZE; i++){
        free_list(hashtab[i]);
    }
    fclose(source_code);
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
    if (c != ';'){
        ungetch(c);
    }

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
    int hashval = 0;

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