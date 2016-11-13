#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <repl.h>
#include <stdbool.h>

struct expression_struct{
    bool isatomic;
    int numitems;
    struct expression_struct ** subexprs;
    char * value; //only defined for atomic expressions
};
typedef struct expression_struct expression_t;
typedef expression_t * expression;
expression parse(char * input);

void print(expression output);

char ** tokenize(char * input);
int token_arrlen(char ** arr);
#endif
