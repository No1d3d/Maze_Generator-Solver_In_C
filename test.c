#include <stdio.h>

#include "allinclude.h"
#include "maze.h"

int main() {
  Maze m;
  m.height = 0;
  m.width = 0;
  printf("Reading test_maze.txt\n");
  ReadMazeTest(&m);
  printf("Initiating tests\n");
  SolveMazeTest(&m);
  FreeMemory(&m);
}

