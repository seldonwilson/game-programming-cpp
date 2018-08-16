#ifndef SOURCE_GAME_HPP
#define SOURCE_GAME_HPP

#include "SDL/SDL.h"


   // Holds 2D coordinates
struct Vector2
{
   float x;
   float y;
};


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
      SDL_Window*   mWindow;
      SDL_Renderer* mRenderer;
      bool          mIsRunning;
      Vector2       mPaddlePosition;
      Vector2       mBallPosition;
      Uint32        mTicksCount;
      int           mPaddleDirection;
};

#endif // SOURCE_GAME_HPP
