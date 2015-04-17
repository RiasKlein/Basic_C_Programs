#include <stdio.h>	
#include <stdint.h>	
#include <stdlib.h> 
#include <math.h>

/*
	readtxt.c

	Usage: ./readtxt (filename to read)
		e.g. ./readtxt story.txt

	Simple program to read in file and store in char array

	By Shunman Tse		4/17/2015
*/

char*	input;	// buffer to hold chars
int		input_size;

/**************************************/
void get_input(char filename[]) {
	FILE *fp;
	int i, j;
	char ch;
	input_size = 0;

	//===== Count Size of File
	// The size of the file will be used to allocate our buffer input
	fp = fopen(filename, "r");	// open file in read mode
	if (!fp) {
		printf("Cannot open file %s\n", filename);
		exit(1);
	}

	while (ch = fgetc(fp) != EOF) {
		input_size++;
	}

	fclose(fp);					// close file (we will open again to read from the start)

	//===== Dynamically Allocate Input
	input = (char*)malloc(input_size * sizeof(char));
	if (!input) {
		printf("Cannot allocate input!\n");
		exit(1);
	}

	//===== Reading the File & Storing into Buffer
	fp = fopen(filename, "r");	// open file in read mode 
	if (!fp) {
		printf("Cannot open file %s\n", filename);
		exit(1);
	}

	// Store the File into Buffer
	for (i = 0; i < input_size; i++) {
		fscanf(fp, "%c", &input[i]);
	}

	fclose(fp);					// close the file because we are done
}

/**************************************/
int main(int argc, char* argv[]) {
	int i, j;

	// An input should have been provided as an argument 
	if (argc != 2) {
		printf("Usage: ./readtxt (filename to read)\n");
		exit(1);
	}

	get_input(argv[1]);

	// Printing the file to verify that it's stored
	for (i = 0; i < input_size; i++) {
		printf("%c", input[i]);
	}

	exit(0);
}