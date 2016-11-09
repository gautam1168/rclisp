#ifndef REPL_H
#define REPL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <interpreter.h>

void prompt();
char * read(int openparens);
void resize(char * input, int newsize);
void print(char * output);

#endif
