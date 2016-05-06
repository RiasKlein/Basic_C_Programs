/******************************************************************************
	Name: 		Shunman Tse
	NID:		N13382418
	Net ID:		st1637
	Course:		UNIX Programming
	Homework:	1: Basic C

	The Game of Life v2
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>		// For strtol error detection
#include <limits.h>		// For strtol error detection

#define TRUE 1
#define FALSE 0

/* Function Prototypes */
void print_help();
void print_world (int** world, int rows, int columns, int generation);
int** get_input (char filename[], int rows, int columns);
int ng_alive (int** world, int row, int column);
int** next_generation(int** world, int rows, int columns);
int nstrtol (const char *ptr);

/*	print_help
	Function is used to print the valid user input formats
*/
void print_help () {
	printf ("Error: The input is not in a valid format. Valid formats include:\n");
	printf ("\t./life\n");
	printf ("\t./life rows columns\n");
	printf ("\t./life rows columns filename\n");
	printf ("\t./life rows columns filename generations\n");
	printf ("Note: rows and columns must be valid numbers\n");
	exit(1);
}

/*	print_gen
	Function is used to print the GoL world
	Alive cells are represented as *
	Dead  cells are represented as -
*/
void print_world (int** world, int rows, int columns, int generation) {
	int i, j;
	printf ("Generation %i:\n", generation);
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			if (world[i][j]) {
				printf ("*");
			}
			else {
				printf ("-");
			}
		}
		printf ("\n");
	}
	printf ("================================\n");
}

/* 	get_input
	Function is used to read the provided file and generate the proper GoL world
*/
int** get_input (char filename[], int rows, int columns) {
	FILE *fp;
	int i, j;
	char tmp[columns];
	char* result;

	// Dynamically Allocate Matrix to Store Input File
	int** m = (int**) malloc (rows * sizeof(int*));
	for (i = 0; i < rows; i++) {
		m[i] = (int*) malloc (columns * sizeof (int));
	}

	// Initialize Matrix such that All Cells are Dead
	// Note on notation: 	FALSE (or 0) marks a dead cell
	//						TRUE (or 1) marks a live cell
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			m[i][j] = FALSE;
		}
	}

	// Reading the Input File & Storing into Matrix
	fp = fopen (filename, "r");	// open file in read mode
	if (!fp) {
		printf ("Cannot open file %s\n", filename);
		exit(1);
	}

	for (i = 0; i < rows; i++) {
		memset (tmp, 0, columns * sizeof(char) ); // zero tmp to prevent issues
		result = fgets (tmp, columns+2, fp);      // NULL is returned if ERROR
		if (result != NULL) {
			for (j = 0; j < columns; j++) {
				if (tmp[j] == '*') {
						m[i][j] = TRUE;
				}
			}
		}
	}

	fclose(fp); // Close the file since we are done reading

	return m;	
}

/*	ng_alive (where ng is for next generation)
	Function returns whether the cell at the provided row and column
	will be alive in the next generation of the provided world
*/
int ng_alive (int** world, int row, int column) {
	int return_value = FALSE;

	// Note the world that is being passed in IS padded
	// We don't have to worry as much about the corner and edge cases

	// Count the number of live neighbors around this cell
	int live_neighbors = 0;

	// Top Left Position
	if (world[row-1][column-1])
		live_neighbors++;
	// Top Mid Position
	if (world[row-1][column])
		live_neighbors++;
	// Top Right Position
	if (world[row-1][column+1])
		live_neighbors++;

	// Middle Left Position
	if (world[row][column-1])
		live_neighbors++;
	// Middle Right Position
	if (world[row][column+1])
		live_neighbors++;

	// Bottom Left Position
	if (world[row+1][column-1])
		live_neighbors++;
	// Bottom Middle Position
	if (world[row+1][column])
		live_neighbors++;
	// Bottom Right Position
	if (world[row+1][column+1])
		live_neighbors++;

	// Game of Life rules
	// 1. Any live cell with fewer than two live neighbors dies
	// 2. Any live cell with 2 or 3 live neighbors lives on to the next generation
	// 3. Any live cell with more than 3 live neighbors dies
	// 4. Any dead cell with exactly three live neighbors become a live cell
	if (world[row][column]) { // Cell is alive
		if (live_neighbors < 2) { // 1.
			return_value = FALSE;
		}
		else if (live_neighbors == 2 || live_neighbors == 3) { // 2.
			return_value = TRUE;
		}
		else { // 3.
			return_value = FALSE;
		}

	}
	else { // Cell is dead
		if (live_neighbors == 3) // 4.
			return_value = TRUE;
	}

	return return_value;
}

