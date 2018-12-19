#include <SDL.h>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

const int SCREEN_WIDTH  = 480;
const int SCREEN_HEIGHT = 480;

enum MazeSurfaces
{
   START, FINISH, BOINK,                                       // special tiles
   WALLS_NONE,                                                 // 0 walls
   WALLS_N, WALLS_E, WALLS_S, WALLS_W,                         // 1 wall
   WALLS_NE, WALLS_SE, WALLS_SW, WALLS_NW, WALLS_EW, WALLS_NS, // 2 walls
   OPEN_N, OPEN_E, OPEN_S, OPEN_W,                             // 3 walls
   MAZE_SURFACES_TOTAL   
};

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);
std::vector<std::vector<int>> loadMaze(std::string maze);

SDL_Window*  gWindow         = nullptr;
SDL_Surface* gScreenSurface  = nullptr;
SDL_Surface* gCurrentSurface = nullptr;
SDL_Surface* gMazeSurfaces[MAZE_SURFACES_TOTAL];


   /* There's a bug, either in SDL, OpenGL, or MacOS which won't render the
      window until it has been moved.
   */
int main(int argc, char* argv[])
{
   if (init() && loadMedia())
   {
      bool quit = false;
      int i = START;
      gCurrentSurface = gMazeSurfaces[i];

      while (!quit)
      {
         SDL_Event e;
         
         while(SDL_PollEvent(&e))
         {
            if (e.type == SDL_QUIT)
               quit = true;
            
            else if (e.type == SDL_KEYDOWN)
            {
               i = (i + 1) % 3; // change to MAZE_SURFACES_TOTAL
               gCurrentSurface = gMazeSurfaces[i];
            }
         }

         SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
         SDL_UpdateWindowSurface(gWindow);
      }
   }
   
   loadMaze("maze.txt");

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
      "Event Driven Test To See If The Title Is Too Long Or Too Long! It just needs to be a little longer",
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
   
   gMazeSurfaces[START] = loadSurface("img/start.bmp");
   if (gMazeSurfaces[START] == nullptr)
   {
      printf("Failed to load start image!\n");
      success = false;
   }
   
   gMazeSurfaces[FINISH] = loadSurface("img/finish.bmp");
   if (gMazeSurfaces[FINISH] == nullptr)
   {
      printf("Failed to load finish image!\n");
      success = false;
   }
   
   gMazeSurfaces[BOINK] = loadSurface("img/boink.bmp");
   if (gMazeSurfaces[BOINK] == nullptr)
   {
      printf("Failed to load boink image!\n");
      success = false;
   }
   
   // Load remainder of surfaces

   return success;
}


void close()
{   
   for (int i = 0; i < MAZE_SURFACES_TOTAL; ++i)
   {
      if (gMazeSurfaces[i])
      {
         SDL_FreeSurface(gMazeSurfaces[i]);
         gMazeSurfaces[i] = nullptr;
      }
   }
            
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

std::vector<std::vector<int>> loadMaze(std::string filename) {
   std::ifstream mazeFile(filename.c_str());
   
   if (!mazeFile.is_open()) {
      printf("ERROR opening file\nEXITING...\n");
      exit(1);
   }

   std::string s;
   mazeFile >> s;
   
   int base;
   mazeFile >> base;
   mazeFile >> s;
   
   int height;
   mazeFile >> height;
   mazeFile >> s;
   
   int start;
   mazeFile >> start;
   mazeFile >> s;
   
   int end;
   mazeFile >> end;
   
   std::vector<std::vector<int>> maze(height, std::vector<int>(base, 0));
   
   for (int row = 0; row < height; ++row) {
      for (int col = 0; col < base; ++col) {
         int wall;
         mazeFile >> wall;
         maze[row][col] = wall;
      }
   }
   
   
   for (int row = 0; row < height; ++row) {
      for (int col = 0; col < base; ++col) {
         printf("%2d ", maze[row][col]);
      }
      printf("\n");
   }
   
   return {};
}