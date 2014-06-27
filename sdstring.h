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
sdstring * sdstring_empty(); /* create an empty string */
void sdstring_release(sdstring *s);

void sdstring_clear(sdstring *s);

int  sdstring_len(sdstring *s);
int  sdstring_avail(sdstring *s);

bool sdstring_equal(sdstring *s1, sdstring *s2);
bool sdstring_equal_cstr(sdstring *s, const char *str);

void sdstring_cat(sdstring *s, const char *str);
void sdstring_catlen(sdstring *s, const char *str, int addlen);
void sdstring_catprintf(sdstring *s, const char *fmt, ...);
void sdstring_catvprintf(sdstring *s, const char *fmt, va_list ap);

bool sdstring_startwith(sdstring *s, const char *pattern);
bool sdstring_endwith(sdstring *s, const char *pattern);

/* Low level functions */
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
