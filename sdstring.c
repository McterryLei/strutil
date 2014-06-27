/**
 * @file sdstring.c
 * @author Terry Lei
 * @email mcterrylei@gmail.com
 * @brief Implemetation of types defined in sdstring.h
 */
#include "sdstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_PREALLOC    (1024*1024)

sdstring * sdstring_new(const char *str) {
    sdstring *s = calloc(1, sizeof(sdstring));
    sdstring_cat(s, str);
    return s;
}

sdstring * sdstring_empty() {
    sdstring *s = calloc(1, sizeof(sdstring));
    return s;
}

void sdstring_release(sdstring *s) {
    if (s->buf)
        free(s->buf);
    free(s);
}

void sdstring_clear(sdstring *s) {
    s->len = 0;
}

int sdstring_len(sdstring *s) {
    return s->len;
}

int sdstring_avail(sdstring *s) {
    return s->free;
}

bool sdstring_equal(sdstring *s1, sdstring *s2) {
    if (s1->len != s2->len)
        return false;
    return memcmp(s1->buf, s2->buf, s1->len) == 0;
}

bool sdstring_equal_cstr(sdstring *s, const char *str) {
    int len = strlen(str);
    if (s->len != len)
        return false;
    return memcmp(s->buf, str, len) == 0;
}

void sdstring_cat(sdstring *s, const char *str) {
    sdstring_catlen(s, str, strlen(str));
}

void sdstring_catlen(sdstring *s, const char *str, int addlen) {
    sdstring_make_room_for(s, addlen);
    memcpy(s->buf+s->len, str, addlen);
    sdstring_increase_len(s, addlen);
}

void sdstring_catprintf(sdstring *s, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    sdstring_catvprintf(s, fmt, ap);
    va_end(ap);
}

void sdstring_catvprintf(sdstring *s, const char *fmt, va_list ap) {
    int addlen;
    va_list ap1, ap2;

    va_copy(ap1, ap);
    va_copy(ap2, ap);

    /* calculate room to add */
    addlen = vsnprintf(NULL, 0, fmt, ap1);
    sdstring_make_room_for(s, addlen);

    /* append */
    vsprintf(s->buf+s->len, fmt, ap2);
    sdstring_increase_len(s, addlen);
    
    va_end(ap1);
    va_end(ap2);
}

bool sdstring_startwith(sdstring *s, const char *pattern) {
    int pattern_len = strlen(pattern);
    if (s->len < pattern_len)
        return false;
    return memcmp(s->buf, pattern, pattern_len) == 0;
}

bool sdstring_endwith(sdstring *s, const char *pattern) {
    int pattern_len = strlen(pattern);
    if (s->len < pattern_len)
        return false;
    return memcmp(s->buf + s->len - pattern_len, pattern, pattern_len) == 0;
}

void sdstring_make_room_for(sdstring *s, int addlen) {
    if (s->free >= addlen)
        return;

    int newlen = s->len + addlen;

    /* preallocate */
    if (newlen >= MAX_PREALLOC) 
        newlen += MAX_PREALLOC;
    else 
        newlen = newlen * 2;

    /* expand */
    s->buf = realloc(s->buf, newlen+1); /* one more byte for '\0' */ 
    s->free = newlen - s->len;
    assert(s->free >= 0);
}

void sdstring_increase_len(sdstring *s, int addlen) {
    assert(s->free >= addlen);
    s->len += addlen;
    s->free -= addlen;
    assert(s->len >= 0);
    s->buf[s->len] = '\0';
}

