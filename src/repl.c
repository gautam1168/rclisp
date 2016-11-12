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
    int output_length = strlen(output);
    char * comprsd_output = (char *)malloc(output_length*sizeof(char));
    memset(comprsd_output, '\0', output_length*sizeof(char));
    int j = 0;
    bool seen_space = false;
    //Add spaces around parenthesis
    for (int i = 0; i < output_length; i++){
        if (output[i] == ' ' && !seen_space){
            comprsd_output[j] = output[i];
            seen_space = true;
            j++;
            if (j >= output_length){
              resize(comprsd_output, strlen(comprsd_output)*2);
            }
        }
        else if (output[i] != ' '){
          if (output[i] == '(' || output[i] == ')'){
            comprsd_output[j] = ' ';
            comprsd_output[j+1] = output[i];
            comprsd_output[j+2] = ' ';
            j += 3;
            if (j >= output_length){
              resize(comprsd_output, strlen(comprsd_output)*2);
            }
          }
          else{
            comprsd_output[j] = output[i];
            j++;
          }
          seen_space = false;
        }
    }
    j = 0; seen_space = false;
    free(output);
    output = comprsd_output;
    output_length = strlen(output);
    comprsd_output = (char *)malloc(output_length*sizeof(char));
    memset(comprsd_output, '\0', output_length*sizeof(char));
    for (int i = 0; i < output_length; i++){
        if (output[i] == ' ' && !seen_space){
            comprsd_output[j] = output[i];
            seen_space = true;
            j++;
            if (j >= output_length){
              resize(comprsd_output, strlen(comprsd_output)*2);
            }
        }
        else if (output[i] != ' '){
            comprsd_output[j] = output[i];
            seen_space = false;
            j++;
        }
    }
    return comprsd_output;
}
