/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);
// Add other prototypes here for any functions you wish to use
bool SFvalid(char**, int, int);
bool invalidChar(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) 
{
  int rows, cols;
  //result;
  char** mymaze=NULL;
  const char* invalid_char_message = "Error, invalid character.";
  const char* invalid_maze_message = "Invalid maze.";
  const char* no_path_message = "No path could be found!";

  if(argc < 2)
  {
    cout << "Please provide a maze input file" << endl;
    return 1;
  }

  mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1

  // For checkpoint 2 you should check the validity of the maze
  // You may do so anywhere you please and can abstract that
  // operation with a function or however you like.

  //================================
  // When working on Checkpoint 4, you will need to call maze_search
  // and output the appropriate message or, if successful, print
  // the maze.  But for Checkpoint 1, we print the maze, regardless.
  
  // print_maze(mymaze, rows, cols);
  
  
  //================================
  // ADD CODE BELOW 
  if (!SFvalid(mymaze, rows, cols)) //deallocating
  {
    cout << invalid_maze_message << endl;
    for (int i = 0; i < rows; i++) //have deallocation in each if there's an error in the maze
    {
      delete[] mymaze[i];
    }
    delete[] mymaze;
    return -1;
  }

  if (!invalidChar(mymaze, rows, cols))
  {
    cout << invalid_char_message << endl;
    for (int i = 0; i < rows; i++) 
    {
      delete[] mymaze[i];
    }
    delete[] mymaze;
    return 0;
  }

  if (!maze_search(mymaze, rows, cols))
  {
    cout << no_path_message << endl;
    for (int i = 0; i < rows; i++) 
    {
      delete[] mymaze[i];
    }
    delete[] mymaze;
    return 0;
  }
  
  cout << rows << " " << cols << endl; 
  print_maze(mymaze, rows, cols);
  // to delete all memory that read_maze allocated: CHECKPOINT 2
  for (int i = 0; i < rows; i++) //deallocation when maze is okay
  {
    delete[] mymaze[i];
  }
  delete[] mymaze;
  
  return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
  // *** You complete **** CHECKPOINT 4
  Location** predecessor = new Location*[rows]; //intializing predecessor
  for (int i = 0; i < rows; ++i)
  {
    predecessor[i] = new Location[cols];
    for (int j = 0; j < cols; j++)
    {
      predecessor[i][j].row = -1; 
      predecessor[i][j].col = -1;
    }
  }

  bool** explored = new bool*[rows]; //intializing explored
  for (int i = 0; i < rows; ++i)
  {
    explored[i] = new bool[cols];
    for (int j = 0; j < cols; j++)
    {
      explored[i][j] = false;
    }
  }

  Queue q(rows*cols); 
  Location start;

  for (int i = 0; i < rows; ++i) //finding where S is located in the maze
  {
    for (int j = 0; j < cols; j++)
    {
      if (maze[i][j]=='S')
      {
        explored[i][j] = true; //mark the start location as explored
        start.row = i;
        start.col = j;
        q.add_to_back(start); //add start location to q
      }
    }
  }

  Location current;
  bool status = false; //if there is a F in the maze

  while(!q.is_empty()) //while q is not empty do
  {
    Location loc = q.remove_from_front(); //set loc = get the first item
    current.row = loc.row;
    current.col = loc.col; 

    if (loc.row > 0) //if north is not out of bounds
    {
      if (maze[loc.row-1][loc.col] == 'F') //if you found F, immedietely break
      {
        status = true;
        break;
      }
      if (maze[loc.row-1][loc.col] != '#' && !explored[loc.row-1][loc.col]) //if not a wall and not explored
      {
        explored[loc.row-1][loc.col] = true;  
        Location n_loc;
        n_loc.row=loc.row-1;
        n_loc.col=loc.col;  
        q.add_to_back(n_loc);
        predecessor[n_loc.row][n_loc.col] = loc;
      }
    }
    if (loc.row < rows - 1) //for south is not out of bounds
    {
      if (maze[loc.row+1][loc.col] == 'F')
      {
        status = true;
        break;
      }
      if(maze[loc.row+1][loc.col] != '#' && !explored[loc.row+1][loc.col])
      {
        explored[loc.row+1][loc.col] = true;
        Location s_loc;
        s_loc.row = loc.row+1;
        s_loc.col = loc.col;
        q.add_to_back(s_loc);
        predecessor[s_loc.row][s_loc.col] = loc;
      }
    }
    if (loc.col > 0) //for west is not out of bounds
    {
      if (maze[loc.row][loc.col-1] == 'F') 
      {
        status = true;
        break;
      }
      if (maze[loc.row][loc.col-1] != '#' && !explored[loc.row][loc.col-1])
      {
        explored[loc.row][loc.col-1] = true;
        Location w_loc;
        w_loc.row = loc.row;
        w_loc.col = loc.col-1;
        q.add_to_back(w_loc);
        predecessor[w_loc.row][w_loc.col] = loc;
      }
    }
    if (loc.col < cols - 1) //for east is not out of bounds
    {
      if (maze[loc.row][loc.col+1] == 'F') 
      {
        status = true;
        break;
      }
      if (maze[loc.row][loc.col+1] != '#' && !explored[loc.row][loc.col+1])
      {
        explored[loc.row][loc.col+1] = true;
        Location e_loc;
        e_loc.row = loc.row;
        e_loc.col = loc.col+1;
        q.add_to_back(e_loc);
        predecessor[e_loc.row][e_loc.col] = loc;
      }
    }
  }

  while(status) //if there is an F
  {
    if (maze[current.row][current.col] == 'S') //if S and F are next to each other
      break;
    maze[current.row][current.col] = '*'; //if not, trace back and set *
    current = predecessor[current.row][current.col];
    if (maze[current.row][current.col] == 'S') //stop if you see a S
      break;
  }

  //deallocating predecessor and explored
  for (int i = 0; i < rows; ++i)
  {
    delete[] predecessor[i]; 
  }
  delete[] predecessor;

  for (int i = 0; i < rows; i++)
  {
    delete[] explored[i];
  }
  delete[] explored;

  return status;
}
    
bool SFvalid(char** maze, int rows, int cols) //checking if there's one S and one F in the maze
{
  bool s_valid = false;
  bool f_valid = false;
  int s = 0;
  int f = 0;
  for (int i = 0; i < rows; i++) //checking each location in maze
  {
    for (int j = 0; j < cols; j++)
    {
      if (maze[i][j] == 'S')
      {
        s_valid = true;
        s++;
      }
      if (maze[i][j] == 'F')
      {
        f_valid = true;
        f++;
      }
    }
  }
  if (s != 1) //if there is more than one 'S'
    s_valid = false;
  if (f != 1)
    f_valid = false;
  return (s_valid && f_valid);
}

bool invalidChar(char**maze, int rows, int cols) //checking if there is an Invalid char in maze
{
  bool charValid = false;
  int invalid_char = 0;
  for (int i = 0; i < rows; ++i) //checking each location in maze
  {
    for (int j = 0; j < cols; ++j)
    {
      if (maze[i][j] == '#' || maze[i][j] == '.' || maze[i][j] == 'S' || maze[i][j] == 'F')
      {
        charValid = true;
      }
      else //if not '#', '.', 'S', and 'F'
      {
        invalid_char++;
      }
    }
  }
  if (invalid_char > 0)
  {
    charValid = false;
  }
  return charValid;
}

