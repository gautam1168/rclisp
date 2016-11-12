#include <repl.h>
#include <stdbool.h>

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
      resize(input, strlen(input)+strlen(nextline)+1);
      input[strlen(input)] = ' ';
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

char * clean(char * rawinput){
    int inputlength = strlen(rawinput);
    char * output = (char *)malloc(inputlength*sizeof(char));
    memset(output, '\0', inputlength*sizeof(char));
    //Replace all characters less than 33 with spaces
    for (int i = 0; i < inputlength; i++){
        if (rawinput[i] < 33){
            output[i] = ' ';
        }
        else {
          output[i] = rawinput[i];
        }
        output[i+1] = '\0';
    }
    //Get start position of all spaces
    int output_length = strlen(output);
    char * comprsd_output = (char *)malloc(output_length*sizeof(char));
    memset(comprsd_output, '\0', output_length*sizeof(char));
    int j = 0;
    bool seen_space = false;
    for (int i = 0; i < output_length; i++){
        if (output[i] == ' ' && !seen_space){
            comprsd_output[j] = output[i];
            seen_space = true;
            j++;
        }
        else if (output[i] != ' '){
          comprsd_output[j] = output[i];
          seen_space = false;
          j++;
        }
    }
    return comprsd_output;
}
