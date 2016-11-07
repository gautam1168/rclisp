#include "NFA.h"

automaton new_automaton(char * state){
  automaton NFA = (automaton)malloc(sizeof(automaton_t));
  NFA->isendstate = false;
  NFA->isephemeral = false;
  NFA->marked = false;
  NFA->state = state;
  NFA->num_connections = 0;
  NFA->space = 1;
  NFA->messages = (message)malloc(sizeof(message_t));
  NFA->connected_automata = (automaton *)malloc(sizeof(automaton));
}

void print_automaton(automaton NFA){
  printf("marked: %d, \nstate: %s, \nnum_connections: %d, \nspace: %d, \nmessages:\n",
          NFA->marked, NFA->state, NFA->num_connections, NFA->space);
  for (int i=0; i<NFA->num_connections; i++){
    printf("\t%d: %s\n", i, NFA->messages[i].string);
  }
  printf("\n");
}

void NFA_connect(automaton NFA, char * msg, automaton connect_NFA){
  //If there is no space to insert new connection then allocate
  if (NFA->num_connections == NFA->space){
    printf("No space to make connections. Allocating.\n");
    int space_to_allocate = 2*NFA->space;

    //Create new array for messages
    message msgs = (message)malloc(space_to_allocate*sizeof(message_t));
    automaton * states = (automaton *)malloc(space_to_allocate*sizeof(automaton));

    //Copy over the old data
    memcpy(msgs, NFA->messages, NFA->space*sizeof(message_t));
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
  NFA->messages[NFA->num_connections].string = (char *)malloc(strlen(msg)*sizeof(char));
  NFA->messages[NFA->num_connections].string = msg;
  // memcpy(NFA->messages[NFA->num_connections].string, msg, sizeof(char));
  // NFA->connected_automata[NFA->num_connections] = (automaton)malloc(sizeof(automaton_t));
  NFA->connected_automata[NFA->num_connections] = connect_NFA;
  //Update number of connections
  NFA->num_connections += 1;
}

void NFA_display(automaton starting_state, char * filename){
  //Create new queue with starting node
  fifo_node nd = new_fifo_queue(starting_state, NULL);

  automaton NFA;
  if (nd->NFA == NULL){nd = NULL;}
  while (nd){
    NFA = pop(nd);
    if (nd->NFA == NULL){nd = NULL;}
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
  if (NFA != NULL){
    return new_fifo_queue(NFA, head);
  }
  //Invalid operations
  else{
    printf("Cannot push NULL to empty queue!\n");
    return NULL;
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
    //TODO: This doesn't work. This is why you shouldn't use
    //just the node as a queue. Make a structure for node and
    //another for storing the head node (the queue)
    //A fifo_node with no NFA is not defined so destroy head
    head = NULL;
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
  machine->state_length = 1;
}

void print_FSM(FSM machine){
  printf("Machine:\nstart_state:%s\nend_state:%s\nstate_length:%d\n\n",
        machine->start_state->state, machine->end_state->state,
        machine->state_length);
  printf("Machine state:\n");
  print_queue(machine->currstate);
}

automaton FSM_popstate(FSM machine){
  automaton NFA = NULL;
  if (machine->currstate){
    NFA = pop(machine->currstate);

    //Destroy state queue when empty
    if (machine->currstate->NFA == NULL){
      machine->currstate = NULL;
    }
  }
  return NFA;
}

int run_FSM(FSM machine, char * message){
    //Traverse state queue
    // automaton NFA = pop(machine->currstate);
    //Get automaton from machine's currstate
    automaton NFA = FSM_popstate(machine), ephemeral;
    fifo_node newstate = NULL;
    int new_statelength = 0;
    while(NFA){
      //If this state is an end state then stop machine in finished state
      if (NFA == machine->end_state || NFA->isendstate){
        printf("Machine is in end state!! Stopping execution.\n");
        return 0;
      }
      else{
        //Iterate over all connections of current automaton
        for (int i=0; i < NFA->num_connections; i++){
          // printf("%s:%s -> %s ", NFA->state, message,
          //                       NFA->connected_automata[i]->state);
          //Check if the connection message is compatible with current msg
          if (strcmp(NFA->messages[i].string, "dot") == 0 ||
              strcmp(message, NFA->messages[i].string) == 0){
            //If the connected state is ephemeral
            if (NFA->connected_automata[i]->isephemeral){
                // printf("Ephemeral state reached\n");
                ephemeral = NFA->connected_automata[i];
                //Iterate over all of its connections
                for (int j=0; j < ephemeral->num_connections; j++){
                    //If the message is compatible to connections on ephemeral state
                    if (strcmp(message, "dot") == 0 ||
                        strcmp(message, ephemeral->messages[j].string) == 0){
                      //Push the connected automata on the new state queue
                      newstate = push(newstate, ephemeral->connected_automata[j]);
                      new_statelength++;
                    }
                }
            }
            //If state is not ephemeral
            else{
              // printf("Normal state\n");
              //Push the connected state to the new state queue
              newstate = push(newstate, NFA->connected_automata[i]);
              new_statelength++;
            }
          }
        }
      }

      // NFA = pop(machine->currstate);
      NFA = FSM_popstate(machine);
    }
    machine->state_length = new_statelength;
    free(machine->currstate);
    machine->currstate = newstate;
    if (new_statelength == 0){
      // printf("Machine's currstate has no more nodes!\n");
      return -1;
    }
    else if(new_statelength == 1 &&
                 (machine->currstate->NFA == machine->end_state ||
                  machine->currstate->NFA->isendstate)){
      return 0;
    }
    return 1;
}

void match_FSM(FSM machine, message msg, int num_message){
  int machinelive;
  for (int i = 0; i < num_message; i++){
    machinelive = run_FSM(machine, msg[i].string);
    if (machinelive < 1){
      break;
    }
  }
  if (machinelive == 1){
    printf("Machine is bigger than message array.\n");
  }
  else if (machinelive == -1){
    printf("Looks like there was no match!\n");
  }
  else if (machinelive == 0){
    printf("Machine in end state. Match complete.\n");
  }
  else{
    printf("There's a ghost here.\n");
  }
}

bool FSM_test(FSM machine, char * string){
  int msglen = strlen(string), machinelive;
  printf("Running machine with: %s\n", string);
  char * msg = (char *)malloc(sizeof(char));
  int numMatches = 0;

  for (int i = 0; i < msglen; i++){
    *msg = string[i];
    machinelive = run_FSM(machine, msg);
    //If a match is found
    if (machinelive == 0){
      numMatches++;
      reset_FSM(machine);
    }
    //If machine failed to match
    else if (machinelive == -1){
      reset_FSM(machine);
    }
    printf("message: %c, machinestate: %d\n",
            string[i], machinelive);
  }
  printf("\n----------------------------------\n");
  printf("Number of matches found: %d\n", numMatches);
  reset_FSM(machine);
  return (numMatches > 0)?true:false;
}

void reset_FSM(FSM machine){
  free(machine->currstate);
  machine->currstate = NULL;
  machine->currstate = new_fifo_queue(machine->start_state, NULL);
  machine->state_length = 1;
}

FSM compile_FSM(char * regex){
  //Iterate over the string
  int len = strlen(regex);
  char * msg, * statestring;
  automaton start = new_automaton(""), curr = start, next;

  for (int i = 0; i < len; i++){
    msg = (char *)malloc(sizeof(char));
    *msg = regex[i];
    statestring = (char *)malloc((i+1)*sizeof(char));
    memcpy((void *)statestring, (void *)regex, (i+1)*sizeof(char));
    //For each character create a NFA in serial
    next = new_automaton(statestring);
    NFA_connect(curr, msg, next);
    curr = next;
    //If character is [ then create NFA in branches
    //If character is ] then merge all branches
    //If character is * then branch back
    //If character is + then create new node then branch back
  }
  //Return machine
  FSM machine = new_FSM(start, curr);
  return machine;
}
