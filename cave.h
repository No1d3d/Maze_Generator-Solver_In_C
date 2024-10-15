#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#ifndef SRC_CAVE_H_
#define SRC_CAVE_H_

#define MAXROWS 50
#define MAXCOLUMNS 50

typedef struct cave_struct {
  int **cave;
  int rows;
  int columns;
  int birth_limit;
  int death_limit;
  int chance;
} cave_t;

int cave_initialisation(cave_t *cave);
int init_start_cave(cave_t *cave);
int fill_cave(cave_t *cave, cave_t *cave_1);
int create_matrix(int rows, int columns, cave_t *result);
void remove_matrix(cave_t *cave);
int change_cave(cave_t cave, cave_t *cave_1);
int isEqual(cave_t *A, cave_t *B);
int paint_in_black(cave_t *cave);
int sum(cave_t cave_old, int i, int j);
void init_val(cave_t *cave_old, cave_t *cave_next, cave_t *cave_buff);
void custom_input(int *birth_limit, int *death_limit, int *skill, int *rows_, int *cols_, int *sleepingTime, FILE *filename, cave_t *cave_old);
int parse(FILE *file, cave_t *old_cave);
int check(cave_t *cave);
void start();

void start() {
        FILE *file;
    cave_t cave_old;
    cave_t cave_next;
    cave_t cave_buff;
    char first_blood [4060];
    int birth_limit = 0;
    int death_limit = 0;
    int skill = 0;
    int sleepingTime = 0;
    int error = 0;
    int rows_ = 0;
    int cols_ = 0;
    printf("input filename or anyfing else to continue: ");
    scanf("%s", first_blood);
    file = fopen(first_blood, "r");
    if (file != NULL) {
        error = parse(file, &cave_old);
    }
    custom_input(&birth_limit, &death_limit, &skill, &rows_, &cols_, &sleepingTime, file, &cave_old);
    init_val(&cave_old, &cave_next, &cave_buff);
    cave_initialisation(&cave_next);
    cave_initialisation(&cave_buff);
    int n = 0;
    paint_in_black(&cave_old);
    change_cave(cave_next, &cave_next);
    if (check(&cave_old) != 1 && error != 1) {
    while (isEqual(&cave_old, &cave_next) != 1 || n < 200) {
        if(n>0){fill_cave(&cave_old, &cave_next);}
        change_cave(cave_old, &cave_buff);
        fill_cave(&cave_next, &cave_buff);
        usleep((10-sleepingTime)*200000);
        system("clear");
        paint_in_black(&cave_next);
        n++;
        printf("n%d\n",n);
    }
    } else {printf("\nerror in input or file\n");}
    remove_matrix(&cave_buff);
    remove_matrix(&cave_old);
    remove_matrix(&cave_next);
}

void custom_input(int *birth_limit, int *death_limit, int *skill, int *rows_, int *cols_, int *sleepingTime, FILE *filename, cave_t *cave_old) {
    printf("choose speeeeed: ");
    scanf("%d", sleepingTime);
    printf("input birth limit(min): ");
    scanf("%d", birth_limit);
    printf("input death limit(min): ");
    scanf("%d", death_limit);
    cave_old->birth_limit = *birth_limit;
    cave_old->death_limit = *death_limit;
    if (filename == NULL) {
        printf("input rows: ");
        scanf("%d", rows_);
        printf("input cols: ");
        scanf("%d", cols_);
        printf("input chance (10 to 90): ");
        scanf("%d", skill);
        cave_old->rows = *rows_;
        cave_old->columns = *cols_;
        cave_old->chance = *skill;
        cave_initialisation(cave_old);
    } else {cave_old->chance = 40;}
}

int check(cave_t *cave) {
    int error = 0;
    if (cave->birth_limit < 0 || cave->birth_limit > 7) {error = 1;printf("error");}
    if (cave->death_limit < 0 || cave->death_limit > 7) {error = 1;printf("error1");}
    if (cave->rows < 0 || cave->rows > 50) {error = 1;printf("error2");}
    if (cave->columns < 0 || cave->columns > 50) {error = 1;printf("error3");}
    if (cave->chance < 10 || cave->chance > 90) {error = 1;printf("error4");}
    return error;
}

int parse(FILE *file, cave_t *old_cave) {
    int error = 0 ;
    char buff[150] = {};
    char *col_row;
    int n = 0;
    int call = 0;
    char c = 'a';
    while (fgets(buff, 150, file)) {
        if(n == 0) {
            col_row = strtok(buff, " ");
            while(col_row != NULL) {
                if (call == 0) {
                    old_cave->rows = atoi(col_row);
                } else if (call == 1){ 
                    old_cave->columns = atoi(col_row);
                    create_matrix(old_cave->rows, old_cave->columns, old_cave);
                    n++;
                }
                call ++;
                col_row = strtok(NULL, " ");
            }
            if (call != 2) { error = 1;}
        } else {
            if (((int)strlen(buff) - 1) != old_cave->columns) {error = 1;}
            for ( int i = 0; i < (int)strlen(buff); i++) {
                c = buff[i];
                old_cave->cave[n-1][i] = atoi(&c);
            }
            n++;
        }
    }
    if (n-1 != old_cave->rows) {error = 1;}
    return error;
}

