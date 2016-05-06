/******************************************************************************
	Name: 		Shunman Tse

	The Game of Life v2	
******************************************************************************/

Approach to the assignment:
The Game of Life world is represented as a 2D array of ints. 
A value of 1 means that the cell is ALIVE, while a 0 represents a DEAD cell.

Notes:
1. 	The program does not check for whether the user is inputting proper numbers
	for the rows and columns parameters. In the case that the user writes in a
	command such as: ./life too bad life.txt 20
	Generations will be listed from 0 ~ 20, however no world is displayed.
2. 	Valgrind was used to ensure that the malloc'ed memory was freed. 
	The command used was:
		valgrind --leak-check=full -v ./life
	Valgrind seems to be happy enough since it claims that:
		"no leaks are possible"
3.	The makefile is run with the command:
		make -f makefile
4.	To make number management easier, the GoL world is normally NOT padded.
	However, padding is added on during the steps to generate the next
	iteration of the world. The padding makes it easier to write the neighbor
	counting function to determine what to do with a cell. 
5. 	I tried to keep the lines to a length of 80, but there are some that goes
	a bit over the limit... to a length of 84 or something close to that.

Changes in v2 submission:
1. 	Added in function called nstrtol (new strtol) that uses strtol to convert
	the provided argument into an int. Checks are added in to make sure that
	the strtol function did not encounter issues such as overflow, underflow,
	or the input wasn't a number.
	If an invalid input was given, a message is printed and the program exits.