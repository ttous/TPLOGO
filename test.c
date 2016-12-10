/**
* @file test.c
*
* @brief Tests the functions 'addInst', 'createInst'
* and 'display'.
*
* @author Teddy TOUSSAINT, 3TC, group 2
*
* @version 2.3
*  
* @date Tuesday, January 12th 2016
*/

#include <stdio.h>
#include "lib.h"
#include "functions.h"
#include <math.h>

int main(int argc, char** argv){
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~ BEGINNING ~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

  if(test_ALL()){
    printf("\nThe functions addInst and createInst");
    printf(" have passed their test.\nYou can check above for");
    printf(" function 'display'.\n");
  }

  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  return 0;
}
