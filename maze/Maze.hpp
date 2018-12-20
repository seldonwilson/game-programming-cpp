#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <string>

using std::vector;
using std::string;

class Maze {
private:
   vector<vector<int>> maze;
   
public:
   Maze(string mazeFile);
   
      /* Takes a position in the maze and determine if there's an opening in the
         specified direction.
      */   
   bool canMoveNorth(int row, int col);
   bool canMoveEast(int row, int col);
   bool canMoveSouth(int row, int col);
   bool canMoveWest(int row, int col);
};


#endif // MAZE_HPP
