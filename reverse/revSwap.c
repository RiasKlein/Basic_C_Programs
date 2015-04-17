#include <stdio.h>	// printf
#include <stdint.h>	// uint64
#include <stdlib.h> // exit()
#include <math.h>

/*
	revSwap.c

	Usage: ./revSwap (input to reverse)

	This is a simple program that will reverse the argument string using swaps

	By Shunman Tse		4/17/2015
*/

/**************************************/
/* Global Variables */
int input_size;
char* input_reversed;

/**************************************/
/* Function that reverses the input by using a dynamically allocated buffer */
char* reverseSWAP(char input[]){
	char ch;
	int i, num_swaps;

	//===== Finding the size of the input 
	//	We will do so by counting chars until end of input
	input_size = 0;

	ch = input[0];
	while (ch != '\0') {
		input_size++;
		ch = input[input_size];
	}

	//===== Finding the number of swaps that we need
	num_swaps = input_size / 2;

	//===== Swapping the chars of input
	for (i = 0; i < num_swaps; i++) {
		ch = input[i];
		input[i] = input[input_size - 1 - i];
		input[input_size - 1 - i] = ch;
	}

	return input;
}

/**************************************/
int main(int argc, char* argv[]) {

	// An input should have been provided as an argument 
	if (argc != 2) {
		printf("Usage: ./revSwap (input to reverse)\n");
		exit(1);
	}

	input_reversed = (char*)malloc(input_size * sizeof(char));
	input_reversed = reverseSWAP(argv[1]);
	printf("%s\n", input_reversed);

	exit(0);
}