/** 
 * @file string_convert.h
 * @author Terry Lei 
 * @email mcterrylei@gmail.com
 * @breif Functions for converting string to value to suit common cases.
 */
#ifndef _STRING_CONVERT_H_
#define _STRING_CONVERT_H_

/**
 * @brief Convert char to integer
 *
 * Support octal, decimal and hex.
 *
 * @return the number value if succeeded
 * @return -1 if it is not a number
 */
int char2int(char c, int base);

/**
 * @brief Convert string to integer
 *
 * Support octal, decimal and hex.
 *
 * @param str [IN] The string of number
 * @param err [OUT] Set to 0 if no error, or -1 if not a valid number; it could be NULL.
 * @return the converted value if succeeded
 * @return 0 if not a valid number
 */
int str2int(const char *str, int *err);

#endif
