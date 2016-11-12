#ifndef INTERPRETER_H
#define INTERPRETER_H

struct s_expression_struct{

};
typedef struct s_expression_struct s_expression_t;
typedef s_expression_t * s_expression;
s_expression parse(char * input);

//value will be a union
//value eval(s_expression input);

char ** tokenize(char * input);

#endif
