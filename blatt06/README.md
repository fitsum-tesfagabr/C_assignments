# blatt06 (16 / 16.0)

### Aufgabe 1 - Make friends with ANSI - ansi_example.c

Sieht gut aus!

**Punktzahl: 2/2**

### Aufgabe 2 - Terminal-Matrix - tui_matrix.c, tui_matrix_test.c

##### matrix_new, matrix_free  **(1/1)**

##### matrix_width, matrix_height, matrix_cell_at  **(1/1)**

##### matrix_clear_with, matrix_clear  **(1/1)**

##### matrix_set_str_at  **(1/1)**

##### matrix_resize  **(2/2)**

Irgendein Grenzfall verhält sich falsch, aber ist egal.

##### matrix_print_update  **(2/2)**

Sehr schön! Sehr gute Tests!


**Punktzahl: 8/8**

### Aufgabe 3 - Rainbows! - rainbows.c

Sehr schön!! =)

**Punktzahl: 4/4**

### Aufgabe 4 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**



### Weiteres Feedback

Tut mir leid, dass ich bei dem Blatt die Fehler nicht mehr alle auflösen kann. Mir fehlt schlicht die Zeit dazu. Ich kann euch aber anbieten, dass ihr mir eine Mail schreibt, wenn ihr doch noch ausführlicheres Feedback zu bestimmten Fehlern in eurem Code braucht.





**Punktzahl: -0**

### Anmerkungen

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
+ git checkout f7ed81e1f254cfab2bf7863cf2ab372dabf866cc -b master
Already on 'master'

```

### retrieve current sheet  🟢 (success)
```bash
+ export SHEET=$(curl https://courses.inpro.informatik.uni-freiburg.de/2021-SS/c-kurs/active_exercises | head -n 1)
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed

  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
100     7  100     7    0     0    120      0 --:--:-- --:--:-- --:--:--   120
+ echo Currently active exercise directory: $SHEET
Currently active exercise directory: blatt06
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -g -Wall -c ansi_codes.c -o ansi_codes.o
gcc -g -Wall -c ansi_example.c -o ansi_example.o
gcc -g -Wall ansi_example.o ansi_codes.o -o ansi_example
gcc -g -Wall -c tui_matrix_example.c -o tui_matrix_example.o
gcc -g -Wall -c tui_matrix.c -o tui_matrix.o
gcc -g -Wall tui_matrix_example.o tui_matrix.o ansi_codes.o -o tui_matrix_example
gcc -g -Wall -c tui_example.c -o tui_example.o
gcc -g -Wall -c tui_io.c -o tui_io.o
gcc -g -Wall -c tui.c -o tui.o
gcc -g -Wall tui_example.o tui_matrix.o tui_io.o ansi_codes.o tui.o -o tui_example
gcc -g -Wall -c rainbows.c -o rainbows.o
gcc -g -Wall rainbows.o tui_matrix.o tui_io.o ansi_codes.o tui.o -o rainbows

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0mgcc -g -Wall -c tui_matrix_test.c -o tui_matrix_test.o
gcc  -g -c ../unity/unity.c -o ../unity/unity.o
gcc -g -Wall tui_matrix_test.o tui_matrix.o ansi_codes.o ../unity/unity.o -o tui_matrix_test
./tui_matrix_test
tui_matrix_test.c:228:test_cell_eq:[42mPASS[00m
tui_matrix_test.c:229:test_matrix_new:[42mPASS[00m
tui_matrix_test.c:230:test_matrix_clear_with:[42mPASS[00m
tui_matrix_test.c:231:test_matrix_clear:[42mPASS[00m
tui_matrix_test.c:232:test_matrix_width:[42mPASS[00m
tui_matrix_test.c:233:test_matrix_height:[42mPASS[00m
tui_matrix_test.c:234:test_matrix_cell_at:[42mPASS[00m
tui_matrix_test.c:235:test_matrix_set_str_at:[42mPASS[00m
tui_matrix_test.c:236:test_matrix_resize:[42mPASS[00m

-----------------------
9 Tests 0 Failures 0 Ignored 
[42mOK[00m

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet ansi_codes.c ansi_example.c rainbows.c tui.c tui_example.c tui_io.c tui_matrix.c tui_matrix_example.c tui_matrix_test.c ansi_codes.h tui.h tui_io.h tui_matrix.h --
231 warnings generated.
462 warnings generated.
1275 warnings generated.
1506 warnings generated.
2198 warnings generated.
3262 warnings generated.
3854 warnings generated.
4312 warnings generated.
4746 warnings generated.
4746 warnings generated.
4977 warnings generated.
4977 warnings generated.
4977 warnings generated.

```

### check clang-format  🟢 (success)
```bash
+ check_clang_format -r $(cat current_sheet)

```

### check erfahrungen.txt  🟢 (success)
```bash
+ check_erfahrungen $(cat current_sheet)

```
