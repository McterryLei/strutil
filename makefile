test_string_convert:test_string_convert.c string_convert.c
	gcc -o $@ test_string_convert.c string_convert.c -Wall -g

clean:
	rm -f test_string_convert
