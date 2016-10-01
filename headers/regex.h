#ifndef REGEX_H
#define REGEX_H

#include "NFA.h"

struct regex_struct{
    automaton FSM;
    automaton * machinestate;
};

typedef struct regex_struct regex_t;
typedef regex_t * regex;

regex new_regex(char * regular_expression);
int regex_num_matches(char * string);
void regex_replace(char * string);
char ** regex_match_result(char * string);
#endif
