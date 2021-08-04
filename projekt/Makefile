CFLAGS= -fsanitize=address -g -Wall


.PHONY: compile test clean checkstyle format


compile: mini_sweeper

refresh: compile clean

test: 
	echo "Check if Program runs appropraitely"

clean:
	rm -f *.o mini_sweeper ../tui/*.o ../unity/unity.o

checkstyle:
	clang-tidy --quiet $(wildcard *.c) $(wildcard *.h) --

format:
	clang-format -i $(wildcard *.c) $(wildcard *.h)


mini_sweeper: mini_sweeper.o mini_sweeper_lib.o memtools.o json_data.o json_reader.o json_printer.o reader.o menu.o game_matrix.o ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o vec.o
	gcc $(CFLAGS) mini_sweeper.o mini_sweeper_lib.o memtools.o json_data.o json_reader.o json_printer.o reader.o menu.o game_matrix.o ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o vec.o -o mini_sweeper

mini_sweeper.o: mini_sweeper.c menu.h ../tui/tui.h ../tui/tui_io.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c mini_sweeper.c -o mini_sweeper.o

mini_sweeper_lib.o: mini_sweeper_lib.c menu.h mini_sweeper_lib.h game_matrix.o ../tui/tui.h ../tui/tui_io.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c mini_sweeper_lib.c -o mini_sweeper_lib.o

game_matrix.o: game_matrix.c game_matrix.h
	gcc -fsanitize=address -g -c game_matrix.c -o game_matrix.o

menu.o: menu.c menu.h
	gcc $(CFLAGS) -c menu.c -o menu.o

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

vec.o: vec.c vec.h
	gcc -fsanitize=address -g -c vec.c -o vec.o

../tui/tui.o: ../tui/tui.c ../tui/tui.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c ../tui/tui.c -o ../tui/tui.o

../tui/tui_matrix.o: ../tui/tui_matrix.c ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c ../tui/tui_matrix.c -o ../tui/tui_matrix.o

../tui/tui_io.o: ../tui/tui_io.c ../tui/tui_io.h
	gcc $(CFLAGS) -c ../tui/tui_io.c -o ../tui/tui_io.o

../tui/ansi_codes.o: ../tui/ansi_codes.c ../tui/ansi_codes.h
	gcc $(CFLAGS) -c ../tui/ansi_codes.c -o ../tui/ansi_codes.o


../unity/unity.o: ../unity/unity.c ../unity/unity.h ../unity/unity_internals.h
	gcc -fsanitize=address -g -c ../unity/unity.c -o ../unity/unity.o
