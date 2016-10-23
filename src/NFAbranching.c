#include <NFA.h>

int main(int argc, char ** argv){
automaton start = new_automaton(""),
  FA1 = new_automaton("g"),
  FA2 = new_automaton("ga"),
  FA3 = new_automaton("gau"),

  FA4 = new_automaton("gaur"),
  FA5 = new_automaton("gaura"),
  FA6 = new_automaton("gaurav"),

  FA7 = new_automaton("gaut"),
  FA8 = new_automaton("gauta"),
  FA9 = new_automaton("gautam"),

  end = new_automaton("");

  //Create the machine
  NFA_connect(start, "g", FA1);
  NFA_connect(FA1, "a", FA2);
  NFA_connect(FA2, "u", FA3);

  NFA_connect(FA3, "r", FA4);
  NFA_connect(FA4, "a", FA5);
  NFA_connect(FA5, "v", FA6);
  NFA_connect(FA6, "e", end);

  NFA_connect(FA3, "t", FA7);
  NFA_connect(FA7, "a", FA8);
  NFA_connect(FA8, "m", FA9);
  NFA_connect(FA9, "e", end);

  FSM machine = new_FSM(start, end);

  printf("Testing gaurav: %d\n\n", FSM_test(machine, "gaurave"));
  printf("Resetting machine.\n");
  reset_FSM(machine);
  printf("Testing gautam: %d\n\n", FSM_test(machine, "gautame"));

  return 0;
}