/*	next_generation
	Function takes in the current world and generates the next generation
*/
int** next_generation(int** world, int rows, int columns) {
	int i, j;

	// Copy the current world into a padded version of the world
	int** padded_world = (int**) malloc ((rows+2)* sizeof(int*));
	for (i = 0; i < rows+2; i++) {
		padded_world[i] = (int*) malloc ((columns+2)* sizeof (int));
	}
	for (i = 0; i < (rows+2); i++) {
		for (j = 0; j < (columns+2); j++) {
			padded_world[i][j] = FALSE;
		}
	}
	for (i = 1; i <= rows; i++) {
		for (j = 1; j <= columns; j++) {
			padded_world[i][j] = world[i-1][j-1];
		}
	}
	//print_world(padded_world, rows+2, columns+2, 99);

	// Create a matrix to contain the new GoL world (next generation)
	int** new_world = (int**) malloc (rows * sizeof(int*));
	for (i = 0; i < rows; i++) {
		new_world[i] = (int*) malloc (columns * sizeof (int));
	}

	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			new_world[i][j] = ng_alive(padded_world, (i+1), (j+1));
		}
	}

	//print_world (world, rows, columns, 0);
	//print_world (new_world, rows, columns, 1); 

	/* Free padded_world */
	for (i = 0; i < rows+2; i++) {
		free(padded_world[i]);
	}
	free(padded_world);

	return new_world;
}

/*	nstrtol
	Function uses strtol to convert the provided argument to an int
	Includes error checking for underflow, overflow, or non-int input
	Program's error message will print and program will exit if failure
*/
int nstrtol (const char *ptr) {
	char *endptr;
	int return_value;
	errno = 0;

	return_value = strtol(ptr, &endptr, 10);
	if (endptr == ptr) { // Do we have something that's not a number?
		print_help();
		exit(1);
	}
	if (errno == ERANGE) { // Do we have an over/underflow
		print_help();
		exit(1);
	}

	return return_value;
}

int main(int argc, char **argv) {
	int 	i, j;			// Index variables
	int 	rows;			// Stores the number of rows in world
	int 	columns;		// Stores the number of columns in world
	int 	generations;	// Stores the number of generations to run
	char* 	file;			// Pointer to filename
	int** 	world;			// Pointer to the world setup
	int*** 	ptr_malloc;		// Keeps track of all world mallocs
	char*	ptr_file;		// Keeps track of the filename malloc
	int 	cur_gen = 1;	// Counter for the generation iteration
	int 	filename_len;	// Contains the length of the filename to read from

	/* Default Parameters */
	rows 			= 10;
	columns 		= 10;
	generations 	= 10;
	filename_len 	= 8;

	// Determine whether we need to allocate memory for filename
	// If number of arguments are greater than 3, a user filename was provided
	// Allocate the proper amount of memory for the user filename
	if (argc > 3) {
		filename_len = strlen(argv[3]);
	}
	file = (char*)malloc((filename_len) * sizeof(char));
	ptr_file = file;

	/* Updating Parameters */
	// Acceptable inputs: 	./life
	//						./life rows columns
	//						./life rows columns filename
	//						./life rows columns filename generations 
	switch (argc) {
		case 1: // Input: life
			file = "life.txt";	
			break;
		case 3: // Input: life rows columns
		{
			rows = nstrtol(argv[1]);
			columns = nstrtol(argv[2]);

			file = "life.txt";
			break;
		}
		case 4: // Input: life rows columns filename
		{
			rows = nstrtol(argv[1]);
			columns = nstrtol(argv[2]);

			for (i = 0; i < filename_len; i++) {
				file[i]=argv[3][i];
			}
			break;
		}
		case 5: // Input: life rows column filename generations
		{
			rows = nstrtol(argv[1]);
			columns = nstrtol(argv[2]);

			for (i = 0; i < filename_len; i++) {
				file[i]=argv[3][i];
			}

			generations = nstrtol(argv[4]);
			break;
		}
		default:
			print_help();
			break;
	}

	// Allocate memory for the Game of Life World
	ptr_malloc = (int***) malloc ((generations+1) * sizeof (int**));

	// Generate Game of Life World by using the provided file
	world = get_input (file, rows, columns);
	ptr_malloc[0] = world;
	print_world (world, rows, columns, 0); 

	// Iterate Game of Life generations
	while (cur_gen <= generations) {
		world = next_generation(world, rows, columns);
		ptr_malloc[cur_gen] = world;
		print_world (world, rows, columns, cur_gen);
		cur_gen++; 
	}

	/* Free Allocated Memory */
	for (i = 0; i <= generations; i++) {
		for (j = 0; j < rows; j++) {	
			free (ptr_malloc[i][j]);
		}
		free (ptr_malloc[i]);
	}
	free (ptr_malloc);

	free (ptr_file);

	return 0;
}
