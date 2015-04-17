#include <stdio.h>	
#include <stdint.h>	
#include <stdlib.h> 
#include <math.h>

/*
	write.c

	Usage: ./write (file name to write to)
		./write test.txt

	Simple program to write data to a provided file name

	By Shunman Tse		4/17/2015
*/

/**************************************/
void write_inputfile(char filename[]) {
	FILE *fp;
	fp = fopen(filename, "w+");

	fprintf(fp, "Here are is a string.\n");
	fprintf(fp, "And some numbers! %d, %f\n", 12, 3.1415927);
	fprintf(fp, "And a char: %c", 'a');

	fclose(fp);
}


/**************************************/
int main(int argc, char* argv[]) {
	int i, j;

	// An input should have been provided as an argument 
	if (argc != 2) {
		printf("Usage: ./write (filename to write to)\n");
		exit(1);
	}

	write_inputfile(argv[1]);

	exit(0);
}