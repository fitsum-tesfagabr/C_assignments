CFLAGS= -fsanitize=address -g -Wall


.PHONY: compile test clean checkstyle format


compile: table

test: list_test
	./list_test

clean:
	rm -f *.o list_test table

checkstyle:
	clang-tidy --quiet $(wildcard *.c) $(wildcard *.h) --

format:
	clang-format -i $(wildcard *.c) $(wildcard *.h)


list.o: list.c list.h
	gcc -fsanitize=address -g -c list.c -o list.o

list_test.o: list_test.c list.h
	gcc -fsanitize=address -g -c list_test.c -o list_test.o

list_test: list_test.o list.o ../unity/unity.o
	gcc -fsanitize=address -g list_test.o list.o ../unity/unity.o -o list_test


table_lib.o: table_lib.c table_lib.h
	gcc -fsanitize=address -g -c table_lib.c -o table_lib.o

table.o: table.c table_lib.h
	gcc -fsanitize=address -g -c table.c -o table.o

table: table.o table_lib.o
	gcc -fsanitize=address -g table.o table_lib.o -o table


../unity/unity.o: ../unity/unity.c ../unity/unity.h ../unity/unity_internals.h
	gcc -fsanitize=address -g -c ../unity/unity.c -o ../unity/unity.o
