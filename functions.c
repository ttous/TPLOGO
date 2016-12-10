/**
* @file functions.c
*
* @brief Contains all the functions used.
* 
* @author Teddy TOUSSAINT, 3TC, group 2
*
* @version 3.2
*  
* @date Tuesday, January 19th 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "lib.h"
#include "functions.h"

#define PI 3.14159265

/**
* @fn void display(INST* root, int indent)
*
* @brief Displays a program.
*
* @param root The pointer towards the root instruction of the
* program to display.
* @param indent Number of spaces to put before the instruction,
* according to the number of nested 'REPEAT'.
*
* @warning 'indent' parameter must be initialized at 0. The
* program will increment it itself.
*/
void display(INST* root, int indent){
  int i;
  while (root != NULL){
    if (1){ //TODO ... or not.
      switch (root->key) {
        case 0:
          for(i = 0; i < indent; i++){
            printf("  ");
          }
          printf("FORWARD %d\n", root->val);
          break;
        case 1:
          for(i = 0; i < indent; i++){
            printf("  ");
          }
          printf("LEFT %d\n", root->val);
          break;
        case 2:
          for(i = 0; i < indent; i++){
            printf("  ");
          }
          printf("RIGHT %d\n", root->val);
          break;
        case 3:
          if(root->prog == NULL){
            printf("ERROR: 'REPEAT' without parameter 'prog'.");
          } else {
          for(i = 0; i < indent; i++){
            printf("  ");
          }
          printf("REPEAT %d\n", root->val);
          indent++;
          display(root->prog, indent);
          indent--;
          }
          break;
      }
      root = root->next;
    }
  }

}

/**
* @fn void test_display()
*
* @brief Test the 'display' function.
*
* @note This function prints two results: what the 'display'
* function does, and what it should do. It is up to the user
* to see if the 'display' function passes the test or not,
* by comparing the two results.
*/
void test_display(){
  PROG my_prog;
  INST *inst1, *inst2, *inst3, *inst4, *inst5, *inst6;
  INST *inst7, *inst8;
  
  inst2 = createInst(RIGHT, 90, NULL);
  inst3 = createInst(FORWARD, 10, NULL);
  inst4 = createInst(LEFT, 90, NULL);
  inst5 = createInst(RIGHT, 45, NULL);
  inst6 = createInst(FORWARD, 50, NULL);
  inst7 = createInst(FORWARD, 1, NULL);
  inst8 = createInst(LEFT, 30, NULL);

  addInst(inst3, inst2);
  addInst(inst4, inst2);
  
  inst1 = createInst(REPEAT, 5, inst2);
  
  addInst(inst7, inst1);
  addInst(inst1, inst8);

  my_prog = createInst(REPEAT, 2, inst8);
  
  addInst(inst5, my_prog);
  addInst(inst6, my_prog);
  
  printf("What the 'display' function does:\n");

  display(my_prog, 0);

  printf("\nWhat it should do:\n");
  printf("REPEAT 2\n");
  printf("  LEFT 30\n");
  printf("  REPEAT 5\n");
  printf("    RIGHT 90\n");
  printf("    FORWARD 10\n");
  printf("    LEFT 90\n");
  printf("  FORWARD 1\n");
  printf("RIGHT 45\n");
  printf("FORWARD 50\n");
  
  freeProg(my_prog);
}

/**
* @fn void addInst(INST* inst, INST* prog)
*
* @brief Adds an instruction to a LOGO program.
*
* @param inst The instruction to add.
* @param prog The program to add the instruction to.
*/
void addInst(INST* inst, INST* prog){
  assert((prog != NULL)&&(inst != NULL));
  while (prog->next != NULL){
    prog = prog->next;
  }
  prog->next = inst;
}

/**
* @fn int test_addInst()
*
* @brief Test the 'addInst' function.
*
* @note 'createInst' function is tested before 'addInst' function
* can pass its test.
*
* @return 1 if the function passed the test.
* @return 0 if the function failed it.
*/
int test_addInst(){
  assert(test_createInst());
  PROG prog = createInst(FORWARD, 50, NULL);
  INST* inst = createInst(LEFT, 90, NULL);

  addInst(inst, prog);

  if(prog->next == inst) {
    freeProg(prog);
    return 1;
  }
  else {
    printf("\nERROR: addInst failed its test.\n");
    freeProg(prog);
    return 0;
  }
}

/**
* @fn void freeProg(INST* root)
*
* @brief Frees an allocated memory.
*
* @param root The pointer which the memory to free was
* allocated for.
*/
void freeProg(INST* root){
  INST* inst;
  while(root != NULL) {
    if(root->prog != NULL) {
      freeProg(root->prog);
    }
    inst = root->next;
    free(root);
    root = inst;
  }
}

