#include <regex.h>

int main(int argc, char * argv){
    regex regxp = new_regex("gaurav");
    FSM_test(regxp->machine, "fsaldgauravadsfjj");
    return 0;
}
