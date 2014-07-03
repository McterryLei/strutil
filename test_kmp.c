#include "kmp.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv) {
    const char str[] = "hello abcabd!";
    assert(kmp_search_string(str, "") == 0);
    assert(kmp_search_string(str, "hello") == 0);
    assert(kmp_search_string(str, "world") == -1);
    assert(kmp_search_string(str, "abcabd") == 6);

    const char *pattern = "ABCDABD";
    int table[strlen(pattern)];
    kmp_dump_partial_match_table(pattern, kmp_gen_partial_match_table(pattern, table));
    return 0;
}

