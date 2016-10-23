#include "NFA.h"

//Match
int main(int argc, char ** argv){
  automaton start = new_automaton(""),
  FA1 = new_automaton("g"),
  FA2 = new_automaton("ga"),
  FA3 = new_automaton("gau"),
  FA4 = new_automaton("gaur"),
  FA5 = new_automaton("gaura"),
  FA6 = new_automaton("gaurav");

  //Create the machine
  NFA_connect(start, "g", FA1);
  NFA_connect(FA1, "a", FA2);
  NFA_connect(FA2, "u", FA3);
  NFA_connect(FA3, "r", FA4);
  NFA_connect(FA4, "a", FA5);
  NFA_connect(FA5, "v", FA6);
  FSM machine = new_FSM(start, FA6);

  //Printing the machine
  print_FSM(machine);

  //Test some strings on the machine
  printf("Resetting machine.\n");
  reset_FSM(machine);
  printf("Result gaurav: %d\n\n", FSM_test(machine, "gaurav"));

  printf("Resetting machine.\n");
  reset_FSM(machine);
  printf("Result fsalfa: %d\n\n", FSM_test(machine, "fsalfa"));

  printf("Resetting machine.\n");
  reset_FSM(machine);
  printf("Result as23gaurav1244: %d\n\n",
                        FSM_test(machine, "as23gaurav1244"));
  return 0;
}
