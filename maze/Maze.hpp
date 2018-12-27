#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <string>
#include <utility>

#define TILE_EAST    2
#define TILE_SOUTH   3
#define TILE_WEST    5
#define TILE_NORTH   7
#define TILE_START  11
#define TILE_FINISH 13

using std::vector;
using std::string;

class Maze {   
public:
   Maze(string mazeFilename);
   
      /* Takes a position in the maze and determine if there's an opening in the
         specified direction.
      */   
   bool canMoveNorth(int row, int col) const;
   bool canMoveEast (int row, int col) const;
   bool canMoveSouth(int row, int col) const;
   bool canMoveWest (int row, int col) const;
   
      // Gets some basic information about the maze
   int getNumRows() const;
   int getNumCols() const;
   std::pair<int, int> getStart()  const;
   std::pair<int, int> getFinish() const;

      // Gets the filename based on the given position
   std::string getTilename(int row, int col) const;

private:
   vector<vector<int>>    maze;
   vector<vector<string>> tileNames;
   std::pair<int, int>    start;
   std::pair<int, int>    finish;
};


#endif // MAZE_HPP