/**
* @fn INST* createInst(instType key, int val, INST* prog)
*
* @brief Creates an instruction.
*
* @param key The key number corresponding to the type of the
* instruction to create.
* @param val The value of the instruction to create.
* @param prog The pointer towards the program to repeat.
*
* @warning Parameter 'prog' is different from 'NULL' if and only
* parameter 'key' equals '3', which refers to the 'REPEAT'
* instruction.
* @warning This function allocates memory to the returned pointer.
* Function 'freeProg(INST* root)' must be used on the returned
* variable to free the allocated memory.
*
@return The pointer towards the instruction created.
*/
INST* createInst(instType key, int val, INST* prog){
  assert( !(   ((key == 3)&&(prog == NULL))
            || ((key != 3)&&(prog != NULL)) ) );
     
  INST* my_prog = (INST*) malloc(sizeof(INST));
  my_prog->key = key;
  my_prog->val = val;
  my_prog->prog = prog;
  my_prog->next = NULL;

  return my_prog;
}

/**
* @fn int test_createInst()
*
* @brief Test the 'createInst' function.
*
* @return 1 if the function passed the test.
* @return 0 if the function failed it.
*/
int test_createInst(){
  int res = 0;
  
  INST* my_FORWARD = createInst(FORWARD, 10, NULL);
  PROG my_REPEAT = createInst(REPEAT, 3, my_FORWARD);
  
  if( (my_REPEAT->key == 3)
  &&  (my_REPEAT->val == 3)
  &&  (my_REPEAT->prog == my_FORWARD)

  &&  (my_FORWARD->key == 0)
  &&  (my_FORWARD->val == 10) ) {
    res = 1;
  }
  else printf("\nERROR: createInst failed its test.\n");
  freeProg(my_REPEAT);
  return res;
}

/**
* @fn int test_ALL()
*
* @brief Tests the following functions : display, addInst,
* addInstR and createInst.
*
* @note The function 'addInst' can pass its test if an only if
* the function 'createInst' has passed its own test.
*
* @return 1 if all the functions passed the test.
* @return 0 if at least one of them failed it.
*/
int test_ALL(){
  test_display();
  return test_addInst();
}

