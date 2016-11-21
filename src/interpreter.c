#include <interpreter.h>

int token_arrlen(char ** arr){
    int i = 0;
    while(arr[i] != NULL) i++;
    return i;
}

char * trim(char * input){
  int length = strlen(input);
  int start = 0, end;
  bool startfound = false;
  for (int i = 0; i < length; i++){
      if (input[i] != ' ' && !startfound){
          start = i;
          startfound = true;
      }
      if (startfound && input[i] == ' '){
        end = i;
      }
  }
  char * output = (char *)malloc(end-start+2);
  memset(output, '\0', end-start+2);
  memcpy(output, input+start, end-start+1);
  free(input);
  return output;
}

char ** tokenize(char * input){
  int inputlength = strlen(input), numtokens = 0;
  int start = 0;
  //Skip all spaces in the front
  while( input[start] == ' '){
    start++;
  }
  for (int i = start; i < inputlength; i++){
      if (input[i] == ' '){
        numtokens++;
      }
  }
  char ** token_arr = (char **)malloc((numtokens + 1)*sizeof(char *));
  int tokenstart, tokenend, j, token_num = 0;
  int i = 0;
  while (i < inputlength){
      if (input[i] != ' '){
          tokenstart = i;
          j = tokenstart;
          while(input[j] != ' '){
              j++;
          }
          tokenend = j;
          int tokenlength = tokenend-tokenstart;
          token_arr[token_num] = (char *)malloc((tokenlength+1)*sizeof(char));
          memset(token_arr[token_num], '\0', (tokenlength+1)*sizeof(char));
          memcpy(token_arr[token_num], input+tokenstart, tokenlength);
          token_num++;
          i = tokenend;
      }
      else{
        i++;
      }
  }
  token_arr[numtokens] = NULL;
  return token_arr;
}

void print(expression e){
  if (e->numitems == 1){
    printf(" %s ", e->value[0]);
  }
  else if (e->numitems == 0){
    printf(" () ");
  }
  else{
    printf(" ( ");
    for ( int i = 0; i < e->numitems; i++ ){
        print(e->subexprs[i]);
    }
    printf(" ) ");
  }
}

expression parse(char ** tokens, int start, int end){
  expression e = (expression)malloc(sizeof(expression_t));
  int totaltokens;
  if (start == 0){
    totaltokens = end-start+1;
  }
  else{
    totaltokens = end-start+2;
  }
  printf("Total tokens: %d %d\n", totaltokens, token_arrlen(tokens));

  //Check that the the expression is enclosed in parenthesis
  tokens[start] = trim(tokens[start]);
  tokens[end] = trim(tokens[end]);
  printf("Starting token: %s, %d\n", tokens[start], strcmp(tokens[start], "("));
  printf("Ending token: %s, %d\n", tokens[end], strcmp(tokens[end], ")"));
  if (strcmp(tokens[start], "(") != 0 ||
      strcmp(tokens[end], ")") != 0){
    printf("ERROR! Invalid expression encountered");
    return NULL;
  }

  //Number of subexpressions
  int i = start+1, num_openparens = 0, num_subexprs = 0;
  while (i < totaltokens-1){
    printf("Token: %s ", tokens[i]);
    tokens[i] = trim(tokens[i]);
    if (strcmp(tokens[i], "(") == 0){
      num_openparens++;
      printf("Number of open parens: %d\n", num_openparens);
    }
    else if (strcmp(tokens[i], ")") == 0 && num_openparens == 1){
      num_subexprs++;
      num_openparens--;
      printf("Number of open parens: %d\n", num_openparens);
    }
    else if (strcmp(tokens[i], ")") == 0){
      num_openparens--;
      printf("Number of open parens: %d\n", num_openparens);
    }
    else if (strcmp(tokens[i], ")") != 0 &&
             strcmp(tokens[i], "(") != 0 &&
             num_openparens == 0){
      num_subexprs++;
      printf("Number of subexpressions seen: %d\n", num_subexprs);
    }
    i++;
  }

  printf("Number of subexpressions: %d\n", num_subexprs);
  e->numitems = num_subexprs;
  e->subexprs = (expression *)malloc(num_subexprs*sizeof(expression));
  e->isatomic = (bool *)malloc(num_subexprs*sizeof(bool));
  e->value = (char **)malloc(num_subexprs*sizeof(char *));

  //Put expressions and values in the arrays
  int j = start+1;
  for (int i = start+1; i < num_subexprs-1; i++){ //Parse from after first bracket to before last bracket
    if (strcmp(tokens[j], "(") != 0){
      e->subexprs[i] = NULL;
      e->isatomic[i] = true;
      e->value[i] = (char *)malloc(strlen(tokens[j]));
      strcpy(e->value[i], tokens[j]);
      j++;
    }
    else {
      int subexpr_start = j;
      while (strcmp(tokens[j], ")") != 0){
        j++;
      }
      printf("Recursive call with: %d -> %s: %d -> %s", subexpr_start,
                                        tokens[start], j, tokens[j]);
      e->subexprs[i] = (expression)malloc(sizeof(expression_t));
      e->subexprs[i] = parse(tokens, subexpr_start, ++j);
      j++;
      e->isatomic[i] = false;
      e->value[i] = NULL;
    }
  }
  return e;
}

// expression quote(expression){
//
// }
//
// char * atom(expression){
//
// }
//
// char * eq( e1, e2){
//
// }
//
// char * car(expression){
//
// }
//
// expression cdr(expression){}
//
// expression cons(e1, e2){}
//
// expression cond(expression * ){}
//
// expression execute(expression){
//
// }
