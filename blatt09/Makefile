CFLAGS= -fsanitize=address -g -Wall


.PHONY: compile test clean checkstyle format


compile: game event_example

test: game_highscores_test
	./game_highscores_test

clean:
	rm -f *.o game game_highscores_test event_example ../tui/*.o

checkstyle:
	clang-tidy --quiet $(wildcard *.c) $(wildcard *.h) --

format:
	clang-format -i $(wildcard *.c) $(wildcard *.h)


event.o: event.c event.h
	gcc $(CFLAGS) -c event.c -o event.o

event_example.o: event_example.c event.h
	gcc $(CFLAGS) -c event_example.c -o event_example.o

event_example: event_example.o event.o
	gcc $(CFLAGS) event_example.o event.o -o event_example


memtools.o: memtools.c memtools.h
	gcc $(CFLAGS) -c memtools.c -o memtools.o


json_data.o: json_data.c json_data.h memtools.h vec.h
	gcc $(CFLAGS) -c json_data.c -o json_data.o

json_reader.o: json_reader.c json_data.h json_reader.h memtools.h vec.h
	gcc $(CFLAGS) -c json_reader.c -o json_reader.o

json_printer.o: json_printer.c json_printer.h json_data.h memtools.h vec.h
	gcc $(CFLAGS) -c json_printer.c -o json_printer.o

reader.o: reader.c reader.h
	gcc $(CFLAGS) -c reader.c -o reader.o


game: game.o game_lib.o game_highscores.o json_data.o json_reader.o json_printer.o memtools.o reader.o vec.o ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o
	gcc $(CFLAGS) game.o game_lib.o game_highscores.o json_data.o json_reader.o json_printer.o memtools.o reader.o vec.o ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o -o game

game.o: game.c memtools.h vec.h ../tui/tui.h ../tui/tui_io.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c game.c -o game.o

game_lib.o: game_lib.c game_lib.h memtools.h vec.h ../tui/tui.h ../tui/tui_io.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c game_lib.c -o game_lib.o

game_highscores.o: game_highscores.c game_highscores.h memtools.h vec.h json_reader.h json_printer.h json_data.h ../tui/tui.h ../tui/tui_io.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c game_highscores.c -o game_highscores.o

vec.o: vec.c vec.h memtools.h
	gcc $(CFLAGS) -g -c vec.c -o vec.o

game_highscores_test: game_highscores_test.o game_highscores.o memtools.o vec.o json_data.o json_reader.o json_printer.o reader.o memtools.o ../unity/unity.o
	gcc $(CFLAGS) game_highscores_test.o game_highscores.o vec.o json_data.o json_reader.o json_printer.o reader.o memtools.o ../unity/unity.o -o game_highscores_test

game_highscores_test.o: game_highscores_test.c game_highscores.h memtools.h vec.h ../unity/unity.h
	gcc $(CFLAGS) -c game_highscores_test.c -o game_highscores_test.o


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
