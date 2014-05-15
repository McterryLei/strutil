#include "string_convert.h"
#include <stdio.h>
#include <assert.h>

void test_str2int(const char *str, int expected_value, int expected_err_code) {
  int err; 
  int value = str2int(str, &err);    
  printf("test converting %s\n", str);
  assert(value == expected_value);
  assert(err == expected_err_code);
}

int main(int argc, char **argv) {
  test_str2int("123", 123, 0);  
  test_str2int("0xa2", 0xa2, 0);  
  test_str2int("-012", -012, 0);  
  test_str2int("0", 0, 0);

  test_str2int("", 0, -1);
  test_str2int("-", 0, -1);
  test_str2int("1a", 0, -1);
  test_str2int("0ab", 0, -1);
  test_str2int("0xfg", 0, -1);
  return 0;
}
