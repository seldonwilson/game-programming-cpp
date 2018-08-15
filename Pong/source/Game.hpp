#ifndef SOURCE_GAME_HPP
#define SOURCE_GAME_HPP

#include "SDL/SDL.h"


class Game
{
   public:
      Game();
      bool initialize();
      void runLoop();
      void shutdown();

   private:
         // Helper functions for the game loop
      void processInput();
      void updateGame();
      void generateOutput();

         // Data members
      SDL_Window* mWindow;
      SDL_Renderer* mRenderer;
      bool mIsRunning;
};

#endif // SOURCE_GAME_HPP