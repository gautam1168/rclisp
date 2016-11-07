#include <NFA.h>
#include <regex.h>

char ** stringsplit(char * input, char delimiter){
    //Calculate number of substrings
    char * itr = input;
    int loc = 0, numsubstrs = 0;
    while (*itr != '\0'){
        if (*itr == '|'){
            numsubstrs++;
        }
        loc++;
        itr++;
    }
    numsubstrs += 1;

    int stringlength = loc;
    //Allocate space for the output array of strings
    char ** output = (char **)malloc(sizeof(char*)*(numsubstrs+1));

    //Populate the output array
    int currloc = 0, lastloc = 0, subid = 0;
    itr = input;
    for(int i = 0; i <= stringlength; i++){
        if (*itr == '|' || *itr == '\0'){
            lastloc = (lastloc == 0)?lastloc:lastloc+1;
            output[subid] = (char *)malloc(sizeof(char)*(currloc-lastloc+1));
            memset(output[subid], '\0', sizeof(char)*(currloc-lastloc+1));
            memcpy(output[subid], &input[lastloc], sizeof(char)*(currloc-lastloc));
            lastloc = currloc;
            subid++;
        }
        itr++;
        currloc++;
    }
    output[numsubstrs] = NULL;
    return output;
}

char ** termsplit(char * input, char delimiter){
    //Calculate number of substrings
    char * itr = input;
    int loc = 0, numsubstrs = 0;
    while (*itr != '\0'){
        if (*itr == '|'){
            numsubstrs++;
        }
        loc++;
        itr++;
    }
    numsubstrs += 1;

    int stringlength = loc;
    //Allocate space for the output array of strings
    char ** output = (char **)malloc(sizeof(char*)*(numsubstrs+1));

    //Populate the output array
    int currloc = 0, lastloc = 0, subid = 0, openparen = 0;
    itr = input;

    for(int i = 0; i <= stringlength; i++){
        if (*itr == '('){
            openparen++;
        }
        else if (*itr == ')'){
            openparen--;
        }
        else if ((*itr == '|' || *itr == '\0') && (openparen == 0)){
            lastloc = (lastloc == 0)?lastloc:lastloc+1;
            output[subid] = (char *)malloc(sizeof(char)*(currloc-lastloc+1));
            memset(output[subid], '\0', sizeof(char)*(currloc-lastloc+1));
            memcpy(output[subid], &input[lastloc], sizeof(char)*(currloc-lastloc));
            lastloc = currloc;
            subid++;
        }
        itr++;
        currloc++;
    }
    output[numsubstrs] = NULL;
    return output;
}


int strArrayLen(char ** arr){
    int len = 0;
    while(*arr){
        len++;
        arr++;
    }
    return len;
}

void printStrArray(char ** arr){
    int len = strArrayLen(arr);
    for (int i = 0; i < len; i++){
        printf("%s\n", arr[i]);
    }
}

char * peekbase(char * string){
    char * output;
    if(*string == '('){
        char * itr;
        int loc=0;
        itr = string+1;
        while (*itr != ')' && *itr != '\0'){
            if (*itr == '\0'){
                printf("Unbalanced parenthesis\n");
                return NULL;
            }
            loc++;
            itr++;
        }
        output = (char *)malloc(sizeof(char)*loc);
        memset(output, '\0', loc);
        memcpy(output, string+1, loc);
    }
    else if(*string == '['){
        printf("Peeking square bracket base\n");
        char * itr;
        int loc=0;
        itr = string;
        while (*itr != ']' && *itr != '\0'){
            if (*itr == '\0'){
                printf("Unbalanced brackets\n");
                return NULL;
            }
            loc++;
            itr++;
        }
        printf("End location of base: %d %c\n", loc, string[loc]);
        //Check if base is followed by any special characters
        if (string[loc+1] == '*' || string[loc+1] == '+' || string[loc+1] == '?'){
          printf("Base followed by special characters\n");
          output = (char *)malloc(sizeof(char)*(loc+3));
          memset(output, '\0', loc+3);
          memcpy(output, string, loc+2);
        }
        else{
          printf("Base not followed by special characters\n");
          output = (char *)malloc(sizeof(char)*(loc+2));
          memset(output, '\0', loc+2);
          memcpy(output, string, loc+1);
        }
        printf("Base returned: %s\n", output);
    }
	else if (*(string+1) == '*' || *(string+1) == '+' || *(string+1) == '?'){
		output = (char *)malloc(sizeof(char)*4);
		output[0] = *string;
		output[1] = *(string+1);
    output[2] = *(string+2);
		output[3] = '\0';
	}
	else {
        output = (char *)malloc(sizeof(char)*2);
        output[0] = *string;
        output[1] = '\0';
    }

    return output;
}


char * eatbase(char * base, char * string){
    char * output;
    int stringlength = strlen(string), baselength = strlen(base);

    for (int i = 0; i < baselength; i++){
        if (*base != *string){
            printf("Base is not present in string\n");
            return NULL;
        }
    }
    int outputlength = stringlength-baselength+1;
    output = (char *)malloc(sizeof(char)*outputlength);
    memset(output, '\0', sizeof(char)*outputlength);
    memcpy(output, string+baselength, sizeof(char)*outputlength);
    return output;
}

