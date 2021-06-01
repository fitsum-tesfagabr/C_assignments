CFLAGS= -fsanitize=address -g -Wall


.PHONY: compile test clean checkstyle format


compile: ansi_example tui_matrix_example tui_example rainbows

test: tui_matrix_test
	./tui_matrix_test

clean:
	rm -f *.o ansi_example tui_example tui_matrix_example tui_matrix_test rainbows

checkstyle:
	clang-tidy --quiet $(wildcard *.c) $(wildcard *.h) --

format:
	clang-format -i $(wildcard *.c) $(wildcard *.h)


tui.o: tui.c tui.h tui_matrix.h ansi_codes.h
	gcc $(CFLAGS) -c tui.c -o tui.o

tui_example: tui_example.o tui_matrix.o tui_io.o ansi_codes.o tui.o
	gcc $(CFLAGS) tui_example.o tui_matrix.o tui_io.o ansi_codes.o tui.o -o tui_example

tui_example.o: tui_example.c tui_matrix.h tui_io.h ansi_codes.h tui.h
	gcc $(CFLAGS) -c tui_example.c -o tui_example.o

tui_matrix.o: tui_matrix.c tui_matrix.h ansi_codes.h
	gcc $(CFLAGS) -c tui_matrix.c -o tui_matrix.o

tui_matrix_example: tui_matrix_example.o tui_matrix.o ansi_codes.o
	gcc $(CFLAGS) tui_matrix_example.o tui_matrix.o ansi_codes.o -o tui_matrix_example

tui_matrix_example.o: tui_matrix_example.c tui_matrix.h ansi_codes.h
	gcc $(CFLAGS) -c tui_matrix_example.c -o tui_matrix_example.o

tui_matrix_test: tui_matrix_test.o tui_matrix.o ansi_codes.o ../unity/unity.o
	gcc $(CFLAGS) tui_matrix_test.o tui_matrix.o ansi_codes.o ../unity/unity.o -o tui_matrix_test

tui_matrix_test.o: tui_matrix_test.c ../unity/unity.h tui_matrix.h ansi_codes.h
	gcc $(CFLAGS) -c tui_matrix_test.c -o tui_matrix_test.o

tui_io.o: tui_io.c tui_io.h
	gcc $(CFLAGS) -c tui_io.c -o tui_io.o

ansi_codes.o: ansi_codes.c ansi_codes.h
	gcc $(CFLAGS) -c ansi_codes.c -o ansi_codes.o

ansi_example: ansi_codes.o ansi_example.o
	gcc $(CFLAGS) ansi_example.o ansi_codes.o -o ansi_example

ansi_example.o: ansi_example.c ansi_codes.h
	gcc $(CFLAGS) -c ansi_example.c -o ansi_example.o

rainbows: rainbows.o tui_matrix.o tui_io.o ansi_codes.o tui.o
	gcc $(CFLAGS) rainbows.o tui_matrix.o tui_io.o ansi_codes.o tui.o -o rainbows

rainbows.o: rainbows.c tui_matrix.h tui_io.h ansi_codes.h tui.h
	gcc $(CFLAGS) -c rainbows.c -o rainbows.o



../unity/unity.o: ../unity/unity.c ../unity/unity.h ../unity/unity_internals.h
	gcc -fsanitize=address -g -c ../unity/unity.c -o ../unity/unity.o
