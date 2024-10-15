#ifndef S21_HELPERS_H_
#define S21_HELPERS_H_
#include <stdio.h>
#include <string.h>

void Error(char *context) { printf("%s", context); }

void InputValue(int *res, int min_val, int max_val, char *context) {
  do {
    printf("%s", context);
    scanf("%d", res);
    if (*res < min_val || *res > max_val) {
      Error("Error! Incorrect Value! Please, try again!\n");
    }
  } while (*res < min_val || *res > max_val);
}

void s21_reverse(char s[]) {
  int i, j;
  char c;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void s21_itoa(int n, char s[]) {
  int i, sign;
  if ((sign = n) < 0) {
    n = -n;
  }
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  s21_reverse(s);
}

int File_exists(const char *filename) {
  FILE *fp = fopen(filename, "r");
  int is_exist = 0;
  if (fp != NULL) {
    is_exist = 1;
    fclose(fp);
  }
  return is_exist;
}
#endif  // S21_HELPERS_H_