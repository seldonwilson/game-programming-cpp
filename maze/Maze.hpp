#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <string>

#define TILE_EAST    2
#define TILE_SOUTH   3
#define TILE_WEST    5
#define TILE_NORTH   7
#define TILE_START  11
#define TILE_FINISH 13

using std::vector;
using std::string;

class Maze {
private:
   vector<vector<int>> maze;
   
public:
   Maze(string mazeFilename);
   
      /* Takes a position in the maze and determine if there's an opening in the
         specified direction.
      */   
   bool canMoveNorth(int row, int col);
   bool canMoveEast(int row, int col);
   bool canMoveSouth(int row, int col);
   bool canMoveWest(int row, int col);
};


#endif // MAZE_HPP
