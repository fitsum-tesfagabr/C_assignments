# -*- Makefile -*-

.PHONY: compile test checkstyle format clean

compile: warmup.o symcrypt_lib.o symcrypt_test.o ../unity/unity.o symcrypt

test: warmup symcrypt_test
	./warmup
	./symcrypt_test

warmup: warmup.o ../unity/unity.o
	gcc warmup.o ../unity/unity.o -o warmup

symcrypt: symcrypt.o symcrypt_lib.o symcrypt_lib.h
	gcc symcrypt.o symcrypt_lib.o -o symcrypt

symcrypt.o: symcrypt.c
	gcc -c symcrypt.c -o symcrypt.o


symcrypt_test: symcrypt_test.o symcrypt_lib.o symcrypt_lib.h ../unity/unity.o
	gcc symcrypt_test.o symcrypt_lib.o ../unity/unity.o -o symcrypt_test

symcrypt_lib.o: symcrypt_lib.c symcrypt_lib.h
	gcc -c symcrypt_lib.c -o symcrypt_lib.o

symcrypt_test.o: symcrypt_test.c symcrypt_lib.h ../unity/unity.h
	gcc -c symcrypt_test.c -o symcrypt_test.o

warmup.o: warmup.c
	gcc -c warmup.c -o warmup.o

../unity/unity.o: ../unity/unity.c
	gcc -c ../unity/unity.c -o ../unity/unity.o

checkstyle:
		clang-tidy --quiet *.c *.h --

format:
		clang-format -i *.c *.h

clean:
		rm -f *.o ../unity/unity.o warmup symcrypt_lib symcrypt_test symcrypt

