%{
/**
* @file logo.l
*
* @brief Recognizes the LOGO syntax with 'flex'.
*
* @author Teddy TOUSSAINT, 3TC, group 2
*
* @version 1.0
*  
* @date Tuesday, January 12th 2016
*/

#include <stdio.h>
#include "lib.h"
#include "logo.tab.h"
%}

%%
([1-9][0-9]*)|0 yylval.val = atoi(yytext); return VAL;

"[" return '[';
"]" return ']';

"FORWARD" return tFORWARD;
"LEFT" return tLEFT;
"RIGHT" return tRIGHT;
"REPEAT" return tREPEAT;

[ \t] //Ignore whitespaces.
%%
