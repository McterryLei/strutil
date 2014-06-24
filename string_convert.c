#include "string_convert.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int char2int(char c, int base) {
  assert(base > 0);
  assert(base <= 10 || base == 16);

  if (base <= 10) {
    if (c >= '0' && c < '0'+base)
      return c - '0';
  }
  else {
    /* hex */
    if (c >= '0' && c <= '9')
      return c - '0';
    if (c >= 'a' && c <= 'f')
      return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
      return c - 'A' + 10;
  }

  return -1;
}

int str2int(const char *str, int *err) {
  int result = 0;
  bool is_negative = false;
  int base = 10;
  int i = 0;

  assert(str);
  assert(err);

  *err = 0;

  /* check sign char */
  if (str[i] == '-') {
    i++;
    is_negative = true;
  }
  else if (str[i] == '+') {
    i++;
  }

  /* check base */
  if (str[i] == '0') {
    if (str[i+1] == 'x' || str[i+1] == 'X') {
      base = 16;
      i += 2;
    }
    else if (str[i+1] != '\0') {
      base = 8;
      i++;
    }
  }

  /* handle the number part */
  do {
    int tmp = char2int(str[i], base);
    if (tmp < 0) {
      *err = -1;
      return 0;
    }

    result *= base;
    result += tmp;
  } while (str[++i] != '\0');

  if (is_negative)
    result *= -1;

  return result;
}

