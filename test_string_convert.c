#include "string_convert.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>

void test_str2int(const char *str, int expected_value, int expected_err_code) {
  int err; 
  int value = str2int(str, &err);    
  printf("testing converting %s :\n", str);
  printf("  >> expected: value=%d err=%d\n", expected_value, expected_err_code);
  printf("  >> got:      value=%d err=%d\n", value, err);
  printf("\n");
  assert(value == expected_value);
  assert(err == expected_err_code);
}

int main(int argc, char **argv) {
  /* pass err as NULL to igonre the error */
  assert(str2int("123", NULL) == 123);

  test_str2int("123", 123, 0);  
  test_str2int("0xa2", 0xa2, 0);  
  test_str2int("-012", -012, 0);  
  test_str2int("0", 0, 0);

  test_str2int("", 0, -1);
  test_str2int("-", 0, -1);

  test_str2int("a1", 0, -1);
  test_str2int("0ab", 0, -1);
  test_str2int("0xgh", 0, -1);

  test_str2int(" 12abc", 12, -1);
  test_str2int(" 20 ", 20, -1);

  char buf[128];

  sprintf(buf, "%d", INT_MIN);
  test_str2int(buf, INT_MIN, 0);

  sprintf(buf, "%d", INT_MAX);
  test_str2int(buf, INT_MAX, 0);

  /* underflow */
  sprintf(buf, "%lld", (long long)INT_MIN-1);
  test_str2int(buf, INT_MIN, -1);

  /* overflow */
  sprintf(buf, "%lld", (long long)INT_MAX+1);
  test_str2int(buf, INT_MAX, -1);

  printf("All tests succeeds!\n");  
  return 0;
}
