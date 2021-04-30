# -*- Makefile -*-

.PHONY: compile test checkstyle format clean

compile: fib_lib.o fib_slow fib_fast fib_test

test: fib_test
	./fib_test

fib_test: fib_test.o fib_lib.o ../unity/unity.o
	gcc fib_test.o fib_lib.o ../unity/unity.o -o fib_test

fib_test.o: fib_test.c
	gcc -c fib_test.c -o fib_test.o

fib_lib.o: fib_lib.c
	gcc -c fib_lib.c -o fib_lib.o

../unity/unity.o: ../unity/unity.c
	gcc -c ../unity/unity.c -o ../unity/unity.o

fib_slow: fib_slow.o fib_lib.o
	gcc fib_slow.o fib_lib.o -o fib_slow

fib_slow.o: fib_slow.c
	gcc -c fib_slow.c -o fib_slow.o

fib_fast: fib_fast.o fib_lib.o
	gcc fib_fast.o fib_lib.o -o fib_fast

fib_fast.o: fib_fast.c
	gcc -c fib_fast.c -o fib_fast.o


checkstyle:
		clang-tidy --quiet *.c *.h --

format:
		clang-format -i *.c *.h

clean:
		rm -f ../unity/unity.o fib_test.o fib_test fib_lib.o fib_slow.o fib_slow fib_fast.o fib_fast

