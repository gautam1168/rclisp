#include "NFA.h"

int main(int argc, char ** argv){
  FSM machine = compile_FSM("annie");
  print_FSM(machine);
  printf("Testing dsafannied31rfa: %d\n", FSM_test(machine, "dsafannied31rfa"));
  return 0;
}
