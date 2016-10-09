#ifndef NFA_H
#define NFA_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Structure to represent an automaton
/* Functions:
 * 1. Store a string state
 * 2. Store array of other automatons representing other states
 * 3. Store a list of messages that lead to transition to these
 *    other states
**/
struct automaton_struct{
    bool marked;
    char * state;
    char ** messages;
    int num_connections, space;
    struct automaton_struct ** connected_automata;
};
typedef struct automaton_struct automaton_t;
typedef automaton_t * automaton;

//Create new automaton
automaton new_automaton(char * state);
//Connect two automatons with a string message
void NFA_connect(automaton NFA, char * msg, automaton connect_NFA);
//Print a set of connected automata to screen
void NFA_display(automaton starting_state, char * filename);
void print_automaton(automaton NFA);

//A queue of automata for graph traversal etc.
/*
 * head is at the last node pushed
 * pop removes tail
**/
struct fifo_node_struct{
  automaton NFA;
  struct fifo_node_struct * next;
};
typedef struct fifo_node_struct fifo_node_t;
typedef fifo_node_t * fifo_node;

//push/pop an automaton to queue
fifo_node push(fifo_node queue, automaton NFA);
automaton pop(fifo_node queue);
//A queue is just a one node that is treated as the head.
//Accordingly this constructor simply returns a fifo_node
fifo_node new_fifo_queue(automaton NFA, fifo_node next);
void print_queue(fifo_node queue);

//Finite state machine
/*
 * Functions
 * 1. Store a starting and ending state of the machine
 * 2. Store a queue of automata representing current state of machine
**/
struct FSM_struct{
  automaton start_state, end_state;
  fifo_node currstate;
  int state_length;
};
typedef struct FSM_struct FSM_t;
typedef FSM_t * FSM;

//Create new machine
FSM new_FSM(automaton start, automaton end);
//Send a message to a machine to change its state
void run_FSM(FSM machine, char * message);
//Print FSM
void print_FSM(FSM machine);
#endif
