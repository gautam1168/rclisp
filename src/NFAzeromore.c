#include <NFA.h>

int main(int argc, char ** argv){
  automaton start = new_automaton(""),
  FA1 = new_automaton("g"),
  FA2 = new_automaton("ga*u"),
  FA3 = new_automaton("ga*ur"),
  FA4 = new_automaton("ga*ura"),
  FA5 = new_automaton("ga*urav");

  //Create machine
  NFA_connect(start, "g", FA1);
  NFA_connect(FA1, "a", FA1);
  NFA_connect(FA1, "u", FA2);
  NFA_connect(FA2, "r", FA3);
  NFA_connect(FA3, "a", FA4);
  NFA_connect(FA4, "v", FA5);
  FSM machine = new_FSM(start, FA5);

  printf("Testing gaurav: %d\n\n", FSM_test(machine, "gaurav"));
  printf("Resetting the machine.\n");
  reset_FSM(machine);
  printf("Testing gurav: %d\n\n", FSM_test(machine, "gurav"));
  printf("Resetting the machine.\n");
  reset_FSM(machine);
  printf("Testing gaaaurav: %d\n\n", FSM_test(machine, "gaaaurav"));
  return 0;
}
