#ifndef S21_SOLVE_MAZE_H_
#define S21_SOLVE_MAZE_H_
#include <stdlib.h>

#include "helpers.h"
#include "maze.h"

struct Bot {
  int x;
  int y;
  char direction;
};

int GetAllDeadEnds(char **maze, int height, int width, struct Bot *ends) {
  int counter = 0;
  for (int i = 1; i < height - 1; i++) {
    for (int j = 1; j < width - 1; j++) {
      if (maze[i][j] == ' ') {
        int walls = 0;
        char dir = 'r';
        maze[i][j] = '.';
        if (maze[i][j + 1] == '#') {
          walls++;
        } else if (maze[i][j + 1] == ' ' || maze[i][j + 1] == '.') {
          dir = 'r';
        }
        if (maze[i][j - 1] == '#') {
          walls++;
        } else if (maze[i][j - 1] == ' ' || maze[i][j - 1] == '.') {
          dir = 'l';
        }
        if (maze[i + 1][j] == '#') {
          walls++;
        } else if (maze[i + 1][j] == ' ' || maze[i + 1][j] == '.') {
          dir = 'd';
        }
        if (maze[i - 1][j] == '#') {
          walls++;
        } else if (maze[i - 1][j] == ' ' || maze[i - 1][j] == '.') {
          dir = 'u';
        }
        if (walls == 3) {
          ends[counter].y = i;
          ends[counter].x = j;
          ends[counter].direction = dir;
          counter++;
        }
      }
    }
  }
  return counter;
}

void ClearMazeDeadEnds(char **maze, int xs, int ys, int xe, int ye,
                       struct Bot *bot, int count) {
  for (int i = 0; i < count; i++) {
    if ((bot[i].x == xe && bot[i].y == ye) ||
        (bot[i].x == xs && bot[i].y == ys)) {
      continue;
    }
    while (1 == 1) {
      int ways = 0;
      if (maze[bot[i].y - 1][bot[i].x] == '.') {
        ways++;
      }
      if (maze[bot[i].y + 1][bot[i].x] == '.') {
        ways++;
      }
      if (maze[bot[i].y][bot[i].x - 1] == '.') {
        ways++;
      }
      if (maze[bot[i].y][bot[i].x + 1] == '.') {
        ways++;
      }
      if (ways >= 2) {
        break;
      }

      maze[bot[i].y][bot[i].x] = ' ';
      if (bot[i].direction == 'r') {
        bot[i].x += 1;
        if (maze[bot[i].y][bot[i].x] == '#') {
          bot[i].x -= 1;
        }
        if (maze[bot[i].y - 1][bot[i].x] == '.' &&
            maze[bot[i].y - 1][bot[i].x - 1] != '.' &&
            maze[bot[i].y - 1][bot[i].x + 1] != '.') {
          bot[i].direction = 'u';
        } else if (maze[bot[i].y - 1][bot[i].x] != '.' &&
                   maze[bot[i].y][bot[i].x + 1] != '.') {
          bot[i].direction = 'd';
        }

      } else if (bot[i].direction == 'u') {
        bot[i].y -= 1;
        if (maze[bot[i].y][bot[i].x] == '#') {
          bot[i].y += 1;
        }
        if (maze[bot[i].y][bot[i].x - 1] == '.' &&
            maze[bot[i].y - 1][bot[i].x - 1] != '.' &&
            maze[bot[i].y + 1][bot[i].x - 1] != '.') {
          bot[i].direction = 'l';
        } else if (maze[bot[i].y - 1][bot[i].x] != '.' &&
                   maze[bot[i].y][bot[i].x - 1] != '.') {
          bot[i].direction = 'r';
        }

      } else if (bot[i].direction == 'l') {
        bot[i].x -= 1;
        if (maze[bot[i].y][bot[i].x] == '#') {
          bot[i].x += 1;
        }
        if (maze[bot[i].y + 1][bot[i].x] == '.' &&
            maze[bot[i].y + 1][bot[i].x - 1] != '.' &&
            maze[bot[i].y + 1][bot[i].x + 1] != '.') {
          bot[i].direction = 'd';
        } else if (maze[bot[i].y + 1][bot[i].x] != '.' &&
                   maze[bot[i].y][bot[i].x - 1] != '.') {
          bot[i].direction = 'u';
        }

      } else if (bot[i].direction == 'd') {
        bot[i].y += 1;
        if (maze[bot[i].y][bot[i].x] == '#') {
          bot[i].y -= 1;
        }
        if (maze[bot[i].y][bot[i].x + 1] == '.' &&
            maze[bot[i].y - 1][bot[i].x + 1] != '.' &&
            maze[bot[i].y + 1][bot[i].x + 1] != '.') {
          bot[i].direction = 'r';
        } else if (maze[bot[i].y + 1][bot[i].x] != '.' &&
                   maze[bot[i].y][bot[i].x + 1] != '.') {
          bot[i].direction = 'l';
        }
      }
      if ((bot[i].y == ye && bot[i].x == xe) ||
          (bot[i].y == ys && bot[i].x == xs)) {
        break;
      }
    }
  }
}

