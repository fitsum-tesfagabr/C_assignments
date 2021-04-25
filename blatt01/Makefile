.PHONY: compile test checkstyle format clean

compile: hello bye

test:
	echo "Everything is ok. There are no tests, yet."

checkstyle:
	clang-tidy --quiet *.c --

format:
	clang-format -i *.c

clean:
	rm -f hello.o hello bye.o bye

hello.o: hello.c
	gcc -c hello.c -o hello.o

hello: hello.o
	gcc hello.o -o hello

bye.o: bye.c
	gcc -c bye.c -o bye.o

bye: bye.o
	gcc bye.o -o bye
