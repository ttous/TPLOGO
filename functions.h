/**
* @file functions.h
*
* @brief Declares all the functions used.
*
* @author Teddy TOUSSAINT, 3TC, group 2
*
* @version 3.1
*  
* @date Monday, January 18th 2016
*/

void display(INST* root, int indent);
void test_display();

void addInst(INST* inst, INST* prog);
int test_addInst();

void freeProg(INST* root);

void translateToSVG(INST* root);
void writeHeader(FILE* svg);
void recTranslateToSVG(INST* root, FILE* svg, double* px1, double* py1, int* angle, char* colour, int* pfrir);

INST* createInst(instType key, int val, INST* prog);
int test_createInst();

int test_ALL();
