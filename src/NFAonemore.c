#include <NFA.h>

int main(int argc, char ** argv){
  automaton start = new_automaton(""),
  FA1 = new_automaton("g"),
  FA2 = new_automaton("ga"),
  FA3 = new_automaton("ga+u"),
  FA4 = new_automaton("ga+ur"),
  FA5 = new_automaton("ga+ura"),
  FA6 = new_automaton("ga+urav");

  //Create machine
  NFA_connect(start, "g", FA1);
  NFA_connect(FA1, "a", FA2);
  NFA_connect(FA2, "a", FA2);
  NFA_connect(FA2, "u", FA3);
  NFA_connect(FA3, "r", FA4);
  NFA_connect(FA4, "a", FA5);
  NFA_connect(FA5, "v", FA6);
  FSM machine = new_FSM(start, FA6);

  printf("Testing gaurav: %d\n\n", FSM_test(machine, "gaurav"));
  printf("Resetting the machine.\n");
  reset_FSM(machine);
  printf("Testing gurav: %d\n\n", FSM_test(machine, "gurav"));
  printf("Resetting the machine.\n");
  reset_FSM(machine);
  printf("Testing gaaaurav: %d\n\n", FSM_test(machine, "gaaaurav"));
  return 0;
}
