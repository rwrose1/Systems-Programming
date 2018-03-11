#include <stdio.h>

#include "file1header.h"
#include "globals.h"

void main (void){
  //globals
  p = 13;
  q = 32;

  //Local variables
  int i = 5;
  char c = 'x';

  //temps
  float tempFloat;
  int tempInt;

  //declare and initialized variable passed to f1
  int passedToOne = i + p + q;

  //f1
  puts("The value of the first function is: ");
  tempFloat = f1(passedToOne);
  printf("%f\n", tempFloat);

  //f2
  puts("The value of the second function is: ");
  tempInt = f2(c);
  printf("%d\n", tempInt);
}
