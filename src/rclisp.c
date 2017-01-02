#include <repl.h>
#include <interpreter.h>

void printTermTree(expression e){
    printf("%d :(", e->numitems);
    for (int i=0; i <  e->numitems; i++){
      if (!e->isatomic[i]){
        printf(" %d=[ ", i);
        printTermTree(e->subexprs[i]);
        printf(" ] ");
      }
      else{
        printf(" %d=[ %s ] ", i, e->value[i]);
      }
    }
    printf(")");
}

int main(int argc, char ** argv){
  char * input="", * clean_input;
  char dummy;
  while(strcmp(input, "q")){
    prompt();
    input = read(0);
    clean_input = clean(input);
    printf("\t\tCleaned input: %s\n", clean_input);
    char ** tokens = tokenize(clean_input);
    for (int i = 0; i < token_arrlen(tokens); i++){
        printf("%d\t", i);
    }
    printf("\n");
    for (int i = 0; i < token_arrlen(tokens); i++){
        printf("%s\t", tokens[i]);
    }
    printf("\n");

    expression e = parse(tokens, 0, token_arrlen(tokens)-1);
    printf("Answer:\n");
    //printTermTree(e);
    //printf("\n");
    expression ans = execute(e);
    print(ans, 0);
    free(e->isatomic);
    free(e->value);
    free(e->subexprs);
    free(e);
    free(ans);
    // free(input);
    free(clean_input);
  }
  return 0;
}
