#pragma once

#include "vm.h"

#define BUFSIZE 100
#define MAX_TOKEN_NAME 100

int fgetch(FILE *source_code);
void ungetch(int c);
int get_token(char *token_name, FILE *source_code);
int is_operator(int c);
int skip_whitespace(FILE *source_code, int c);
int skip_comments(FILE *source_code);
SimStep *generate_code(SimStep *sim_step, char *source_code_file);
void push(int instruction);
int pop(void);