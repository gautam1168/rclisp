#ifndef REPL_H
#define REPL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <interpreter.h>

void prompt();
char * read(int openparens);
char * clean(char * rawinput);
char * my_resize(char * input, int newsize);
void remove_linebreaks(char * input);

#endif
