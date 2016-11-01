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
    if (*string != '('){
        printf("Processing normal char: %c\n", *string);
        output = (char *)malloc(sizeof(char)*2);
        output[0] = *string;
        output[1] = '\0';
    }
    
    else if(*string == '('){
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
    return output;
}


char * eatbase(char * base, char * string){
    char * output;
    int stringlength = strlen(string), baselength = strlen(base);
    printf("Input stringlength: %d, baselength: %d\n", 
            stringlength, baselength);
    
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
        printf("Compiling string: %s\n", input);
        char ** substrs = termsplit(input, '|');
        char * base;
        automaton nextFA;

        for (int i = 0; i < strArrayLen(substrs); i++){
            base = peekbase(substrs[i]);
            nextFA = new_automaton(base);
            NFA_connect(root, base, nextFA);

            regex_compile(eatbase(base, substrs[i]), nextFA);
        }
    }
}
