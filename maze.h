#ifndef S21_MAZE_H_
#define S21_MAZE_H_
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"

typedef struct Maze {
  int height;
  int width;
  int **walls;
  int **floors;
} Maze;

void AllocateMemory(Maze *m) {
  m->walls = malloc(m->height * sizeof(int *));
  for (int i = 0; i < m->height; i++) {
    m->walls[i] = malloc(m->width * sizeof(int));
  }
  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      m->walls[i][j] = 0;
    }
  }
  m->floors = malloc(m->height * sizeof(int *));
  for (int i = 0; i < m->height; i++) {
    m->floors[i] = malloc(m->width * sizeof(int));
  }
  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      m->floors[i][j] = 0;
    }
  }
}

void FreeMemory(Maze *m) {
  for (int i = 0; i < m->height; i++) {
    free(m->walls[i]);
    free(m->floors[i]);
  }
  free(m->walls);
  free(m->floors);
}

char **PrepareMaze(Maze *m) {
  int height = m->height * 2 + 1;
  int width = m->width * 2 + 1;
  char **maze = malloc(height * sizeof(char *));
  for (int i = 0; i < height; i++) {
    maze[i] = malloc(width * sizeof(char));
  }
  int h = 0;
  int w = 0;
  for (int i = 0; i < height; i++) {
    w = 0;
    if (i % 2 == 1 && i > 1) {
      h++;
    }
    for (int j = 0; j < width; j++) {
      if (j % 2 == 1 && j > 1) {
        w++;
      }
      if (i == 0) {
        maze[i][j] = '#';
      } else if (j == 0) {
        maze[i][j] = '#';
      } else if (i % 2 == 1) {
        if (j % 2 == 1) {
          maze[i][j] = ' ';
        } else {
          maze[i][j] = (m->walls[h][w] == 0 ? ' ' : '#');
        }
      } else {
        if (j % 2 == 1) {
          maze[i][j] = (m->floors[h][w] == 0 ? ' ' : '#');
        } else {
          if ((m->walls[h][w] == 1) || (m->floors[h][w] == 1) ||
              (h < m->height - 1 && m->walls[h + 1][w] == 1) ||
              (w < m->width - 1 && m->floors[h][w + 1] == 1) ||
              (h > 0 && m->walls[h - 1][w] == 1) || (h == m->height - 1) ||
              (w == m->width - 1)) {
            maze[i][j] = '#';
          } else {
            maze[i][j] = ' ';
          }
        }
      }
    }
  }

  return maze;
}

void DisplayMaze(char **maze, int height, int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (maze[i][j] == '.') {
        printf("\x1b[31m%c \033[0m", maze[i][j]);
      } else if (maze[i][j] == '#') {
        printf("\x1b[32m%c \033[0m", maze[i][j]);
      } else {
        printf("%c ", maze[i][j]);
      }
    }
    printf("\n");
  }
}

#endif  // S21_MAZE_H_