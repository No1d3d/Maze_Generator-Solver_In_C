#ifndef S21_GENERATE_MAZE_H_
#define S21_GENERATE_MAZE_H_
//#include "allinclude.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "maze.h"

void EulerMaze(Maze *m) {
  srand(time(NULL));
  int *randNums = (int *)malloc(m->width * sizeof(int));
  int new_set = 1;
  int i, j, put_barrier, to_find, counter;
  // int w = 0, f = 0;
  int *currentRow = (int *)malloc(m->width * sizeof(int));
  for (i = 0; i < m->height; i++) {
    if (i == 0) {
      for (j = 0; j < m->width; j++) {
        currentRow[j] = new_set;
        new_set++;
      }
    } else {
      for (j = 0; j < m->width; j++) {
        m->walls[i][j] = 0;
        m->floors[i][j] = m->floors[i - 1][j];
        if (m->floors[i][j] == 1) {
          currentRow[j] = 0;
          m->floors[i][j] = 0;
        }
      }
      for (j = 0; j < m->width; j++) {
        if (currentRow[j] == 0) {
          new_set++;
          currentRow[j] = new_set;
        }
      }
    }
    for (j = 0; j < m->width - 1; j++) {
      put_barrier = rand() % 2;
      if (put_barrier == 1) {
        m->walls[i][j] = 1;
      } else if (put_barrier == 0) { 
        if (currentRow[j] == currentRow[j + 1]) {
          m->walls[i][j] = 1;
        } else {
          to_find = currentRow[j + 1];
          for (int k = 0; k < m->width; k++) {
            if (currentRow[k] == to_find) {
              currentRow[k] = currentRow[j];
            }
          }
        }
      }
    }

    for (j = 0; j < m->width; j++) {
      put_barrier = rand() % 2;
      if (put_barrier == 0) {
        m->floors[i][j] = 0;
      } else if (put_barrier == 1) {
        to_find = currentRow[j];
        counter = 0;
        for (int k = 0; k < m->width; k++) {
          if (currentRow[k] == to_find &&
              m->floors[i][k] == 0) {
            counter++;
          }
        }
        if (counter > 1) {
          m->floors[i][j] = 1;
        }
      }
    }

    if (i == m->height - 1) {
      for (j = 0; j < m->width; j++) {
        m->floors[i][j] = 1;
      }
      for (j = 0; j < m->width - 1; j++) {
        if (currentRow[j] != currentRow[j + 1]) {
          m->walls[i][j] = 0;
          to_find = currentRow[j + 1];
          for (int k = 0; k < m->width; k++) {
            if (currentRow[k] == to_find) {
              currentRow[k] = currentRow[j];
            }
          }
        }
      }
    }
    m->walls[i][m->width - 1] = 1;
  }
  free(randNums);
  free(currentRow);
}

void MazeIntoFile(Maze *m) {
  static int count = 1;
  char buffer[8];
  char fileNameForMaze[19];
  do {
    s21_itoa(count, buffer);
    strcpy(fileNameForMaze, "maze");
    strcat(fileNameForMaze, buffer);
    strcat(fileNameForMaze, ".txt");
    count++;
  } while (File_exists(fileNameForMaze) == 1);
  FILE *fptr;
  fptr = fopen(fileNameForMaze, "w");
  char file_inp[101];
  s21_itoa(m->height, buffer);
  strcpy(file_inp, buffer);
  strcat(file_inp, " ");
  s21_itoa(m->width, buffer);
  strcat(file_inp, buffer);
  strcat(file_inp, "\n");
  fputs(file_inp, fptr);

  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      s21_itoa(m->walls[i][j], buffer);
      if (j == 0) {
        strcpy(file_inp, buffer);
      } else {
        strcat(file_inp, buffer);
      }
      if (j < m->width - 1) {
        strcat(file_inp, " ");
      }
    }
    strcat(file_inp, "\n");
    fputs(file_inp, fptr);
  }

  fputs("\n", fptr);

  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      s21_itoa(m->floors[i][j], buffer);
      if (j == 0) {
        strcpy(file_inp, buffer);
      } else {
        strcat(file_inp, buffer);
      }
      if (j < m->width - 1) {
        strcat(file_inp, " ");
      }
    }
    strcat(file_inp, "\n");
    fputs(file_inp, fptr);
  }
  fclose(fptr);
}

void GenerateAMaze(Maze *m) {
  if (m->height != 0 && m->width != 0) {
    FreeMemory(m);
  }
  InputValue(&m->height, 2, 50, "Enter height: ");
  InputValue(&m->width, 2, 50, "Enter width: ");
  printf("%d %d\n", m->height, m->width);
  AllocateMemory(m);
  EulerMaze(m);
  MazeIntoFile(m);
  char **maze = PrepareMaze(m);
  DisplayMaze(maze, m->height * 2 + 1, m->width * 2 + 1);
  for (int i = 0; i < m->height * 2 + 1; i++) {
    free(maze[i]);
  }
  free(maze);
}
#endif  // S21_GENERATE_MAZE_H_