#include <stdio.h>	
#include <stdint.h>	
#include <stdlib.h> 
#include <math.h>

/*
	queue.c

	Usage: ./queue (optional size)

	Interactive int queue

	By Shunman Tse		4/17/2015
*/

#define MAXBUFFERSIZE 1000

typedef struct {
	int*	queue;
	int		front;
	int		back;
	int		num;
} Queue;

/**************************************/
/* Commands */
int exit_flag = 0;
int help_flag = 0;
int enqueue_flag = 0;
int print_flag = 0;

/**************************************/
/* Global Variables */
Queue queue;
int char_count;
int queueSize;
char buffer[MAXBUFFERSIZE];	// buffer to hold user input
char item[MAXBUFFERSIZE];	// buffer to hold enqueue items

/**************************************/
int checkCommand(char* command_buffer, int buffer_start, char* command, int command_size) {
	int i;

	for (i = 0; i < command_size; i++) {
		if (command_buffer[i+buffer_start] != command[i]) {
			return 0;
		}
	}
	return 1;
}

/**************************************/
/* Help */
void printHelp() {
	printf("\n\t\tHelp\n\n");
	printf("dequeue\t\tremoves element from queue and prints it to screen\n");
	printf("enqueue (input)\tinserts element into queue\n");
	printf("help\t\tprovides help info\n");
	printf("print\t\tprints out queue\n");
	printf("quit\t\texits program\n");
	printf("reset\t\tzeroes the queue\n");
	printf("size\t\tprints out size of queue\n");
	printf("\n");
}

/**************************************/
void enqueue() {
	int i, j, k;
	char ch;

	// Getting the user's item
	i = 8;
	j = 0;

	ch = buffer[i];
	while ((ch != ' ') && (i < char_count)) {
		item[j] = ch;
		i++;
		ch = buffer[i];
		j++;
	}
	item[j] = 0x00;

	sscanf(item, "%d", &k);

	queue.num += 1;
	queue.queue[queue.back] = k;
	queue.back += 1;
}

/**************************************/
void printQueue(){
	int i;

	printf("Printing Queue:\n");
	for (i = 0; i < queue.num; i++) {
		printf("%d ", queue.queue[(queue.front + i) % queueSize]);
	}
	printf("\n\n");
}

/**************************************/
int main(int argc, char* argv[]) {
	int i, j, k;
	char ch;

	//===== SETTING UP OUR QUEUE
	// See if a size was included via command line for the queue otherwise, it's the size of MAXBUFFERSIZE
	queueSize = MAXBUFFERSIZE;
	if (argc > 1) {
		sscanf(argv[1], "%d", &queueSize);
	}

	// Initializing values
	queue.front = 0;
	queue.back = 0;
	queue.num = 0;
	queue.queue = (int*)malloc(queueSize * sizeof(int));
	if (!queue.queue) {
		printf("Could not allocate queue of Queue struct!\n");
	}

	//=====	MAIN USER INTERACTION LOOP
	char_count = 0;
	while (!exit_flag) {

		//===== READING USER COMMAND
		while (char_count == 0) {	// make sure that the user enters something
			// Read User Input
			printf("Command: ");
			ch = getchar();

			while ((ch != '\n') && (char_count < MAXBUFFERSIZE)) {
				buffer[char_count++] = ch;
				ch = getchar();
			}
			buffer[char_count] = 0x00;	/* null terminate buffer */
		}

		//=====	PROCESSING COMMAND

		//=== Check what the command is and how to handle it
		int c;
		
		c = checkCommand(buffer, 0, "quit", 4);
		if (c == 1) { exit_flag = 1; }

		c = checkCommand(buffer, 0, "help", 4);
		if (c == 1) { help_flag = 1; }

		c = checkCommand(buffer, 0, "enqueue", 7);
		if (c == 1) { enqueue_flag = 1; }

		c = checkCommand(buffer, 0, "print", 5);
		if (c == 1) { print_flag = 1; }
	
		//=====	HANDLING COMMAND

		//=== Handling the help flag
		if (help_flag) {
			printHelp();

			help_flag = 0; // Reset help flag since we handled it
		}

		//=== Handling the enqueue flag
		if (enqueue_flag) {
			enqueue();

			enqueue_flag = 0; // Reset enqueue flag since we handled it
		}

		//=== Handling the print flag
		if (print_flag) {
			printQueue();

			print_flag = 0; // Reset the print flag
		}

		//===== GET READY TO ACCEPT NEXT COMMAND
		//printf("char_count: %d buffer: %s\n", char_count, buffer);
		char_count = 0;
	}

	exit(0);
	return 0;
}