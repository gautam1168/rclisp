#include <regex.h>

int main(int argc, char * argv){
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

  return 0;
}
