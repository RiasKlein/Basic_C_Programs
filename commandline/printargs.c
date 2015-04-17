#include <stdio.h>	
#include <stdint.h>	
#include <stdlib.h> 
#include <math.h>

/*
	printargs.c

	Usage: ./printargs (argument1) (argument2) ...
		./printargs -v -t -o filename.txt

	Simple program that prints out all arguments provided

	By Shunman Tse		4/17/2015
*/

/**************************************/
int main(int argc, char* argv[]) {
	int i;

	printf("Number of arguments: %d\n", argc);
	for (i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	exit(0);
}