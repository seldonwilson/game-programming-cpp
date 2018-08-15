#include <iostream>
#include "Game.hpp"

int main()
{
   Game game;
   if (game.initialize())
   {
      game.runLoop();
   }

   game.shutdown();
   return 0;
}
