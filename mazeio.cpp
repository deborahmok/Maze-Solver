/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols)
{
  ifstream readfile(filename);
  if(readfile.fail())
  {
    return NULL;
  }
  readfile >> *rows >> *cols; //save the first two #s
  char** rowPNT = new char*[*rows]; //dynamically allocating 2Darray
  for (int i = 0; i < *rows; i++)
  {
    rowPNT[i] = new char[*cols]; //declare each size to each box
    for (int j = 0; j < *cols; j++) //focusing on the current column
    {
      readfile >> rowPNT[i][j]; //storing each index into the array from the file
    }
  }
  return rowPNT;
  // *** You complete **** CHECKPOINT 1
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      cout << maze[i][j];
    }
    
    cout << endl;
  }
    // *** You complete **** CHECKPOINT 1
}

