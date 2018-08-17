#include "Game.hpp"
#include <cmath>
#include <iostream>

const int thickness = 15;
const int paddleHeight = 100.0f;

Game::Game()
: mWindow(nullptr)
, mRenderer(nullptr)
, mIsRunning(true)
, mLeftPaddlePosition{15, 384}
, mRightPaddlePosition{1009, 384}
, mTicksCount(0)
, mLeftPaddleDirection(0)
, mRightPaddleDirection(0)
, balls{{{512, 384}, {-250.0f, 235.0f}}, {{400, 500}, {200.0f, 275.0f}}}
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

   mLeftPaddleDirection = 0;
   mRightPaddleDirection = 0;
   if (state[SDL_SCANCODE_W])
      mLeftPaddleDirection -= 1;
   if (state[SDL_SCANCODE_S])
      mLeftPaddleDirection += 1;
   if (state[SDL_SCANCODE_UP])
      mRightPaddleDirection -= 1;
   if (state[SDL_SCANCODE_DOWN])
      mRightPaddleDirection += 1;
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

      // Update left paddle position based on keyboard input
   if (mLeftPaddleDirection != 0)
   {
      mLeftPaddlePosition.y += mLeftPaddleDirection * 300.0f * deltaTime;

         // Ensure paddle doesn't move off the screen
      if (mLeftPaddlePosition.y < paddleHeight / 2.0f + thickness)
         mLeftPaddlePosition.y = paddleHeight / 2.0f + thickness;
      else if (mLeftPaddlePosition.y > 768 - paddleHeight / 2.0f - thickness)
         mLeftPaddlePosition.y = 768 - paddleHeight / 2.0f - thickness;
   }

      // Update right paddle position based on keybaord input
   if (mRightPaddleDirection != 0)
   {
      mRightPaddlePosition.y += mRightPaddleDirection * 300.0f * deltaTime;

         // Ensure paddle doesn't move off the screen
      if (mRightPaddlePosition.y < paddleHeight / 2.0f + thickness)
         mRightPaddlePosition.y = paddleHeight / 2.0f + thickness;
      else if (mRightPaddlePosition.y > 768 - paddleHeight / 2.0f - thickness)
         mRightPaddlePosition.y = 768 - paddleHeight / 2.0f - thickness;
   }

   for (Ball& ball : balls)
   {
      ball.position.x += ball.velocity.x * deltaTime;
      ball.position.y += ball.velocity.y * deltaTime;

         // Handle ball bouncing against top, bottom, and right walls
      if (ball.position.y <= thickness * 1.4f && ball.velocity.y < 0.0f)
         ball.velocity.y *= -1.0f;
      else if (ball.position.y >= (768 - thickness * 1.4f) && ball.velocity.y > 0.0f)
         ball.velocity.y *= -1.0f;

         // Handle ball bouncing off left paddle
      int diff = abs(ball.position.y - mLeftPaddlePosition.y);

      if (
         diff <= paddleHeight / 2.0f &&
         ball.position.x <= 28.0f    &&
         ball.position.x >= 20.0f    &&
         ball.velocity.x < 0.0f
      )
         ball.velocity.x *= -1.0f;

         // End game if ball went off screen
      if (ball.position.x <= 0.0f || ball.position.x >= 1024)
         mIsRunning = false;

         // Handle ball bouncing off right paddle
      diff = abs(ball.position.y - mRightPaddlePosition.y);

      if (
          diff <= paddleHeight / 2.0f &&
          ball.position.x >= 996.0f   &&
          ball.position.x <= 1004.0f  &&
          ball.position.x > 0.0f
          )
         ball.velocity.x *= -1.0f;

         // End game if ball went off screen
      if (ball.position.x <= 0.0f || ball.position.x >= 1024)
         mIsRunning = false;
   }
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

      // Draw balls
   for (const auto& ball : balls)
   {
      SDL_Rect drawBall {
         static_cast<int>(ball.position.x - thickness / 2),
         static_cast<int>(ball.position.y - thickness / 2),
         thickness,
         thickness
      };
      SDL_RenderFillRect(mRenderer, &drawBall);
   }

      // Draw left paddle
   SDL_Rect paddle {
      static_cast<int>(mLeftPaddlePosition.x - thickness / 2),
      static_cast<int>(mLeftPaddlePosition.y - paddleHeight / 2),
      thickness,
      paddleHeight
   };
   SDL_RenderFillRect(mRenderer, &paddle);

      // Draw right paddle
   paddle.x = static_cast<int>(mRightPaddlePosition.x - thickness / 2);
   paddle.y = static_cast<int>(mRightPaddlePosition.y - paddleHeight / 2);
   SDL_RenderFillRect(mRenderer, &paddle);


      // Swap front and back buffers (update screen)
   SDL_RenderPresent(mRenderer);
}
