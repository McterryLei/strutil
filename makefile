CFLAGS = -Wall -g
TARGETS = test_string_convert test_kmp

all : $(TARGETS)

test_string_convert : test_string_convert.c string_convert.c
	gcc -o $@ test_string_convert.c string_convert.c $(CFLAGS)

test_kmp : test_kmp.c kmp.c kmp.h
	gcc -o $@ test_kmp.c kmp.c $(CFLAGS)

clean:
	rm -f $(TARGETS)
