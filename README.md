This code is a search algorithm that will find a shortest path from the start cell to the finish. It will indicate this path by filling in the character locations on the path with asterisks *; then, it will write the resulting character maze to cout (standard output).

There is a test file in this file and the input file is structured as follows:
The first line of the file should contain two integer numbers indicating the row and column size of the maze. The number of rows indicated will determine how many lines of text follow (1 row per line).
On each line will be one character for each of the indicated number of columns followed by a newline character. The characters can be a period . indicating a space in the maze, a # sign indicating a wall in the maze, a capital S indicating the start location for the search, or a capital F for the desired finish location. It can’t go outside the grid. 

Mainly this code uses the idea of breadth-first search, a simple algorithm that finds not just any path to the exit in a maze, but actually finds a shortest path from the start to the finish. 
