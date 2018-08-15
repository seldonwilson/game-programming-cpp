#include "Game.hpp"

Game::Game()
: mWindow(nullptr)
, mIsRunning(true)
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
   {
      mIsRunning = false;
   }
}


void Game::updateGame()
{


}


void Game::generateOutput()
{
   SDL_SetRenderDrawColor(
      mRenderer,
      0,   // red
      0,   // green
      0,   // blue
      255  // alpha
   );

   SDL_RenderClear(mRenderer);
   SDL_RenderPresent(mRenderer);
}
