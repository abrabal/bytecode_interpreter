#pragma once

#include "vm.h"

#define MAX_TOKEN_NAME 100
#define HASHTAB_SIZE 100

typedef struct Label{
    struct Label *next_page;
    char *name;
    int value;

} Label;

int get_token(char *token_name, FILE *source_code);
int is_operator(int c);
int skip_whitespace(FILE *source_code, int c);
int skip_comments(FILE *source_code);
void compile_program(unsigned char *program, FILE *source_code, int max_program_size);
void push(int instruction);
int pop(void);
int compare_opcodes(const void *p1, const void *p2);
int hash (char *str);
Label *lookup(char *label);
Label *install(char *name, int definition);
void free_list(Label *next_page);