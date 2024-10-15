#ifndef S21_READ_MAZE_H_
#define S21_READ_MAZE_H_
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "maze.h"

void ReadMazeFile(Maze *m) {
  FILE *fp;
  char filename[100] = "";
  memset(filename, '\0', 100);

  printf("Enter a file name to read maze from: ");
  scanf("%100s", filename);
  printf("filename: %s\n", filename);
  if (File_exists(filename) == 1) {
    fp = fopen(filename, "r");
    char buf[101];
    char *current_number;
    int height, width;
    fgets(buf, 101, fp);
    current_number = strtok(buf, " ");
    height = atoi(current_number);
    current_number = strtok(NULL, " ");
    width = atoi(current_number);
    if (m->height != 0 || m->width != 0) {
      FreeMemory(m);
    }
    m->height = height;
    m->width = width;
    AllocateMemory(m);
    for (int i = 0; i < height; i++) {
      fgets(buf, 101, fp);
      for (int j = 0; j < width; j++) {
        if (j == 0) {
          current_number = strtok(buf, " ");
        } else {
          current_number = strtok(NULL, " ");
        }
        m->walls[i][j] = atoi(current_number);
      }
    }
    fgets(buf, 101, fp);
    for (int i = 0; i < height; i++) {
      fgets(buf, 101, fp);
      for (int j = 0; j < width; j++) {
        if (j == 0) {
          current_number = strtok(buf, " ");
        } else {
          current_number = strtok(NULL, " ");
        }
        m->floors[i][j] = atoi(current_number);
      }
    }
    fclose(fp);

    char **maze = PrepareMaze(m);
    DisplayMaze(maze, m->height * 2 + 1, m->width * 2 + 1);
    for (int i = 0; i < m->height * 2 + 1; i++) {
      free(maze[i]);
    }
    free(maze);
  } else {
    printf("No such file: %s\n", filename);
  }
}

void ReadMazeTest(Maze *m) {
  FILE *fp;
  fp = fopen("test_maze.txt", "r");
  char buf[101];
  char *current_number;
  int height, width;
  fgets(buf, 101, fp);
  current_number = strtok(buf, " ");
  height = atoi(current_number);
  current_number = strtok(NULL, " ");
  width = atoi(current_number);
  m->height = height;
  m->width = width;
  AllocateMemory(m);
  for (int i = 0; i < height; i++) {
    fgets(buf, 101, fp);
    for (int j = 0; j < width; j++) {
      if (j == 0) {
        current_number = strtok(buf, " ");
      } else {
        current_number = strtok(NULL, " ");
      }
      m->walls[i][j] = atoi(current_number);
    }
  }
  fgets(buf, 101, fp);
  for (int i = 0; i < height; i++) {
    fgets(buf, 101, fp);
    for (int j = 0; j < width; j++) {
      if (j == 0) {
        current_number = strtok(buf, " ");
      } else {
        current_number = strtok(NULL, " ");
      }
      m->floors[i][j] = atoi(current_number);
    }
  }
  fclose(fp);
}

#endif  // S21_READ_MAZE_H_
