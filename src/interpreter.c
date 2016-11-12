#include <interpreter.h>

int token_arrlen(char ** arr){
    int i = 0;
    while(arr[i] != NULL) i++;
    return i;
}

char ** tokenize(char * input){
  int inputlength = strlen(input), numtokens = 0;
  int start = 0;
  //Skip all spaces in the front
  while( input[start] == ' '){
    start++;
  }
  printf("Input length: %d\n", inputlength);
  for (int i = start; i < inputlength; i++){
      printf("character: %d %c\n",i, input[i]);
      if (input[i] == ' '){
        numtokens++;
      }
  }
  char ** token_arr = (char **)malloc(numtokens*sizeof(char *));
  printf("Number of tokens: %d\n", numtokens);
  return token_arr;
}
