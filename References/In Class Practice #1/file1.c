#include <stdio.h>

#include "file1header.h"
#include "externs.h"


//Function f1 takes a single input argument of type int and returns the value of it’s input argument as float
float f1(int arg){
  return (float)arg;
}

//Function f2 takes a single input argument of type char and returns an int
int f2(char arg){
  char one = 'a';
  char two = 'A';
  int evaluated;
  evaluated = p + q + (int)arg;
  evaluated = evaluated - (int)one + (int)two;
}
