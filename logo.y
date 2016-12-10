/**
* @file logo.y
*
* @brief Translates the syntax to the intermediate form
* with 'bison'.
*
* @author Teddy TOUSSAINT, 3TC, group 2
*
* @version 2.3
*  
* @date Monday, January 18th 2016
*/

/* definitions */
%{
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "functions.h"
  int yywrap() {return 1;}
  int yyerror() {printf("ERROR: syntax error.\n"); return 0;}
  PROG root = NULL;
%}

//Terminal symbols :
%token tFORWARD tLEFT tRIGHT tREPEAT VAL '[' ']'

//Types of yylval :
%union { //Changes the type of "yylval".
  INST* inst;
  int val;
};

//Types of symbols :
%type <inst> INST PROG
%type <val> VAL

/* reduction rules */
%%

PROG: INST
  {
    $$ = $1;
    root = $$;
  }
    | PROG INST
  {
    addInst($2, $1);
    $$ = $1;
    root = $$;
  }

INST: tFORWARD VAL
  {
    $$ = createInst(0, $2, NULL);
  }
    | tLEFT VAL
  {
    $$ = createInst(1, $2, NULL);
  }
    | tRIGHT VAL
  {
    $$ = createInst(2, $2, NULL);
  }
    | tREPEAT VAL '[' PROG ']'
  {
    $$ = createInst(3, $2, $4);
  }

/* main function */
%%

int main() {
  printf("************************* BEGINNING *************************\n");
  yyparse();

  printf("Reading the 'LOGO' file :\n");
  display(root, 0);
  printf("\n");

  translateToSVG(root);
  freeProg(root);

  printf("\n**************************** END ****************************\n");
  return 0;
}


