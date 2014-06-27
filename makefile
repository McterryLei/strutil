CFLAGS = -Wall -g
TARGETS = test_string_convert test_kmp test_sdstring

all : $(TARGETS)

test_string_convert : test_string_convert.c string_convert.c string_convert.h
	gcc -o $@ test_string_convert.c string_convert.c $(CFLAGS)

test_kmp : test_kmp.c kmp.c kmp.h
	gcc -o $@ test_kmp.c kmp.c $(CFLAGS)

test_sdstring : test_sdstring.c sdstring.c sdstring.h
	gcc -o $@ test_sdstring.c sdstring.c $(CFLAGS)

clean:
	rm -f $(TARGETS)
