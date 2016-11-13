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
  if (e->isatomic){
    printf(" %s ", e->value);
  }
  else{
    printf(" ( ");
    for ( int i = 0; i < e->numitems; i++ ){
        print(e->subexprs[i]);
    }
    printf(" ) ");
  }
}

// expression parse(char ** tokens){
//   expression e;
//   if (!openparen(token[0])){
//     //error
//   }
//   //for tokens
//   if (openparen(token)){
//       addtoexpr(e, parse(find_close_paren(token)), type="expr")
//   }
//   else{
//       addtoexpr(e, token, type="atom")
//   }
//   return e;
// }

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
