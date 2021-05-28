# -*- Makefile -*-

.PHONY: compile test checkstyle format clean all

all: compile checkstyle format test

compile: vec_test statistics

test: vec_test
	./vec_test

vec.o: vec.c vec.h
	gcc -fsanitize=address -g -c vec.c -o vec.o

vec_test: vec.o vec_test.o ../unity/unity.o vec.h
	gcc -fsanitize=address -g vec_test.o vec.o ../unity/unity.o -o vec_test

vec_test.o: vec_test.c vec.h
	gcc -fsanitize=address -g -c vec_test.c -o vec_test.o

../unity/unity.o: ../unity/unity.c
	gcc -fsanitize=address -g -c ../unity/unity.c -o ../unity/unity.o

statistics: statistics.o vec.o vec.h
	gcc -fsanitize=address -g statistics.o vec.o -o statistics

statistics.o: statistics.c vec.h
	gcc -fsanitize=address -g -c statistics.c -o statistics.o
checkstyle:
		clang-tidy --quiet *.c *.h --

format:
		clang-format -i *.c *.h

clean:
		rm -f *.o ../unity/unity.o vec_test statistics

