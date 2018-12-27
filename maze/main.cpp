#include <SDL.h>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include "Maze.hpp"
#include "Player.hpp"

const int SCREEN_WIDTH  = 480;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);
std::vector<std::vector<int>> loadMaze(std::string maze);

SDL_Window*  gWindow         = nullptr;
SDL_Surface* gScreenSurface  = nullptr;
SDL_Surface* gCurrentSurface = nullptr;
std::unordered_map<std::string, SDL_Surface*> gMazeSurfaces;


   /* There's a bug, either in SDL, OpenGL, or MacOS which won't render the
      window until it has been moved.
   */
int main(int argc, char* argv[])
{
   if (init() && loadMedia())
   {
      bool quit = false;
      Maze maze("maze.txt");
      std::pair<int, int> start = maze.getStart();
      gCurrentSurface = gMazeSurfaces[maze.getTilename(start.first, start.second)];
      Player player(start.first, start.second);

      while (!quit)
      {
         SDL_Event e;
         
         while(SDL_PollEvent(&e))
         {
            if (e.type == SDL_QUIT)
               quit = true;
            
            else if (e.type == SDL_KEYDOWN)
            {
               int row = player.getRow();
               int col = player.getCol();
               
               switch (e.key.keysym.sym)
               {
                  case SDLK_UP:
                     if (!maze.canMoveNorth(row, col)) { break; }
                     
                     break;
                  
                  case SDLK_DOWN:
                  
                     break;
                     
                  case SDLK_LEFT:
                  
                     break;
                     
                  case SDLK_RIGHT:
                  
                     break;
               }
            }
         }

         SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
         SDL_UpdateWindowSurface(gWindow);
      }
   }
   
   close();
   return 0;
}


bool init()
{   
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
   {
      printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
      return false;
   }
   
   gWindow = SDL_CreateWindow(
      "Maze Game",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN
   );
   
   if (gWindow == nullptr)
   {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return false;
   }  

   gScreenSurface = SDL_GetWindowSurface(gWindow);
   
   return true;
}


bool loadMedia()
{
   bool success = true;
   
   gMazeSurfaces["N"] = loadSurface("img/N.bmp");
   if (gMazeSurfaces["N"] == nullptr)
   {
      printf("Failed to load \"N.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["E"] = loadSurface("img/E.bmp");
   if (gMazeSurfaces["E"] == nullptr)
   {
      printf("Failed to load \"E.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["S"] = loadSurface("img/S.bmp");
   if (gMazeSurfaces["S"] == nullptr)
   {
      printf("Failed to load \"S.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["W"] = loadSurface("img/W.bmp");
   if (gMazeSurfaces["W"] == nullptr)
   {
      printf("Failed to load \"W.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["NE"] = loadSurface("img/NE.bmp");
   if (gMazeSurfaces["NE"] == nullptr)
   {
      printf("Failed to load \"NE.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["ES"] = loadSurface("img/ES.bmp");
   if (gMazeSurfaces["ES"] == nullptr)
   {
      printf("Failed to load \"ES.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["SW"] = loadSurface("img/SW.bmp");
   if (gMazeSurfaces["SW"] == nullptr)
   {
      printf("Failed to load \"SW.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["NW"] = loadSurface("img/NW.bmp");
   if (gMazeSurfaces["NW"] == nullptr)
   {
      printf("Failed to load \"NW.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["NS"] = loadSurface("img/NS.bmp");
   if (gMazeSurfaces["NS"] == nullptr)
   {
      printf("Failed to load \"NS.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["EW"] = loadSurface("img/EW.bmp");
   if (gMazeSurfaces["EW"] == nullptr)
   {
      printf("Failed to load \"EW.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["NES"] = loadSurface("img/NES.bmp");
   if (gMazeSurfaces["NES"] == nullptr)
   {
      printf("Failed to load \"NES.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["ESW"] = loadSurface("img/ESW.bmp");
   if (gMazeSurfaces["ESW"] == nullptr)
   {
      printf("Failed to load \"ESW.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["NSW"] = loadSurface("img/NSW.bmp");
   if (gMazeSurfaces["NSW"] == nullptr)
   {
      printf("Failed to load \"NSW.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["NEW"] = loadSurface("img/NEW.bmp");
   if (gMazeSurfaces["NEW"] == nullptr)
   {
      printf("Failed to load \"NEW.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["NESW"] = loadSurface("img/NESW.bmp");
   if (gMazeSurfaces["NESW"] == nullptr)
   {
      printf("Failed to load \"NESW.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["finish"] = loadSurface("img/finish.bmp");
   if (gMazeSurfaces["finish"] == nullptr)
   {
      printf("Failed to load \"finish.bmp\"!\n");
      success = false;
   }
   
   gMazeSurfaces["boink"] = loadSurface("img/boink.bmp");
   if (gMazeSurfaces["boink"] == nullptr)
   {
      printf("Failed to load \"boink.bmp\"!\n");
      success = false;
   }
   
   return success;
}


void close()
{               
   SDL_DestroyWindow(gWindow);

   gScreenSurface  = nullptr;
   gCurrentSurface = nullptr;
   gWindow         = nullptr;   
   
   SDL_Quit();
}


SDL_Surface* loadSurface(std::string path)
{
   SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
   
   if (loadedSurface == nullptr)
   {
      printf(
         "Unable to load image %s! SDL Error: %s\n",
         path.c_str(),
         SDL_GetError()
      );
   }
   
   return loadedSurface;
}
