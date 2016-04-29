#include <stdio.h>	
#include <stdint.h>	
#include <stdlib.h> 
#include <math.h>

/*
	stack.c

	Usage: ./stack

	This program contains basic functions for an array implementation of a stack
	Main function can be used to test functions

	By Shunman Tse		4/17/2015
*/

#define MAXBUFFERSIZE 1000

typedef struct {
	int*	stack;
	int		back;
} Stack;

/**************************************/
/* Global Variables */
Stack	stack;				// stack 
int		stackSize = 1000;	// modify this to change the size of the stack

/**************************************/
/* Function to print out contents of stack */
void printStack() {
	int i;
	if (stack.back > 0) {
		for (i = 0; i < stack.back; i++) {
			printf("%d ", stack.stack[i]);
		}
		printf("\n");
	}
	else {
		printf("The stack is currently empty!\n");
	}
}

/**************************************/
/* Function to push element into the stack */
void push(int item) {
	int i;

	if (stack.back < stackSize) {
		printf("Pushing into stack: %d\n", item);
		stack.stack[stack.back] = item;
		stack.back++;
	}
	else {
		printf("The stack is FULL. Cannot push to stack.\n");
	}
}

/**************************************/
/* Function to pop element from the stack */
void pop() {
	int i;

	if (stack.back == 0) {
		printf("The stack is EMPTY. Cannot pop from stack.\n");
	}
	else {
		stack.back--;
		i = stack.stack[stack.back];
		printf("Popped from stack: %d\n", i);
	}
}

/**************************************/
int main() {
	int i, j, k;

	// Allocate stack for use
	stack.stack = (int*)malloc(stackSize * sizeof(int));
	stack.back = 0;
	
	// Print out the stack before doing anything
	printf("Initial Stack Contents:\n");
	printStack();
	printf("\n");

	// Push some items into the stack
	printf("Pushing some stuff into the stack...\n");
	for (i = 0; i < 10; i++) {
		push(i);
	}

	// Print out the stack
	printf("\nNow the stack looks like this!\n");
	printStack();
	printf("\n");

	// Pop some items from the stack
	printf("Now to pop some stuff from the stack...\n");
	for (i = 0; i < 2; i++) {
		pop();
	}

	// Print out final stack
	printf("\nThe final stack is like this!\n");
	printStack();

	exit(0);
	return 0;
}