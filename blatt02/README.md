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
## Build Log  🟢 (success)
### clone  🟢 (success)
```bash
Initialized empty Git repository in /drone/src/.git/
+ git fetch origin +refs/heads/master:
From https://git.inpro.informatik.uni-freiburg.de/2021-ss-c-kurs/ft101
 * branch            master     -> FETCH_HEAD
 * [new branch]      master     -> origin/master
+ git checkout fe39c0b33a0778e1afd7346983be9c7a8bfd5acb -b master
Already on 'master'

```

### retrieve current sheet  🟢 (success)
```bash
+ export SHEET=$(curl https://courses.inpro.informatik.uni-freiburg.de/2021-SS/c-kurs/active_exercises | head -n 1)
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0100     7  100     7    0     0    120      0 --:--:-- --:--:-- --:--:--   120
+ echo Currently active exercise directory: $SHEET
Currently active exercise directory: blatt02
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -c fib_lib.c -o fib_lib.o
gcc -c fib_slow.c -o fib_slow.o
gcc fib_slow.o fib_lib.o -o fib_slow
gcc -c fib_fast.c -o fib_fast.o
gcc fib_fast.o fib_lib.o -o fib_fast
gcc -c fib_test.c -o fib_test.o
gcc -c ../unity/unity.c -o ../unity/unity.o
gcc fib_test.o fib_lib.o ../unity/unity.o -o fib_test

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0m./fib_test
fib_test.c:20:test_fib_slow_0:[42mPASS[00m
fib_test.c:21:test_fib_slow_1:[42mPASS[00m
fib_test.c:22:test_fib_slow_15:[42mPASS[00m
fib_test.c:24:test_fib_fast_0:[42mPASS[00m
fib_test.c:25:test_fib_fast_1:[42mPASS[00m
fib_test.c:26:test_fib_fast_35:[42mPASS[00m

-----------------------
6 Tests 0 Failures 0 Ignored 
[42mOK[00m

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet *.c *.h --
232 warnings generated.
233 warnings generated.
465 warnings generated.
779 warnings generated.
779 warnings generated.
[1m/drone/src/blatt02/fib_fast.c:7:3: [0m[0;1;35mwarning: [0m[1mCall to function 'scanf' is insecure as it does not provide security checks introduced in the C11 standard. Replace with analogous functions that support length arguments or provides boundary checks such as 'scanf_s' in case of C11 [clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling][0m
  scanf("%d", &n);
[0;1;32m  ^
[0m[1m/drone/src/blatt02/fib_fast.c:7:3: [0m[0;1;30mnote: [0mCall to function 'scanf' is insecure as it does not provide security checks introduced in the C11 standard. Replace with analogous functions that support length arguments or provides boundary checks such as 'scanf_s' in case of C11[0m
[1m/drone/src/blatt02/fib_lib.c:29:5: [0m[0;1;35mwarning: [0m[1mUndefined or garbage value returned to caller [clang-analyzer-core.uninitialized.UndefReturn][0m
    return cache[n];
[0;1;32m    ^
[0m[1m/drone/src/blatt02/fib_lib.c:16:7: [0m[0;1;30mnote: [0mAssuming 'n' is not equal to 0[0m
  if (n == 0) {
[0;1;32m      ^
[0m[1m/drone/src/blatt02/fib_lib.c:16:3: [0m[0;1;30mnote: [0mTaking false branch[0m
  if (n == 0) {
[0;1;32m  ^
[0m[1m/drone/src/blatt02/fib_lib.c:18:14: [0m[0;1;30mnote: [0mAssuming 'n' is not equal to 1[0m
  } else if (n == 1) {
[0;1;32m             ^
[0m[1m/drone/src/blatt02/fib_lib.c:18:10: [0m[0;1;30mnote: [0mTaking false branch[0m
  } else if (n == 1) {
[0;1;32m         ^
[0m[1m/drone/src/blatt02/fib_lib.c:26:21: [0m[0;1;30mnote: [0mAssuming the condition is false[0m
    for (int i = 2; i < n + 1; i++) {
[0;1;32m                    ^
[0m[1m/drone/src/blatt02/fib_lib.c:26:5: [0m[0;1;30mnote: [0mLoop condition is false. Execution continues on line 29[0m
    for (int i = 2; i < n + 1; i++) {
[0;1;32m    ^
[0m[1m/drone/src/blatt02/fib_lib.c:29:5: [0m[0;1;30mnote: [0mUndefined or garbage value returned to caller[0m
    return cache[n];
[0;1;32m    ^
[0m[1m/drone/src/blatt02/fib_slow.c:7:3: [0m[0;1;35mwarning: [0m[1mCall to function 'scanf' is insecure as it does not provide security checks introduced in the C11 standard. Replace with analogous functions that support length arguments or provides boundary checks such as 'scanf_s' in case of C11 [clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling][0m
  scanf("%d", &n);
[0;1;32m  ^
[0m[1m/drone/src/blatt02/fib_slow.c:7:3: [0m[0;1;30mnote: [0mCall to function 'scanf' is insecure as it does not provide security checks introduced in the C11 standard. Replace with analogous functions that support length arguments or provides boundary checks such as 'scanf_s' in case of C11[0m

```

### check clang-format  🟢 (success)
```bash
+ check_clang_format -r $(cat current_sheet)

```

### check erfahrungen.txt  🟢 (success)
```bash
+ check_erfahrungen $(cat current_sheet)

```