void SolveMazeDeadEndFill(Maze *m) {
  char **maze = PrepareMaze(m);
  int xs, ys, xe, ye;

  InputValue(&xs, 0, m->width, "Enter X of start point: ");
  InputValue(&ys, 0, m->height, "Enter Y of start point: ");
  InputValue(&xe, 0, m->width, "Enter X of end point: ");
  InputValue(&ye, 0, m->height, "Enter Y of end point: ");
  xs = xs * 2 + 1;
  ys = ys * 2 + 1;
  xe = xe * 2 + 1;
  ye = ye * 2 + 1;
  struct Bot *corridors = (struct Bot *)malloc(1000 * sizeof(*corridors));
  int count =
      GetAllDeadEnds(maze, m->height * 2 + 1, m->width * 2 + 1, corridors);

  // printf("\nlol\n");
  ClearMazeDeadEnds(maze, xs, ys, xe, ye, corridors, count);
  DisplayMaze(maze, m->height * 2 + 1, m->width * 2 + 1);
  free(corridors);
  for (int i = 0; i < m->height * 2 + 1; i++) {
    free(maze[i]);
  }
  free(maze);
}

void SolveMazeTest(Maze *m) {
  char **maze1 = PrepareMaze(m);
  char **maze2 = PrepareMaze(m);
  int xs = 0, ys = 0, xe = 9, ye = 9;
  xs = xs * 2 + 1;
  ys = ys * 2 + 1;
  xe = xe * 2 + 1;
  ye = ye * 2 + 1;
  printf("\nClearing Dead Ends\n");
  struct Bot *corridors1 = (struct Bot *)malloc(1000 * sizeof(*corridors1));
  int count1 =
      GetAllDeadEnds(maze1, m->height * 2 + 1, m->width * 2 + 1, corridors1);

  ClearMazeDeadEnds(maze1, xs, ys, xe, ye, corridors1, count1);
  struct Bot *corridors2 = (struct Bot *)malloc(1000 * sizeof(*corridors2));
  int count2 =
      GetAllDeadEnds(maze2, m->height * 2 + 1, m->width * 2 + 1, corridors2);

  ClearMazeDeadEnds(maze2, xe, ye, xs, ys, corridors2, count2);

  printf("Maze1: \n");
  DisplayMaze(maze1, m->height * 2 + 1, m->width * 2 + 1);
  printf("\n\nMaze2: \n");
  DisplayMaze(maze2, m->height * 2 + 1, m->width * 2 + 1);

  printf("\n\n--------------------Start of the tests--------------------\n");
  int way1 = 0;
  int way2 = 0;
  int correct = 0;
  int fail = 0;
  for (int i = 0; i < m->height * 2 + 1; i++) {
    for (int j = 0; j < m->width * 2 + 1; j++) {
      if (maze1[i][j] != maze2[i][j]) {
        printf("\tCell (%d ; %d)\t-\tFAIL\n", i, j);
        fail++;
      } else {
        printf("\tCell (%d ; %d)\t-\tCHECK!\n", i, j);
        correct++;
      }
      if (maze1[i][j] == '.') {
        way1++;
      }
      if (maze2[i][j] == '.') {
        way2++;
      }
    }
  }
  printf("\nResults: (shortest solution is 45 cells)\n");
  printf("\tLength of solution one: %d\n", way1);
  printf("\tLength of solution two: %d\n", way1);
  printf(way1 == way2 && way1 == 45 ? "Solution test - Correct!\n"
                                    : "Solution test - Fail!\n");
  printf("Maze equality results: Check - %d | Fail - %d\n", correct, fail);
  printf("--------------------End  of  the tests--------------------\n");
  free(corridors1);
  free(corridors2);
  for (int i = 0; i < m->height * 2 + 1; i++) {
    free(maze1[i]);
    free(maze2[i]);
  }
  free(maze1);
  free(maze2);
}

#endif