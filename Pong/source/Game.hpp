#ifndef SOURCE_GAME_HPP
#define SOURCE_GAME_HPP

#include "SDL/SDL.h"
#include <vector>


   // Holds 2D coordinates
struct Vector2
{
   float x;
   float y;
};

struct Ball
{
   Vector2 position;
   Vector2 velocity;
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
      SDL_Window*       mWindow;
      SDL_Renderer*     mRenderer;
      bool              mIsRunning;
      Vector2           mLeftPaddlePosition;
      Vector2           mRightPaddlePosition;
      Uint32            mTicksCount;
      int               mLeftPaddleDirection;
      int               mRightPaddleDirection;
      std::vector<Ball> balls;
};

#endif // SOURCE_GAME_HPP
