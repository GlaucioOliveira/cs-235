###############################################################
# Program:
#     Assignment 02, STACK
#     Brother XXXX, CS235
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h assignment02.o infix.o 
	g++ -o a.out assignment02.o infix.o 
	tar -cf assignment02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment02.o : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
assignment02.o: stack.h infix.h assignment02.cpp
	g++ -c assignment02.cpp  

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp 

