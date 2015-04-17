#include <stdio.h>	
#include <stdint.h>	
#include <stdlib.h> 
#include <math.h>

/*
	readnxn.c

	Usage: ./read (filename to read)

	Simple program to read in nxn matrix of ints into 2D array

	By Shunman Tse		4/17/2015
*/

int**	input;	// 2D matrix to hold nxn matrix of input file
int		n;		// size of row (and column)

/**************************************/
void get_input(char filename[]) {
	FILE *fp;
	int i, j;
	n = 0;

	//===== Count Size of Row
	//	We find the length of a row in order to allocate our matrix
	//	Matrix input will contain the nxn matrix in the provided file
	fp = fopen(filename, "r");	// open file in read mode
	if (!fp) {
		printf("Cannot open file %s\n", filename);
		exit(1);
	}

	int m = 0;
	while (fscanf(fp, "%d ", &i) == 1) {
		m++;
	}
	n = (int)sqrt((double)m);	// The file contains an nxn matrix and therefore n = sqrt (m)

	fclose(fp);					// close file (we will open again to read from the start)

	//===== Dynamically Allocate Matrix to Store Input (using n)
	input = (int**)malloc(n * sizeof(int*));
	if (!input) {
		printf("Cannot allocate input!\n");
		exit(1);
	}

	for (i = 0; i < n; i++) {
		input[i] = (int*)malloc(n * sizeof(int));

		if (!input[i]) {
			printf("Cannot allocate input[%d]!\n", i);
			exit(1);
		}
	}

	//===== Reading the file & storing into matrix
	fp = fopen(filename, "r");	// open file in read mode 
	if (!fp) {
		printf("Cannot open file %s\n", filename);
		exit(1);
	}

	// Read file and store into proper location in matrix a
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fp, "%d ", &input[i][j]);
		}
	}

	fclose(fp);					// close the file because we are done
}

/**************************************/
int main(int argc, char* argv[]) {
	int i, j;

	// An input should have been provided as an argument 
	if (argc != 2) {
		printf("Usage: ./readnxn (filename to read)\n");
		exit(1);
	}

	get_input(argv[1]);

	//===== Print out the N x N matrix
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", input[i][j]);
		}
		printf("\n");
	} 

	exit(0);
}