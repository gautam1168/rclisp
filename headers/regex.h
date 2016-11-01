#ifndef REGEX_H
#define REGEX_H

#include "NFA.h"

struct regex_struct{
    FSM machine;
    char * regexpattern;
};

typedef struct regex_struct regex_t;
typedef regex_t * regex;

regex new_regex(char * regular_expression);
int regex_num_matches(regex r, char * string);
void regex_replace(regex r, char * string);
char * regex_substring(regex r, char * string);
void regex_eat(regex r, char * string);
#endif
