#include <repl.h>

char * eval(char * input){
  return input;
}

void prompt(){
  printf("rclisp> ");
}

char * read(int openparens){
  int loc = 0, size = 2;
  char c = ' ', * input = (char *)malloc(2*sizeof(char));
  memset(input, '\0', 2*sizeof(char));

  while(!(c == ')' && openparens == 0)){
    c = getchar();
    if (c == '('){
      openparens++;
    }
    else if (c == ')'){
      openparens--;
    }

    if (c == '\n'){
      char * nextline = read(openparens);
      resize(input, strlen(input)+strlen(nextline));
      strcat(input, nextline);
      return input;
    }
    else{
      input[loc] = c;
    }

    loc++;
    if (loc == size-2){
      size = size*2;
      resize(input, size);
    }
  }

  return input;
}

void resize(char * input, int newsize){
  char * memory = (char *)malloc(newsize);
  memset(memory, '\0', newsize);
  memcpy(memory, input, newsize/2);
}

void print(char * output){
  printf("\t%s\n\n", output);
}
