#include <regex.h>

int main(int argc, char ** argv){
	printf("Create regex: alpha|beta \n");
    regex regxp = new_regex("alpha|beta");
	printf("\nTest against string alpha\n");
    FSM_test(regxp->machine, "alpha");
	printf("\nTest against string beta\n");
	FSM_test(regxp->machine, "beta");

	printf("\nCreate regex: 20|16\n");
	regex regxp2 = new_regex("20|16");
	printf("\nTest against string 20\n");
	FSM_test(regxp2->machine, "20");
	printf("\nTest against string 16\n");
	FSM_test(regxp2->machine, "16");

	printf("\nCreate regex: ga*urav\n");
	regex regxp3 = new_regex("ga*urav");
	printf("\nTest against string gaurav\n");
	FSM_test(regxp3->machine, "gurav");
	FSM_test(regxp3->machine, "gaaurav");

	printf("\nCreate regex: ga+urav\n");
	regex regxp4 = new_regex("ga+urav");
	printf("\nTest against string gaurav");
	FSM_test(regxp4->machine, "gaurav");
	printf("\nTest against string gurav\n");
	FSM_test(regxp4->machine, "gurav");

	printf("\nCreate regex: ga?urav\n");
	regex regxp5 = new_regex("ga?urav");
	printf("\nTest against string gaurav");
	FSM_test(regxp5->machine, "gaurav");
	printf("\ntest against string gurav\n");
	FSM_test(regxp5->machine, "gurav");
	printf("\ntest against string gaaurav\n");
	FSM_test(regxp5->machine, "gaaurav");

	printf("\nCreate regex abc[0-9]*de\n");
	regex regxp6 = new_regex("abc[0-9]*de");
	printf("\ntest against string abc031de\n");
	FSM_test(regxp6->machine, "abc031de");
	reset_FSM(regxp6->machine);
	printf("\ntest against string abc21de\n");
	FSM_test(regxp6->machine, "abc21de");

	printf("\nCreate regex abc[0789]*de\n");
	regex regxp7 = new_regex("abc[0789]*de");
	printf("\ntest against string abc0de\n");
	FSM_test(regxp7->machine, "abc0de");
	reset_FSM(regxp7->machine);
	printf("\ntest against string abc2de\n");
	FSM_test(regxp7->machine, "abc2de");
	printf("\ntest against string abc0789de\n");
	FSM_test(regxp7->machine, "abc0789de");
  return 0;
}
