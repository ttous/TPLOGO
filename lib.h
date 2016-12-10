/**
* @file lib.h
*
* @brief Declares the structure of an instruction.
*
* @author Teddy TOUSSAINT, 3TC, group 2
*
* @version 1.0
*  
* @date Tuesday, January 12th 2016
*/

typedef enum {FORWARD, LEFT, RIGHT, REPEAT} instType;

/**
* @struct INST
* 
* @brief The instruction structure contains its type, its value,
* the pointer to the program to repeat if it is a "REPEAT"
* instruction, the pointer to the next instruction if there is
* any.
*/
typedef struct inst{
  instType key;
  int val;
  struct inst* prog;
  struct inst* next;
} INST;

typedef INST* PROG;

