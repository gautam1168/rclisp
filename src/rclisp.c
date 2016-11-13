#include <repl.h>
#include <interpreter.h>

int main(int argc, char ** argv){
  char * input, * clean_input;
  char dummy;
  while(strcmp(input, "q")){
    prompt();
    input = read(0);
    clean_input = clean(input);
    printf("\t\t%s\n", clean_input);
    char ** tokens = tokenize(clean_input);
    for (int i = 0; i < token_arrlen(tokens); i++){
        printf("%d: %s\n", i, tokens[i]);
    }

    free(input);
    free(clean_input);
  }
  return 0;
}
