#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Maze.hpp"


class Player {
public:
   Player(int _row, int _col) {row = _row; col = _col;} 
   void moveUp()    { --row; }
   void moveDown()  { ++row; }
   void moveLeft()  { --col; }
   void moveRight() { ++col; }

   int getRow() const { return row;}
   int getCol() const { return col; }

private:
   int row;
   int col;
};

#endif // PLAYER_HPP
