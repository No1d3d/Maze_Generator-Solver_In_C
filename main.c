#include <stdio.h>

#include "allinclude.h"
#include "maze.h"

int main() {
  Maze m;
  m.height = 0;
  m.width = 0;
  // char enter;
  while (1 == 1) {
    int option = 0;
    printf(
        "Options:\n\tGenerate a maze - 1\n\tRead a maze from file - "
        "2\n\tSolve a maze - 3\n\tGenerate a cave - 4\n\tQuit - 5\n");
    printf("Select an option: ");
    scanf("%d", &option);
    if (option == 1) {
      GenerateAMaze(&m);
    } else if (option == 2) {
      ReadMazeFile(&m);
    } else if (option == 3) {
      if (m.height != 0 && m.width != 0) {
        SolveMazeDeadEndFill(&m);
      } else {
        printf(
            "Error! Currently there is no maze to solve! Generate (option "
            "1) or Read (option 2) one first!\n");
      }
    } else if (option == 4) {
      // GenerateCave();
      start();
    } else if (option == 5) {
      printf("Exiting the program...");
      break;
    }
  }
  if (m.height != 0 && m.width != 0) {
    FreeMemory(&m);
  }
}