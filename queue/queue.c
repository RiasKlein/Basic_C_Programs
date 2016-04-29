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
/* Command Flags */
int exit_flag = 0;
int help_flag = 0;
int enqueue_flag = 0;
int print_flag = 0;
int dequeue_flag = 0;
int flush_flag = 0;
int size_flag = 0;

/**************************************/
/* Global Variables */
Queue queue;				// queue 
int queueSize;				// max capacity of the queue
int char_count;				// 
char buffer[MAXBUFFERSIZE];	// buffer to hold user input
char item[MAXBUFFERSIZE];	// buffer to hold enqueue items

/**************************************/
/* Function to confirm command line input */
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
	printf("\n\tHelp\n");
	printf("/dequeue\tremoves element from queue\n");
	printf("/enqueue (item)\tinserts element into queue\n");
	printf("help\t\tprovides help info\n");
	printf("/print\t\tprints out queue\n");
	printf("/quit\t\texits program\n");
	printf("/flush\t\tempties the queue\n");
	printf("/size\t\tprints out size of queue\n");

	printf("\n\tShortcuts\n");
	printf("/d\t\tdequeue\n");
	printf("/e (item)\tenqueue\n");
	printf("/p\t\tprint\n");
	printf("/q\t\tquit\n");
	printf("/f\t\tflush\n");
	printf("/s\t\tsize\n");
	printf("\n");
}

/**************************************/
/* Function to enqueue into queue */
void enqueue() {
	int i, j, k, c;
	char ch;

	if (queue.num < queueSize) {

		// Check how the user enqueued (short cut or not)
		c = checkCommand(buffer, 0, "/enqueue ", 9);
		if (c == 1) {
			// The user did not use the shortcut
			i = 9;
			j = 0;
		}
		else {
			// The user used the shortcut e.g. e item
			i = 3;
			j = 0;
		}

		ch = buffer[i];
		while ((ch != ' ') && (i < char_count)) {
			item[j] = ch;
			i++;
			ch = buffer[i];
			j++;
		}
		item[j] = 0x00;

		sscanf(item, "%d", &k);

		printf("Enqueuing Item: %d\n", k);

		queue.num += 1;
		queue.queue[queue.back] = k;
		queue.back = (queue.back + 1) % queueSize;
	}
	else {
		printf("The queue is full. Cannot enqueue.\n");
	}
}

/**************************************/
/* Function to dequeue from queue */
void dequeue() {
	int i;

	if (queue.num > 0) {
		printf("Deqeued Item: %d\n", queue.queue[queue.front]);
		queue.front = (queue.front + 1) % queueSize;
		queue.num -= 1;
	}
	else {
		printf("The queue is empty. Cannot dequeue.\n");
	}

}

/**************************************/
/* Function to print out queue contents */
void printQueue(){
	int i;

	printf("Printing Queue:\n");
	if (queue.num == 0) {
		printf("The queue is empty right now.\n");
	}
	else {
		for (i = 0; i < queue.num; i++) {
			printf("%d ", queue.queue[(queue.front + i) % queueSize]);
		}
		printf("\n");
	}
	printf("\n");
}

/**************************************/
int main(int argc, char* argv[]) {
	int i, j, k;
	char ch;

	//===== SETTING UP OUR QUEUE
	//=== See if a size was included via command line for the queue otherwise, it's the size of MAXBUFFERSIZE
	queueSize = MAXBUFFERSIZE;
	if (argc > 1) {
		sscanf(argv[1], "%d", &queueSize);
	}

	//=== Initializing values of queue
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
		
		c = checkCommand(buffer, 0, "/quit", 5);
		if (c == 1) { exit_flag = 1; }
		c = checkCommand(buffer, 0, "quit", 4);
		if (c == 1) { exit_flag = 1; }
		c = checkCommand(buffer, 0, "/q\0", 3);
		if (c == 1) { exit_flag = 1; }

		c = checkCommand(buffer, 0, "/help\0", 6);
		if (c == 1) { help_flag = 1; }
		c = checkCommand(buffer, 0, "help", 4);
		if (c == 1) { help_flag = 1; }

		c = checkCommand(buffer, 0, "/enqueue ", 9);
		if (c == 1) { enqueue_flag = 1; }
		c = checkCommand(buffer, 0, "/e ", 3);
		if (c == 1) { enqueue_flag = 1; }

		c = checkCommand(buffer, 0, "/dequeue\0", 9);
		if (c == 1) { dequeue_flag = 1; }
		c = checkCommand(buffer, 0, "/d\0", 3);
		if (c == 1) { dequeue_flag = 1; }

		c = checkCommand(buffer, 0, "/print\0", 7);
		if (c == 1) { print_flag = 1; }
		c = checkCommand(buffer, 0, "/p\0", 3);
		if (c == 1) { print_flag = 1; }

		c = checkCommand(buffer, 0, "/flush\0", 7);
		if (c == 1) { flush_flag = 1; }
		c = checkCommand(buffer, 0, "/f\0", 3);
		if (c == 1) { flush_flag = 1; }
	
		c = checkCommand(buffer, 0, "/size\0", 6);
		if (c == 1) { size_flag = 1; }
		c = checkCommand(buffer, 0, "/s\0", 3);
		if (c == 1) { size_flag = 1; }

		//=====	HANDLING COMMAND

		//=== Handling invalid input
		if (!help_flag && !enqueue_flag && !dequeue_flag && !print_flag && !flush_flag && !size_flag && !exit_flag) {
			printf("Invalid Input. Use \"help\" to see available commands.\n");
		}

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

		//=== Handling the dequeue flag
		if (dequeue_flag) {
			dequeue();

			dequeue_flag = 0; // Reset the dequeue flag
		}

		//=== Handling the print flag
		if (print_flag) {
			printQueue();

			print_flag = 0; // Reset the print flag
		}

		//=== Handling the flush flag
		if (flush_flag) {
			queue.front = 0;
			queue.back = 0;
			queue.num = 0;

			printf("The queue has been emptied.\n");

			flush_flag = 0;
		}

		//=== Handling the size flag
		if (size_flag) {
			printf("Queue Max Size: %d\n", queueSize);
			printf("Number of items: %d\n", queue.num);

			size_flag = 0;
		}

		//===== GET READY TO ACCEPT NEXT COMMAND
		char_count = 0;
	}

	printf("\nExiting interactive queue program.\n");

	exit(0);
	return 0;
}