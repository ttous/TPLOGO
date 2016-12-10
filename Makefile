# Makefile
# 
# Author : Teddy TOUSSAINT, 3TC, group 2
# Version : 2.1  
# Date : Monday, January 18th 2016

#Variables declaration
CC= gcc
CFLAGS= -Wall -g

#Compiler
all: Doxygen

#Doxygen
Doxygen: Doxyfile
	doxygen Doxyfile

Doxyfile: Test Convert
	doxygen -g

#Intermidiate representation
Test: test.o
	$(CC) $(CFLAGS) $< functions.o -o $@ -lm

test.o: test.c functions.o
	$(CC) $(CFALGS) -c $<

functions.o: functions.c lib.h functions.h
	$(CC) $(CFLAGS) -c $<

#Parser
Convert: flex
	$(CC) $(CFLAGS) functions.c lex.yy.c logo.tab.c -o $@ -lm

bison: logo.y test.o lib.h functions.h
	bison -d logo.y 

flex: logo.l bison lib.h
	flex logo.l

#Testers
tTest: Test
	./Test

tConvert: all
	./Convert < LOGO

#Sweeper
clean:
	rm -f *.o logo.tab* lex.* Test Convert SVG.svg Doxyfile*
