/**
 * @file kmp.c
 * @author Terry Lei
 * @email mcterrylei@google.com
 * @brief An implementable of KMP(Knuth–Morris–Pratt) algorithm
 */
#include "kmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int kmp_search_string(const char *str, const char *pattern) {
    int result = -1;
    int *table; 
    
    table = kmp_gen_partial_match_table(pattern);
    if (table == NULL)
        return -1;

    result = kmp_search_string_ex(str, pattern, table);

    free(table);
    return result;
}

int kmp_search_string_ex(const char *str, const char *pattern, int *partial_match_table) {
    assert(str);
    assert(pattern);
    assert(partial_match_table);

    int i, j;
    int pattern_len = strlen(pattern);

    for (i = 0, j = 0; i < strlen(str); i++) {
        while (j > 0 && str[i] != pattern[j]) 
            j = partial_match_table[j - 1];  /* rollback */

        if (str[i] == pattern[j]) 
            j++; 
        
        if (j >= pattern_len) 
            return i - j + 1;
    } 

    return -1;
}

int * kmp_gen_partial_match_table(const char *pattern) {
    int i, num_match;

    int *table = malloc(strlen(pattern) * sizeof(int));
    if (table == NULL)
        return NULL;

    table[0] = 0;

    /* the key is to manage the max matched string;
     * if the next char is not matched, then rollback the matched
     * string via previous partial matched table.
     */
    for (i = 1, num_match = 0; i < strlen(pattern); i++) {
        /* an example : 
         *   source string:  aaabbbaaa + pattern[i]         (i = 9)
         *   matched string:       aaa + pattern[num_match] (num_match = 3)
         */
        while (num_match > 0 && pattern[i] != pattern[num_match]) 
            num_match = table[num_match - 1]; /* rollback */

        if (pattern[i] == pattern[num_match])
            num_match++;

        table[i] = num_match; 
    }
    
    return table;
}

void kmp_dump_partial_match_table(const char *pattern, int *table) {
    int i;
    printf("Partial Match Table of \"%s\": [ ", pattern);
    for (i = 0; i < strlen(pattern); i++) {
        printf("%d ", table[i]);
    }
    printf("]\n");
}

