#include <repl.h>

int main(int argc, char ** argv){
  char * input, * clean_input;
  char dummy;
  while(strcmp(input, "q")){
    prompt();
    input = read(0);
    clean_input = clean(input);
    print(clean_input);
    tokenize(clean_input);
    free(input);
    free(clean_input);
  }
  return 0;
}
