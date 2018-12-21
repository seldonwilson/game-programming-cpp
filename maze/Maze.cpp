#include "Maze.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

Maze::Maze(string mazeFilename)
{
   ifstream mazeFile(mazeFilename);

   string line;
   int i = 0;
   while (getline(mazeFile, line))
   {
      maze.push_back({});
      
      istringstream iss(line);
      int tileNumber;
      while (iss >> tileNumber)
         maze.at(i).push_back(tileNumber);
      
      ++i;
   }
}



bool Maze::canMoveNorth(int row, int col)
{
   return maze.at(row).at(col) % TILE_NORTH == 0;
}


bool Maze::canMoveEast(int row, int col)
{
   return maze.at(row).at(col) % TILE_EAST == 0;
}


bool Maze::canMoveSouth(int row, int col)
{
   return maze.at(row).at(col) % TILE_SOUTH == 0;
}


bool Maze::canMoveWest(int row, int col)
{
   return maze.at(row).at(col) % TILE_WEST == 0;
}
