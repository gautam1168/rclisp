#include <repl.h>

int main(int argc, char ** argv){
  char * input, * output;
  input = (char*)malloc(sizeof(char)*2);
  input[0] = ' ';
  input[1] = '\0';
  char dummy;
  while(strcmp(input, "q")){
    free(input);
    prompt();
    input = read(0);
    print(clean(input));
  }
  return 0;
}
