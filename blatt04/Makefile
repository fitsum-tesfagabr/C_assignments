# -*- Makefile -*-

.PHONY: compile test checkstyle format clean

compile: warmup_structs.o warmup_malloc.o  ../unity/unity.o

test: warmup_structs warmup_malloc
	./warmup_structs
	./warmup_malloc

warmup_structs: warmup_structs.o ../unity/unity.o
	gcc warmup_structs.o ../unity/unity.o -o warmup_structs

warmup_malloc: warmup_malloc.o ../unity/unity.o
	gcc warmup_malloc.o ../unity/unity.o -o warmup_malloc

warmup_malloc.o: warmup_malloc.c
	gcc -c warmup_malloc.c -o warmup_malloc.o

warmup_structs.o: warmup_structs.c
	gcc -c warmup_structs.c -o warmup_structs.o

../unity/unity.o: ../unity/unity.c
	gcc -c ../unity/unity.c -o ../unity/unity.o

checkstyle:
		clang-tidy --quiet *.c --

format:
		clang-format -i *.c 

clean:
		rm -f *.o ../unity/unity.o warmup_structs warmup_malloc