/**
* @fn void translateToSVG(INST* root)
*
* @brief Translates a LOGO program from a "LOGO" file to an SVG
* program in a "SVG.svg" file.
*
* @param root The first instruction of the program to translate.
*/
void translateToSVG(INST* root){
  FILE* svg;
  svg = fopen("SVG.svg", "w");
  
  writeHeader(svg);

  double x1, y1;
  x1 = 500;
  y1 = 250;

  int angle = 0;
  
  double *px1, *py1;
  px1 = &x1;
  py1 = &y1;

  int* pangle;
  pangle = &angle;

  char* colour = "purple";

  int frir; // "f-r-i-r" = "first repeat is read".

  int* pfrir = &frir;

  printf("Welcome, Human.\n\n");
  printf("I am a C program and my purpose ");
  printf("is to translate 'LOGO' files\ninto 'SVG' files. ");
  printf("I have already read what is inside the 'LOGO'\n");
  printf("file, and I am going to create a displayable ");
  printf("'SVG.svg' file.\n\n");

  //This does not work, unfortunately.
  /*
  printf("First of all, choose the colour to display : ");
  printf("red (r), black (bk), blue (be), yellow (y), ");
  printf("green (g), orange (o), purple (p) : ");
  scanf("%s", &colour);
  printf("%s", colour);
 
  if(strcmp(colour, "r") == 0) colour = "red";
  if(strcmp(colour, "bk") == 0) colour = "black";
  if(strcmp(colour, "be") == 0) colour = "blue";
  if(strcmp(colour, "y") == 0) colour = "yellow";
  if(strcmp(colour, "g") == 0) colour = "green";
  if(strcmp(colour, "o") == 0) colour = "orange";
  if(strcmp(colour, "p") == 0) colour = "purple";
  */

  recTranslateToSVG(root, svg, px1, py1, pangle, colour, pfrir);
  
  printf("                             ...\n\n");
  
  //Test : add a signature to the SVG file.
  /**/
  //T
  fprintf(svg, "<line x1=\"800\" y1=\"450\" ");
  fprintf(svg, "x2=\"810\" y2=\"450\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  fprintf(svg, "<line x1=\"805\" y1=\"450\" ");
  fprintf(svg, "x2=\"805\" y2=\"465\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  
  //E
  fprintf(svg, "<line x1=\"812\" y1=\"450\" ");
  fprintf(svg, "x2=\"822\" y2=\"450\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  fprintf(svg, "<line x1=\"812\" y1=\"450\" ");
  fprintf(svg, "x2=\"812\" y2=\"465\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  fprintf(svg, "<line x1=\"812\" y1=\"457\" ");
  fprintf(svg, "x2=\"822\" y2=\"457\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  fprintf(svg, "<line x1=\"812\" y1=\"465\" ");
  fprintf(svg, "x2=\"822\" y2=\"465\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  
  //D
  fprintf(svg, "<line x1=\"824\" y1=\"450\" ");
  fprintf(svg, "x2=\"824\" y2=\"465\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  fprintf(svg, "<line x1=\"824\" y1=\"450\" ");
  fprintf(svg, "x2=\"831\" y2=\"452\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  fprintf(svg, "<line x1=\"831\" y1=\"452\" ");
  fprintf(svg, "x2=\"834\" y2=\"455\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  fprintf(svg, "<line x1=\"834\" y1=\"455\" ");
  fprintf(svg, "x2=\"834\" y2=\"460\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  fprintf(svg, "<line x1=\"834\" y1=\"460\" ");
  fprintf(svg, "x2=\"831\" y2=\"463\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  fprintf(svg, "<line x1=\"831\" y1=\"463\" ");
  fprintf(svg, "x2=\"824\" y2=\"465\" ");
  fprintf(svg, "stroke=\"black\" />\n");
  /**/

  fprintf(svg, "</svg>\n");

  printf("Done. File 'SVG.svg' created.\n");
  printf("You can now display the SVG program by typing the ");
  printf("command\n'eog SVG.svg'.\n\n");
  printf("Thank you for using this program.\n");
  
  fclose(svg);
}

/**
* @fn void writeHeader(FILE* svg)
*
* @brief Writes the svg header in the svg file.
*
* @param svg The SVG file to write in.
*/
void writeHeader(FILE* svg) {

  fprintf(svg, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");

  fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" ");
  fprintf(svg, "version=\"1.1\" width=\"1000\" height=\"500\">");
  fprintf(svg, "\n");

  fprintf(svg, "<title> Mon exemple LOGO</title>\n");

  fprintf(svg, "<desc>Affichage d'une figure LOGO.</desc>\n");
}

/**
* @fn void recTranslateToSVG(INST* root, FILE* svg, double* px1,
* double* py1, int* pangle, char* colour, int* pfrir)
*
* @brief The recursive version of 'translateToSVG'.
*
* @param root The pointer towards the first instruction of the
* program to translate.
* @param svg The pointer towards the SVG file to write in.
* @param px1 The pointer towards the horizontal coordinate.
* @param py1 The pointer towards the vertical coordinate.
* @param pangle The pointer towards the angle or the drawing arrow.
* @param colour The colour we draw with.
* @param pfrir The pointer towards the integer 'first repeat
* is read', which has value '1' if it is, or '0' if it is not.
*/
void recTranslateToSVG(INST* root, FILE* svg, double* px1, double* py1, int* pangle, char* colour, int* pfrir) {
  double x2, y2;
  int i, j;
  INST* first_repeat;
  char* c[8];
  c[0] = "red";
  c[1] = "black";
  c[2] = "blue";
  c[3] = "yellow";
  c[4] = "green";
  c[5] = "orange";
  c[6] = "purple";
  c[7] = "cyan";
  
  while(root != NULL) {
    switch((int)root->key) {
      
      case 0: //FORWARD
        x2 = *px1 + (root->val) * cos((*pangle)*(PI/180));
        y2 = *py1 - (root->val) * sin((*pangle)*(PI/180));
        fprintf(svg, "<line x1=\"%f\" y1=\"%f\" ", *px1, *py1);
        fprintf(svg, "x2=\"%f\" y2=\"%f\" ", x2, y2);
        fprintf(svg, "stroke=\"%s\" />\n", colour);
        *px1 = x2;
        *py1 = y2;
        break;

      case 1: //LEFT
        *pangle = (*pangle + (root->val)) % 360;
        break;

      case 2: //RIGHT
        *pangle = (*pangle - (root->val)) % 360;
        if(*pangle < 0) *pangle = 360 + (*pangle);
        break;

      case 3: //REPEAT
        if(*pfrir != 1) {
          first_repeat = root;
          j = root->val;
          *pfrir = 1;
        }
        for(i = 0; i < root->val; i++) {
          if(first_repeat == root){
            colour = c[j % 8];
            j--;
          }
          recTranslateToSVG(root->prog, svg, px1, py1, pangle, colour, pfrir);
        }
        break;
    }
    root = root->next;
  }
}



