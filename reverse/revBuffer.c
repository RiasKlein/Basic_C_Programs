#include <stdio.h>	// printf
#include <stdint.h>	// uint64
#include <stdlib.h> // exit()
#include <math.h>

/*
	reverse.c

	Usage: ./revBuffer (input to reverse)

	This is a simple program that will reverse the user's input using a buffer.

	By Shunman Tse		4/17/2015
*/

/**************************************/
/* Global Variables */
int input_size;			// Length of the input
char* input_reversed;	// Reverse of the input

/**************************************/
/* Function that reverses the input by using a dynamically allocated buffer */
char* reverseBUFFER(char input[]){
	int i;

	//===== Finding the size of the input 
	//	We will do so by counting chars until end of input
	input_size = 0;

	char ch = input[0];
	while (ch != '\0') {
		input_size++;
		ch = input[input_size];
	}

	//===== Dynamically allocate a buffer to hold our reversed string
	input_reversed = (char*)malloc(input_size * sizeof(char));

	//===== Reverse our input and store it into the buffer
	for (i = 0; i < input_size; i++) {
		input_reversed[i] = input[input_size - 1 - i];
	}

	//===== Return the result
	return input_reversed;
}

/**************************************/
int main(int argc, char* argv[]) {

	// An input should have been provided as an argument 
	if (argc != 2) {
		printf("Usage: ./revBuffer (input to reverse)\n");
		getchar();		// Wait for keypress so user can see
		exit(1);
	}

	input_reversed = reverseBUFFER(argv[1]);
	printf("%s\n", input_reversed);

	getchar();
	exit(0);
}