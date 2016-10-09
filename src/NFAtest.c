#include <NFA.h>
int main(int argc, char ** argv){
  printf("Create and print automata\n");
  //Create new NFA
  automaton FA1 = new_automaton("a");
  print_automaton(FA1);
  automaton FA2 = new_automaton("b");
  print_automaton(FA2);
  automaton FA3 = new_automaton("c");
  print_automaton(FA3);
  printf("-------------------------\n\n");

  printf("Connect the automata\n");
  //Connect the automata
  NFA_connect(FA1, "B", FA2);
  printf("FA1:\n");
  print_automaton(FA1);
  NFA_connect(FA2, "C", FA3);
  printf("FA2:\n");
  print_automaton(FA2);
  printf("FA3:\n");
  print_automaton(FA3);
  printf("-------------------------\n\n");

  //New automaton queue
  printf("Create a queue and push the automata on\n");
  fifo_node queue = new_fifo_queue(FA1, NULL);
  queue = push(queue, FA2);
  queue = push(queue, FA3);
  printf("Automaton queue:\n");
  print_queue(queue);
  printf("-------------------------\n\n");
  // printf("Popping element from queue: \n");
  // FA1 = pop(queue);
  // print_automaton(FA1);
  // printf("Automaton queue:\n");
  // print_queue(queue);

  //Print the automata
  //TODO: Don't know why this is getting stuck
  // NFA_display(FA1, "file");

  //Make a new machine
  printf("Create finite state machine:\n");
  FSM machine = new_FSM(FA1, FA3);
  print_FSM(machine);
  printf("--------------------------\n\n");

  printf("running machine:\n");
  run_FSM(machine, "B");
  run_FSM(machine, "C");
  run_FSM(machine, "X");
  return 0;
}
