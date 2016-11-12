#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <repl.h>

struct s_expression_struct{

};
typedef struct s_expression_struct s_expression_t;
typedef s_expression_t * s_expression;
s_expression parse(char * input);

//value will be a union
//value eval(s_expression input);

char ** tokenize(char * input);
int token_arrlen(char ** arr);
#endif
