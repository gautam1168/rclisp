#ifndef NFA_H
#define NFA_H

struct automaton_struct{
    char * state;
    char ** messages;
    struct automaton * connected_automata;
};

typedef struct automaton_struct automaton_t;
typedef automaton_t * automaton;

automaton new_automaton(int num_messages, char ** messages, char * state);
void NFA_connect(automaton starting_state, automaton * ending_states);
void NFA_display(automaton starting_state, char * filename);

#endif
