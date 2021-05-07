# blatt02 (16 / 16.0)

### Aufgabe 1 - Fibonacci nach Rezept

- Kommentare fehlen für jede einzelne Funktion in der `fib_lib.h`. Dafür muss ich nächstes mal Abzug geben. In `fib_lib.c` kannst du quasi die Kommentare löschen und ins Header-file übertragen.

**Punktzahl: 3/3**

### Aufgabe 2 - Unittests I

sehr schön

**Punktzahl: 3/3**

### Aufgabe 3 - Benutzereingaben für Fibonacci

Klappt super

**Punktzahl: 3/3**

### Aufgabe 4 - Fibonacci on Steroids

sehr schön

**Punktzahl: 5/5**

### Aufgabe 5 - Benchmarking

**Punktzahl: 0/0**

### Aufgabe 6 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**

### Feedback:

Sehr schöne Abgabe!

Zum Makefile: 

- `fib_lib.h` muss ebenfalls in die File-Abhängigkeit für `fib_slow.o` , `fib_test.o` und `fib_fast.o` geschrieben werden. Einfach weil ja in den .c-files `#include "./fib_lib.h"` steht und man dem Makefile ja mitteilen will, dass dieses File dann auch benötigt wird. Auch wenn es redundant erscheint. 
- Wie bei `checkstyle` bzw. `format` kannt du die Syntax `*.o` bei` clean: ` verwenden.

### Anmerkungen:

- Wenn du Fragen zur Korrektur hast, kannst du mir gerne einfach
  eine Mail schreiben.
- Fragen zur Vorlesung und zu den Übungen solltest du aber am
  besten ins Forum stellen, damit jeder etwas von der Antwort hat.

Christian: <christian.handschuh@uranus.uni-freiburg.de>