#include "Game.hpp"
#include <cmath>

const int thickness    = 15;
const int paddleHeight = 100.0f;

Game::Game()
: mWindow(nullptr)
, mIsRunning(true)
, mBallPosition{512, 384}
, mPaddlePosition{15, 384}
, mBallVelocity{-200.0f, 235.0f}
, mTicksCount(0)
, mPaddleDirection(0)
{ }


bool Game::initialize()
{

      // If SDL_Init() fails
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
   {
      SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
      return false;
   }

   mWindow = SDL_CreateWindow(
      "Pong", // Window title
      100,    // Top-left x-coord of window
      100,    // Top-right y-coord of window
      1024,   // Width of window
      768,    // Height of window
      0       // Flags (0 for no flags set)
   );

      // If SDL_CreateWindow() fails
   if (mWindow == nullptr)
   {
      SDL_Log("Failed to create window: %s", SDL_GetError());
      return false;
   }

   mRenderer = SDL_CreateRenderer(
      mWindow, // Window to create renderer for
      -1,      // Driver to use (usually -1)
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
   );

   if (mRenderer == nullptr)
   {
      SDL_Log("Failed to create renderer: %s", SDL_GetError());
      return false;
   }

   return true;
}


void Game::shutdown()
{
   SDL_DestroyWindow(mWindow);
   SDL_DestroyRenderer(mRenderer);
   SDL_Quit();
}


void Game::runLoop()
{
   while (mIsRunning)
   {
      processInput();
      updateGame();
      generateOutput();
   }
}


void Game::processInput()
{
   SDL_Event event;
   while (SDL_PollEvent(&event))
   {
      switch (event.type)
      {
         case SDL_QUIT:
            mIsRunning = false;
            break;
      }
   }

   const Uint8* state = SDL_GetKeyboardState(NULL);
   if (state[SDL_SCANCODE_ESCAPE])
      mIsRunning = false;

   mPaddleDirection = 0;
   if (state[SDL_SCANCODE_W])
      mPaddleDirection -= 1;
   if (state[SDL_SCANCODE_S])
      mPaddleDirection += 1;
}


void Game::updateGame()
{
      // Wait for at least 16 ms to pass
   while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
      ;

      // Difference in ticks from last frame (in seconds)
   float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

      // Limit maximum amount for deltaTime
   if (deltaTime > 0.05f)
      deltaTime = 0.05f;

      // Tick count updated for next frame
   mTicksCount = SDL_GetTicks();

   if (mPaddleDirection != 0)
   {
      mPaddlePosition.y += mPaddleDirection * 300.0f * deltaTime;

         // Ensure paddle doesn't move off the screen
      if (mPaddlePosition.y < paddleHeight / 2.0f + thickness)
         mPaddlePosition.y = paddleHeight / 2.0f + thickness;
      else if (mPaddlePosition.y > 768 - paddleHeight / 2.0f - thickness)
         mPaddlePosition.y = 768 - paddleHeight / 2.0f - thickness;
   }

   mBallPosition.x += mBallVelocity.x * deltaTime;
   mBallPosition.y += mBallVelocity.y * deltaTime;

      // Handle ball bouncing against top, bottom, and right walls
   if (mBallPosition.y <= thickness * 1.4f && mBallVelocity.y < 0.0f)
      mBallVelocity.y *= -1.0f;
   else if (mBallPosition.y >= (768 - thickness * 1.4f) && mBallVelocity.y > 0.0f)
      mBallVelocity.y *= -1.0f;
   else if (mBallPosition.x >= (1024 - thickness * 1.4) && mBallVelocity.x > 0.0f)
      mBallVelocity.x *= -1.0f;

   int diff = abs(mBallPosition.y - mPaddlePosition.y);

   if (
      diff <= paddleHeight / 2.0f &&
      mBallPosition.x <= 28.0f    &&
      mBallPosition.x >= 20.0f    &&
      mBallVelocity.x < 0.0f
   )
      mBallVelocity.x *= -1.0f;

      // End game if ball went off screen
   if (mBallPosition.x <= 0.0f)
      mIsRunning = false;

}


void Game::generateOutput()
{
      // Set draw color to black and render entire window
   SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
   SDL_RenderClear(mRenderer);

      // Set draw color to white
   SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

      // Create and draw top wall
   SDL_Rect wall{0, 0, 1024, thickness};
   SDL_RenderFillRect(mRenderer, &wall);

      // Draw bottom wall
   wall.y = 768 - thickness;
   SDL_RenderFillRect(mRenderer, &wall);

      // Draw right wall
   wall.x = 1024 - thickness;
   wall.y = 0;
   wall.w = thickness;
   wall.h = 768 + thickness * 2;
   SDL_RenderFillRect(mRenderer, &wall);

      // Draw ball
   SDL_Rect ball {
      static_cast<int>(mBallPosition.x - thickness / 2),
      static_cast<int>(mBallPosition.y - thickness / 2),
      thickness,
      thickness
   };
   SDL_RenderFillRect(mRenderer, &ball);

      // Draw Paddle
   SDL_Rect paddle {
      static_cast<int>(mPaddlePosition.x - thickness / 2),
      static_cast<int>(mPaddlePosition.y - paddleHeight / 2),
      thickness,
      paddleHeight
   };
   SDL_RenderFillRect(mRenderer, &paddle);


      // Swap front and back buffers (update screen)
   SDL_RenderPresent(mRenderer);
}
