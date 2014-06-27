#include "sdstring.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv) {
    const char *msg = "Hello";
    sdstring *str = sdstring_new(msg);

    assert(sdstring_len(str) == strlen(msg));
    assert(sdstring_avail(str) == strlen(msg));
    assert(sdstring_equal_cstr(str, msg));

    int oldavail = sdstring_avail(str);
    sdstring_cat(str, "Tom");
    assert(sdstring_len(str) == strlen(msg)+strlen("Tom"));
    assert(sdstring_avail(str) == oldavail-strlen("Tom"));
    assert(sdstring_equal_cstr(str, "HelloTom"));

    assert(sdstring_startwith(str, "Hello"));
    assert(sdstring_endwith(str, "Tom"));

    sdstring_catprintf(str, " (%s) : %032d", "32", 0);
    printf("%s (len=%d, avail=%d)\n", str->buf, sdstring_len(str), sdstring_avail(str));


    sdstring_clear(str);
    assert(sdstring_len(str) == 0);

    sdstring_release(str);

    printf("All tests succeeded!\n");
    return 0;
}