regex new_regex(char * regular_expression){
    regex r = (regex)malloc(sizeof(regex_t));
    int stringsize = sizeof(char)*strlen(regular_expression);
    r->pattern = (char *)malloc(stringsize);
    memcpy(r->pattern, regular_expression, stringsize);

    automaton start = new_automaton(""), end = new_automaton("");
    regex_compile(r->pattern, start);
    r->machine = new_FSM(start, end);

    return r;
}

void regex_compile(char * input, automaton root){
    if (strlen(input) > 0){
        char ** substrs = termsplit(input, '|');
        char * base, * state;
        automaton nextFA, ephemeral;

        for (int i = 0; i < strArrayLen(substrs); i++){
            base = peekbase(substrs[i]);
            state = (char *)malloc(sizeof(char)*
                                   (strlen(root->state)+strlen(base)));
            strcpy(state, root->state);
            strcat(state, base);
            nextFA = new_automaton(state);

			      if (base[1] == '*'){
				        char * msg = (char *)malloc(2*sizeof(char));
				        msg[0] = base[0];
			   	      msg[1] = '\0';
				        NFA_connect(root, msg, root);
                msg = (char *)malloc(2*sizeof(char));
                msg[0] = base[2];
                msg[1] = '\0';
				        NFA_connect(root, msg, nextFA);
				        if (strlen(input) == 2){
					          root->isendstate = true;
				        }
			      }
            else if (base[1] == '+'){
              char * intermstate = (char *)malloc(sizeof(char)*
                                            (strlen(root->state)+1));
              char * msg = (char *)malloc(2*sizeof(char));
              msg[0] = base[0];
              msg[1] = '\0';
              strcpy(intermstate, root->state);
              strcat(intermstate, msg);
              automaton intermediateFA= new_automaton(intermstate);
              NFA_connect(root, msg, intermediateFA);
              msg = (char *)malloc(2*sizeof(char));
              msg[0] = base[0];
              msg[1] = '\0';
              NFA_connect(intermediateFA, msg, intermediateFA);
              msg = (char *)malloc(2*sizeof(char));
              msg[0] = base[2];
              msg[1] = '\0';
              NFA_connect(intermediateFA, msg, nextFA);
              if (strlen(input) == 2){
                  root->isendstate = true;
              }
            }
            else if (base[1] == '?'){
              char * intermstate = (char *)malloc(sizeof(char)*
                                            (strlen(root->state)+1));
              char * msg = (char *)malloc(2*sizeof(char));
              msg[0] = base[0];
              msg[1] = '\0';
              strcpy(intermstate, root->state);
              strcat(intermstate, msg);
              automaton intermediateFA= new_automaton(intermstate);
              NFA_connect(root, msg, intermediateFA);
              msg = (char *)malloc(2*sizeof(char));
              msg[0] = base[2];
              msg[1] = '\0';
              NFA_connect(intermediateFA, msg, nextFA);
              msg = (char *)malloc(2*sizeof(char));
              msg[0] = base[2];
              msg[1] = '\0';
              NFA_connect(root, msg, nextFA);
              if (strlen(input) == 2){
                  root->isendstate = true;
              }
            }
            else if (base[0] == '['){
              //Connect ephemeral state with "dot" message
              // printf("Compiling base in square brackets\n");
              ephemeral = new_automaton("[]");
              ephemeral->isephemeral = true;
              NFA_connect(root, "dot", ephemeral);
              // printf("Base obtained: %s\n", base);
              if (base[2] == '-'){
                char curr = base[1], end = base[3];
                int j = 0;
                char * msg;
                while (curr+j <= end){
                  msg = (char *)malloc(sizeof(char)*2);
                  msg[0] = curr+j;
                  msg[1] = '\0';
                  // printf("rootstate: %s message: %s\n", root->state, msg);
                  char * nextstate = (char *)malloc(sizeof(char)*(
                        strlen(root->state)+2
                  ));
                  memset(nextstate, '\0', strlen(root->state)+2);
                  memcpy(nextstate, root->state, strlen(root->state));
                  strcat(nextstate, msg);
                  nextFA = new_automaton(nextstate);
                  // printf("NextFA created with state: %s\n", nextstate);
                  NFA_connect(ephemeral, msg, nextFA);
                  // printf("Compiling %c\n", curr+j);
                  j++;
                  regex_compile(eatbase(base, substrs[i]), nextFA);
                }
              }
              else{
                char * msg;
                for (int j = 1; j < strlen(base)-1; j++){
                    msg = (char *)malloc(sizeof(char)*2);
                    msg[0] = base[j];
                    msg[1] = '\0';
                    // printf("rootstate: %s message: %s\n", root->state, msg);
                    nextFA = new_automaton(msg);
                    NFA_connect(ephemeral, msg, nextFA);
                    // printf("Compiling %c\n", base[j]);
                    regex_compile(eatbase(base, substrs[i]), nextFA);
                }
              }
            }
			      else{
            	  NFA_connect(root, base, nextFA);
				        if (strlen(input) == 1){
                	 nextFA->isendstate = true;
                  //  printf("End state is set\n");
            	  }
			      }

            regex_compile(eatbase(base, substrs[i]), nextFA);
        }
    }
}
