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
    return sdstring_newlen(str, strlen(str));
}

sdstring * sdstring_newlen(const char *str, int len) {
    sdstring *s = calloc(1, sizeof(sdstring));
    
    if (len == 0) {
        /* for we need one byte to store '\0', so we 
         * should preallocate some memory 
         */
        sdstring_make_room_for(s, 8);
        s->buf[0] = '\0';
    }
    else { 
        sdstring_make_room_for(s, len);
        memcpy(s->buf, str, len);
        sdstring_increase_len(s, len);
    }

    return s;
}

sdstring * sdstring_empty() {
    return sdstring_newlen("", 0);
}

void sdstring_release(sdstring *s) {
    if (s->buf)
        free(s->buf);
    free(s);
}

void sdstring_clear(sdstring *s) {
    s->len = 0;
    s->buf[0] = '\0';
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

void sdstring_copy(sdstring *s, const char *str) {
    sdstring_copylen(s, str, strlen(str));
}

void sdstring_copylen(sdstring *s, const char *str, int len) {
    assert(len >= 0);
    sdstring_clear(s);
    sdstring_catlen(s, str, len);
} 

void sdstring_cat(sdstring *s, const char *str) {
    sdstring_catlen(s, str, strlen(str));
}

void sdstring_catlen(sdstring *s, const char *str, int addlen) {
    assert(addlen >= 0);
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

int sdstring_search(sdstring *s, const char *pattern) {
    char *p = strstr(s->buf, pattern);
    if (p == NULL)
        return -1;
    return p - s->buf;
}

void sdstring_substr(sdstring *s, sdstring *substr, int start, int count) {
    assert(substr);
    assert(start >= 0);
    assert(count >= 0);
   
    if (count > s->len - start) 
        count = s->len - start;

    sdstring_copylen(substr, s->buf+start, count);
}

void sdstring_trim(sdstring *s, int start, int count) {
    assert(start >= 0);
    assert(count >= 0);

    if (count == 0)
        return;

    if (count > s->len - start)
        count = s->len - start;

    /*  
     *  #####xxxxxx####
     *       |     |
     *       v     V
     *     start  start+count
     */
    char *tmp_p = s->buf + start + count;
    int tmp_count = s->len - start - count;
    assert(tmp_count >= 0);

    memmove(s->buf+start, tmp_p, tmp_count);
    sdstring_increase_len(s, -count); 
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

