CFLAGS= -fsanitize=address -g -Wall


.PHONY: compile test clean checkstyle format


compile: game_of_life

test: 
	echo "Let's Play the Game of Live and Prove if it works correctly!"

clean:
	rm -f *.o game_of_life game_of_life_test ../tui/*.o

checkstyle:
	clang-tidy --quiet $(wildcard *.c) $(wildcard *.h) --

format:
	clang-format -i $(wildcard *.c) $(wildcard *.h)


game_of_life: game_of_life.o game_of_life_lib.o bool_matrix.o ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o
	gcc $(CFLAGS) game_of_life.o game_of_life_lib.o bool_matrix.o -lm ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o -o game_of_life

game_of_life.o: game_of_life.c bool_matrix.h game_of_life_lib.h
	gcc $(CFLAGS) -c game_of_life.c -o game_of_life.o

game_of_life_lib.o: game_of_life_lib.c bool_matrix.h ../tui/tui.h ../tui/tui_io.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c game_of_life_lib.c -o game_of_life_lib.o

bool_matrix.o: bool_matrix.c ../tui/tui.h ../tui/tui_io.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c bool_matrix.c -o bool_matrix.o

game_of_life_test: game_of_life_test.o game_of_life_lib.o ../unity/unity.o
	gcc $(CFLAGS) game_of_life_test.o game_of_life_lib.o ../unity/unity.o -o game_of_life_test

game_of_life_test.o: game_of_life_test.c game_of_life_lib.h ../unity/unity.h
	gcc $(CFLAGS) -c game_of_life_test.c -o game_of_life_test.o


../tui/tui.o: ../tui/tui.c ../tui/tui.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c ../tui/tui.c -o ../tui/tui.o

../tui/tui_matrix.o: ../tui/tui_matrix.c ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c ../tui/tui_matrix.c -o ../tui/tui_matrix.o

../tui/tui_io.o: ../tui/tui_io.c ../tui/tui_io.h
	gcc $(CFLAGS) -c ../tui/tui_io.c -o ../tui/tui_io.o

../tui/ansi_codes.o: ../tui/ansi_codes.c ../tui/ansi_codes.h
	gcc $(CFLAGS) -c ../tui/ansi_codes.c -o ../tui/ansi_codes.o


../unity/unity.o: ../unity/unity.c ../unity/unity.h ../unity/unity_internals.h
	gcc $(CFLAGS) -g -c ../unity/unity.c -o ../unity/unity.o
