#include "NFA.h"

automaton new_automaton(char * state){
  automaton NFA = (automaton)malloc(sizeof(automaton_t));
  NFA->marked = false;
  NFA->state = state;
  NFA->num_connections = 0;
  NFA->space = 1;
  NFA->messages = (char **)malloc(sizeof(char *));
  NFA->connected_automata = (automaton *)malloc(sizeof(automaton));
}

void print_automaton(automaton NFA){
  printf("marked: %d, \nstate: %s, \nnum_connections: %d, \nspace: %d, \nmessages:\n",
          NFA->marked, NFA->state, NFA->num_connections, NFA->space);
  for (int i=0; i<NFA->num_connections; i++){
    printf("%d: %s\n", i, NFA->messages[i]);
  }
  printf("\n");
}

void NFA_connect(automaton NFA, char * msg, automaton connect_NFA){
  //If there is no space to insert new connection then allocate
  if (NFA->num_connections == NFA->space){
    printf("No space to make connections. Allocating.\n");
    int space_to_allocate = 2*NFA->space;

    //Create new array for messages
    char ** msgs = (char **)malloc(space_to_allocate*sizeof(char *));
    automaton * states = (automaton *)malloc(space_to_allocate*sizeof(automaton));

    //Copy over the old data
    memcpy(msgs, NFA->messages, NFA->space*sizeof(char *));
    memcpy(states, NFA->connected_automata, NFA->space*sizeof(automaton));

    //Free the old memory
    free(NFA->messages);
    free(NFA->connected_automata);

    //Assign new data
    NFA->messages = msgs;
    NFA->connected_automata = states;

    //Update the available space
    NFA->space = space_to_allocate;
  }
  //Insert data
  NFA->messages[NFA->num_connections] = (char *)malloc(strlen(msg)*sizeof(char));
  NFA->messages[NFA->num_connections] = msg;
  // NFA->connected_automata[NFA->num_connections] = (automaton)malloc(sizeof(automaton_t));
  NFA->connected_automata[NFA->num_connections] = connect_NFA;
  //Update number of connections
  NFA->num_connections += 1;
}

void NFA_display(automaton starting_state, char * filename){
  //Create new queue with starting node
  fifo_node nd = new_fifo_queue(starting_state, NULL);

  automaton NFA;
  while (NFA = pop(nd)){
    //If the current node is not marked then print it, mark it and push all its
    //unmarked neighbors
    if (! NFA->marked){
      printf("Node: %s -> [", NFA->state);
      NFA->marked = true;
      for (int i=0; i < NFA->num_connections; i++){
        // printf("%s ", NFA->connected_automata[i]->state);
        nd = push(nd, NFA->connected_automata[i]);
        printf("%s ", NFA->connected_automata[i]->state);
      }
      printf("]\n");
    }

  }
}

fifo_node new_fifo_queue(automaton NFA, fifo_node next){
  fifo_node nd = (fifo_node)malloc(sizeof(fifo_node_t));
  nd->NFA = NFA;
  nd->next = next;
  return nd;
}

fifo_node push(fifo_node head, automaton NFA){
  //Pushing node to non-empty list (node may be null)
  if (head != NULL){
    return new_fifo_queue(NFA, head);
  }
  //Pushing non-empty node to empty queue
  else if (NFA != NULL){
    fifo_node nd = (fifo_node)malloc(sizeof(fifo_node_t));
    nd->NFA = NFA;
    nd->next = NULL;
  }
  //Invalid operations
  else{
    printf("Cannot push NULL to empty queue!\n");
  }
}

automaton pop(fifo_node head){
  //Find node just before last node(the one that was pushed
  //into the queue first) in queue
  fifo_node curr = head, next;
  automaton returnval;
  if(curr->next){
    next = curr->next;
    while(next->next){
      curr = next;
      next = next->next;
    }
    returnval = next->NFA;
    curr->next = NULL;
    free(next);
  }
  else{
    returnval = curr->NFA;
    free(curr);
  }
  return returnval;
}

void print_queue(fifo_node queue){
  int nodeindex = 0;
  while(queue != NULL){
    printf("Node index: %d\n", nodeindex);
    print_automaton(queue->NFA);
    queue = queue->next;
    nodeindex++;
  }
}

FSM new_FSM(automaton start, automaton end){
  FSM machine = (FSM)malloc(sizeof(FSM_t));
  machine->start_state = start;
  machine->end_state = end;
  //Machine starts in the start_state
  machine->currstate = new_fifo_queue(start, NULL);
}

void print_FSM(FSM machine){
  printf("Machine:\nstart_state:%s\nend_state:%s\nstate_length:%d\n\n",
        machine->start_state->state, machine->end_state->state,
        machine->state_length);
  printf("Machine state:\n");
  print_queue(machine->currstate);
}


automaton * run_FSM(FSM machine, char * message){
    //Traverse state queue
    automaton NFA = pop(machine->currstate);
    fifo_node newstate = NULL;
    while(NFA){
      if (NFA == machine->end_state){
        printf("Machine stopped!!!\n");
      }
      else{
        printf("message:%s, \nindex:%d\n", message, 0);
        for (int i=0; i < NFA->num_connections; i++){
          newstate = push(newstate, NFA->connected_automata[i]);
        }
      }
      NFA = pop(machine->currstate);
    }
}