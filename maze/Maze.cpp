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
      int j = 0;
      maze.push_back({});
      tileNames.push_back({});
      
      istringstream iss(line);
      int tileNumber;
      while (iss >> tileNumber) {
         maze.at(i).push_back(tileNumber);
         string tileName;

         if (tileNumber % 11 == 0) {
            start.first = i;
            start.second = j;
         } else if (tileNumber % 13 == 0) {
            finish.first = i;
            finish.second = j;
         }
         
         if (tileNumber % 7 == 0) {
            tileName += "N";
         }
         if (tileNumber % 2 == 0) {
            tileName += "E";
         }
         if (tileNumber % 3 == 0) {
            tileName += "S";
         }
         if (tileNumber % 5 == 0) {
            tileName += "W";
         }
         
         tileNames.at(i).push_back(tileName);   
         j++;
      }
      
      ++i;
   }
   
   for (auto row : tileNames) {
      for (auto tile : row) {
         std::cout << tile << " ";
      }
      std::cout << std::endl;
   }
}



bool Maze::canMoveNorth(int row, int col) const
{
   return maze.at(row).at(col) % TILE_NORTH == 0;
}


bool Maze::canMoveEast(int row, int col) const
{
   return maze.at(row).at(col) % TILE_EAST == 0;
}


bool Maze::canMoveSouth(int row, int col) const
{
   return maze.at(row).at(col) % TILE_SOUTH == 0;
}


bool Maze::canMoveWest(int row, int col) const
{
   return maze.at(row).at(col) % TILE_WEST == 0;
}


int Maze::getNumRows() const
{
   return maze.size();   
}


int Maze::getNumCols() const
{
   return maze.at(0).size();
}


std::pair<int, int> Maze::getStart() const
{
   return start;
}


std::pair<int, int> Maze::getFinish() const
{
   return finish;
}


std::string Maze::getTilename(int row, int col) const
{
   return tileNames.at(row).at(col);
}