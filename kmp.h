/**
 * @file kmp.h
 * @author Terry Lei
 * @email mcterrylei@google.com
 * @brief An implementable of KMP(Knuth–Morris–Pratt) algorithm
 */
#ifndef _KMP_H_
#define _KMP_H_

/**
 * @brief Search for the pattern in string
 * @return index of matched substring
 * @return -1 if not found or no memory
 */
int kmp_search_string(const char *str, const char *pattern);

/**
 * @brief Search for the pattern in string
 *
 * This is specially for the case that searching one pattern in
 * mutiple strings, to save the partial matched table generation  
 * time.
 *
 * @return index of matched substring
 * @return -1 if not found 
 */
int kmp_search_string_ex(const char *str, const char *pattern, int *partial_match_table);

/** 
 * @brief Generate the KMP partial matched table
 * @return the array with same size as the pattern string
 * @return NULL if out of memory
 */
int * kmp_gen_partial_match_table(const char *pattern);

/** @brief Dump the partial match table to stdout */
void kmp_dump_partial_match_table(const char *pattern, int *table);

#endif
