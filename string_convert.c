/** 
 * @file string_convert.c
 * @author Terry Lei 
 * @email <mcterrylei@gmail.com>
 * @breif Implementation of types defined in string_convert.h
 */
#include "string_convert.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>

#define SET_ERROR(err, code)    if (err) { *err = code; }

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
  assert(str);

  long long result = 0;
  int sign = 1;
  int base = 10;
  unsigned int max_int = INT_MAX;
  int i = 0;

  SET_ERROR(err, 0);

  /* skip space */
  while (isspace(str[i]))
    i++;          

  /* check sign char */
  if (str[i] == '-') { 
    sign = -1;  
    max_int = -INT_MIN;
    i++;
  }
  else if (str[i] == '+') {
    sign = 1;  
    max_int = INT_MAX;
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
      SET_ERROR(err, -1);
      return result;
    }

    /* check if overflow or underflow */
    if (result > (max_int - tmp) / base) {
      SET_ERROR(err, -1)
      return (int)max_int; 
    }

    result *= base;
    result += tmp;
  } while (str[++i]);

  return result * sign;
}

