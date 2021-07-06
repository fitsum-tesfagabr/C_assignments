CFLAGS= -fsanitize=address -g -Wall


.PHONY: compile test clean checkstyle format


compile: plot

test: ivec_ext_test
	./ivec_ext_test

clean:
	rm -f *.o ivec_ext_test plot ../tui/*.o

checkstyle:
	clang-tidy --quiet $(wildcard *.c) $(wildcard *.h) --

format:
	clang-format -i $(wildcard *.c) $(wildcard *.h)


ivec_ext.o: ivec_ext.c ivec_ext.h ivec.h
	gcc $(CFLAGS) -c ivec_ext.c -o ivec_ext.o

ivec_ext_test: ivec_ext_test.o ivec_ext.o ivec.o ../unity/unity.o
	gcc $(CFLAGS) ivec_ext_test.o ivec_ext.o ivec.o ../unity/unity.o -o ivec_ext_test

ivec_ext_test.o: ivec_ext_test.c ivec_ext.h ivec.h ../unity/unity.h
	gcc $(CFLAGS) -c ivec_ext_test.c -o ivec_ext_test.o

ivec.o: ivec.c ivec.h
	gcc $(CFLAGS) -c ivec.c -o ivec.o


plot: plot.o plot_lib.o ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o
	gcc $(CFLAGS) plot.o plot_lib.o -lm ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o -o plot

plot.o: plot.c plot_lib.h
	gcc $(CFLAGS) -c plot.c -o plot.o

plot_lib.o: plot_lib.c ../tui/tui.h ../tui/tui_io.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c plot_lib.c -o plot_lib.o


../tui/tui.o: ../tui/tui.c ../tui/tui.h ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c ../tui/tui.c -o ../tui/tui.o

../tui/tui_matrix.o: ../tui/tui_matrix.c ../tui/tui_matrix.h ../tui/ansi_codes.h
	gcc $(CFLAGS) -c ../tui/tui_matrix.c -o ../tui/tui_matrix.o

../tui/tui_io.o: ../tui/tui_io.c ../tui/tui_io.h
	gcc $(CFLAGS) -c ../tui/tui_io.c -o ../tui/tui_io.o

../tui/ansi_codes.o: ../tui/ansi_codes.c ../tui/ansi_codes.h
	gcc $(CFLAGS) -c ../tui/ansi_codes.c -o ../tui/ansi_codes.o


../unity/unity.o: ../unity/unity.c ../unity/unity.h ../unity/unity_internals.h
	gcc $(CFLAGS) -c ../unity/unity.c -o ../unity/unity.o
