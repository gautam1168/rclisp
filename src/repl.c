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
      input = my_resize(input, strlen(input)+strlen(nextline)+1);
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
      input = my_resize(input, size);
    }
  }

  return input;
}

char * my_resize(char * input, int newsize){
  char * memory = (char *)malloc(newsize);
  memset(memory, '\0', newsize);
  memcpy(memory, input, strlen(input));
  free(input);
  return (char *)memory;
}

void remove_linebreaks(char * input){
    int inputlength = strlen(input);
    //Replace all characters less than 33 with spaces
    for (int i = 0; i < inputlength; i++){
        if (input[i] < 33){
            input[i] = ' ';
        }
    }
}

char * compress_whitespace(char * input){
  int inputlength = strlen(input);
  char * output = (char *)malloc(sizeof(char)*inputlength);
  memset(output, '\0', inputlength*sizeof(char));
  bool seen_space = false;
  int j = 0;
  for (int i = 0; i < inputlength; i++){
      if (input[i] == ' ' && !seen_space){
          output[j] = input[i];
          seen_space = true;
          j++;
      }
      else if (input[i] != ' '){
          output[j] = input[i];
          seen_space = false;
          j++;
      }
  }
  free(input);
  return output;
}

//Pad the parenthesis with spaces
char * padparens(char * input){
  int inputlength = strlen(input);
  char * output = (char *)malloc(inputlength*sizeof(char));
  memset(output, '\0', inputlength*sizeof(char));
  int j = 0;
  bool seen_space = false;
  //Add spaces around parenthesis
  int availablespace = inputlength;
  for (int i = 0; i < inputlength; i++){
      if (input[i] == ' ' && !seen_space){
          output[j] = input[i];
          seen_space = true;
          j++;
      }
      else if (input[i] != ' '){
        if (input[i] == '(' || input[i] == ')'){
          if (j+3 >= availablespace){
            output = my_resize(output, availablespace*2);
            availablespace = availablespace*2;
          }
          output[j] = ' ';
          output[j+1] = input[i];
          output[j+2] = ' ';
          j += 3;
        }
        else{
          output[j] = input[i];
          j++;
        }
        seen_space = false;
      }
      if (j >= availablespace){
        output = my_resize(output, availablespace*2);
        availablespace = availablespace*2;
      }
  }
  free(input);
  return output;
}

char * clean(char * rawinput){
    printf("Cleaning rawinput: %s\n", rawinput);
    remove_linebreaks(rawinput);
    printf("Without linebreaks: %s\n", rawinput);
    char * output = padparens(rawinput);
    printf("Padded parens: %s\n", output);
    char * comprsd_output = compress_whitespace(output);
    printf("Compressed output: %s\n", comprsd_output);
    return comprsd_output;
}
