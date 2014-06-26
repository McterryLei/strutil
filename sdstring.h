/**
 * @file sdstring.h
 * @author Terry Lei
 * @email mcterrylei@gmail.com
 * @brief A simple dynamic string module
 */
#ifndef _SDSTRING_H_
#define _SDSTRING_H_

#include <stdarg.h>

typedef struct tag_stdstring {
    int    len;
    int    free;
    char * buf; /* store the string data */
} sdstring;

sdstring * sdstring_new(const char *str);
sdstring * sdstring_empty();
void sdstring_release(sdstring *s);

void sdstring_clear(sdstring *s);

int  sdstring_len(sdstring *s);
int  sdstring_avail(sdstring *s);

void sdstring_cat(sdstring *s, const char *str);
void sdstring_catlen(sdstring *s, const char *str, int addlen);
void sdstring_catprintf(sdstring *s, const char *fmt, ...);
void sdstring_catvprintf(sdstring *s, const char *fmt, va_list ap);

/* Low level function */
void sdstring_make_room_for(sdstring *s, int addlen);

#endif
