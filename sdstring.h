/**
 * @file sdstring.h
 * @author Terry Lei
 * @email mcterrylei@gmail.com
 * @brief A simple dynamic string module
 */
#ifndef _SDSTRING_H_
#define _SDSTRING_H_

#include <stdarg.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_stdstring {
    int    len;
    int    free;
    char * buf; /* store the string data */
} sdstring;

sdstring * sdstring_new(const char *str);
sdstring * sdstring_newlen(const char *str, int len);
sdstring * sdstring_empty(); /* create an empty string */
void sdstring_release(sdstring *s);

/** set the string empty */
void sdstring_clear(sdstring *s);

int  sdstring_len(sdstring *s);
int  sdstring_avail(sdstring *s);

bool sdstring_equal(sdstring *s1, sdstring *s2);
bool sdstring_equal_cstr(sdstring *s, const char *str);

void sdstring_copy(sdstring *s, const char *str);  
void sdstring_copylen(sdstring *s, const char *str, int len);  

void sdstring_cat(sdstring *s, const char *str);
void sdstring_catlen(sdstring *s, const char *str, int addlen);
void sdstring_catprintf(sdstring *s, const char *fmt, ...);
void sdstring_catvprintf(sdstring *s, const char *fmt, va_list ap);

/* for checking prefix or subffix */
bool sdstring_startwith(sdstring *s, const char *pattern);
bool sdstring_endwith(sdstring *s, const char *pattern);

/**
 * @brief Search the pattern in string
 * @return the index of first matched substring
 * @return -1 if not found
 */
int  sdstring_search(sdstring *s, const char *pattern);

/**
 * @brief Copy the substring beginning with specified position
 * @param substr [OUT] Store the copy of substring
 * @param start The begin position of substring 
 * @param count The number of bytes to copy 
 */
void sdstring_substr(sdstring *s, sdstring *substr, int start, int count);

/** 
 * @biref Trim the data in string 
 * @param start the start position to trim
 * @param count the count of bytes to trim
 */
void sdstring_trim(sdstring *s, int start, int count);


/*=== Functions below are low level functions ===*/

/** @biref make sure there is room available for specified size */
void sdstring_make_room_for(sdstring *s, int addlen);

/**
 * @brief Increase the length of string
 *
 * Used to fix the string length after calling sdstring_make_room_for() and
 * writing something after the end of string.
 *
 * Note: It is possible to use a negative increment in order to
 * right-trim the string.
 *
 * @example
 *   oldlen = sdstring_len(s);
 *   sdstring_make_room_for(s, BUFFER_SIZE);
 *   nread = read(fd, s+oldlen, BUFFER_SIZE);
 *   // omit handle error codes here
 *   sdstring_increase_len(s, nhread);
 */
void sdstring_increase_len(sdstring *s, int addlen);

#ifdef __cplusplus
}
#endif

#endif