void init_val(cave_t *cave_old, cave_t *cave_next, cave_t *cave_buff) {
    cave_next->rows = cave_old->rows;
    cave_next->columns = cave_old->columns;
    cave_next->birth_limit = cave_old->birth_limit;
    cave_next->death_limit = cave_old->death_limit;
    cave_next->chance = cave_old->chance;
    cave_buff->rows = cave_old->rows;
    cave_buff->columns = cave_old->columns;
    cave_buff->birth_limit = cave_old->birth_limit;
    cave_buff->death_limit = cave_old->death_limit;
    cave_buff->chance = cave_old->chance;
}

int cave_initialisation(cave_t *cave_old) {

    create_matrix(cave_old->rows, cave_old->columns, cave_old);
    init_start_cave(cave_old);
    return 0;
}

int create_matrix(int rows, int columns, cave_t *result) {
  int error = 0;
  if (result != NULL && rows > 0 && columns > 0) {
    result->columns = columns;
    result->rows = rows;
    result->cave =
        malloc(rows * columns * sizeof(int) + rows * sizeof(int *));
    int *p = (int *)(result->cave + rows);
    for (int row = 0; row < rows; row++) {
      result->cave[row] = p + columns * row;
    }
    for (int row = 0; row < rows; row++) {
      for (int column = 0; column < columns; column++) {
        result->cave[row][column] = 0;
      }
    }
  } else {
    error = 1;
  }
  printf("matrix created\n");
  return error;
}

void remove_matrix(cave_t *A) {
  if (A) {
    if (A->cave) {
      free(A->cave);
      A->cave = NULL;
    }
    if (A->rows) {
      A->rows = 0;
    }
    if (A->columns) {
      A->columns = 0;
    }
    A = NULL;
  }
}

int fill_cave(cave_t *cave_old, cave_t *cave_next) {
    for (int i = 0; i < cave_old->rows; i++) {
        for (int j = 0; j < cave_old->columns; j++) {
            cave_old->cave[i][j] = cave_next->cave[i][j];
        }
    }
    return 0;
}

int init_start_cave(cave_t *cave_old) {
    srand(time(NULL));
    int r = 0;
    for (int i = 0; i < cave_old->rows; i++) {
        for (int j = 0; j < cave_old->columns; j++) {
            r = rand() % 100; 
            if (r < cave_old->chance) {
                cave_old->cave[i][j] = 1;
            } else {
                cave_old->cave[i][j] = 0;
            }
        }
    }
    return 0;
}

int isEqual(cave_t *A, cave_t *B) {
  int isEqual = 1;
      for (int row = 0; row < A->rows && isEqual; row++) {
        for (int column = 0; column < A->columns && isEqual; column++) {
          if (round(A->cave[row][column] - B->cave[row][column]) != 0) {
            isEqual = 0;
          }
        }
      }
  return isEqual;
}

int change_cave(cave_t cave_old, cave_t *cave_buff) {
    int alive = 0;
    for (int i = 0; i < cave_old.rows; i++) {
        for (int j = 0; j < cave_old.columns; j++) {
            alive = sum(cave_old, i, j);
            if (cave_old.cave[i][j] == 1) {
                if (alive < cave_old.death_limit) {
                    cave_buff->cave[i][j] = 0;
                } else {cave_buff->cave[i][j] = 1;}
            } else if (cave_old.cave[i][j] == 0) {
                if (alive > cave_old.birth_limit) {
                    cave_buff->cave[i][j] = 1;
                } else {cave_buff->cave[i][j] = 0;}
            }
            alive = 0;
        }
    }
    return 0;
}

int sum(cave_t cave_old, int i, int j) {
    int res = 0;
    for (int n = (i-1); n <= (i+1); n ++) {
        for (int k = (j-1); k <= (j+1); k++) {
            if (!(n == i && k == j)) {
                if (n < 0 || k < 0 || n >= cave_old.rows || k >= cave_old.columns) {
                    res ++;
                } else if (cave_old.cave[n][k] == 1){
                    res ++;    
                }   
            }
        }
    } 
    return res;
}

int paint_in_black (cave_t *cave) {
    for (int i = 0; i < cave->rows; i++) {
        for (int j = 0; j < cave->columns; j++) {
            if (cave->cave[i][j] == 1) {
                printf("o");
            } else {
                printf(" ");
            }
            if (j == cave->columns - 1) {
                printf("\n");
            }
        }
    }
    return 0;
}

#endif  // SRC_CAVE_H_
