#include "sdstring.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv) {
    const char *msg = "Hello";
    sdstring *str = sdstring_new(msg);

    /* test new */
    assert(sdstring_len(str) == strlen(msg));
    assert(sdstring_avail(str) == strlen(msg));
    assert(sdstring_equal_cstr(str, msg));

    /* test cat */
    int oldavail = sdstring_avail(str);
    sdstring_cat(str, "Tom");
    assert(sdstring_len(str) == strlen(msg)+strlen("Tom"));
    assert(sdstring_avail(str) == oldavail-strlen("Tom"));
    assert(sdstring_equal_cstr(str, "HelloTom"));

    /* start check subfix and prefix */
    assert(sdstring_startwith(str, "Hello"));
    assert(sdstring_endwith(str, "Tom"));

    /* test search */
    assert(sdstring_search(str, "He") == 0);
    assert(sdstring_search(str, "Tom") == 5);
    assert(sdstring_search(str, "Tomm") == -1);

    /* test substring */
    sdstring *substr = sdstring_empty();
    sdstring_substr(str, substr, 3, 5);
    assert(sdstring_equal_cstr(substr, "loTom"));

    /* test trim */
    sdstring_trim(str, 2, 3); /* i.e remove "llo" in string */
    assert(sdstring_equal_cstr(str, "HeTom"));
    assert(sdstring_len(str) == strlen("HelloTom")-3);
    
    /* test catprintf  */
    sdstring_catprintf(str, " (%s) : %032d", "32", 0);
    printf("%s (len=%d, avail=%d)\n", str->buf, sdstring_len(str), sdstring_avail(str));

    /* test clear */
    sdstring_clear(str);
    assert(sdstring_len(str) == 0);

    sdstring_release(str);

    printf("All tests succeeded!\n");
    return 0;
}
