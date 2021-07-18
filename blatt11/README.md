# blatt11 (16 / 16.0)

### Aufgabe 1 - Higher-Order Functions: `ivec_ext.c`, `ivec_ext_test.c`



##### (a) `ivec_filter`

+++

##### (b) `ivec_fold`, `ivec_sum`, `ivec_product`

+++

**Punktzahl: 4/4**

### Aufgabe 2 - Function Plotter: `plot_lib.c`, `plot.c`

##### `plot`

- Da steht zu viel in der `main()`. In `main()` sollten nur die Parameter stehen, also **was**  geplottet werden soll. Und in `plot()` dann, **wie** es geplottet werden soll.

**Punktzahl: 10/10**

### Aufgabe 3 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**



### Weiteres Feedback

Schön!

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
+ git checkout 00832d6b56cc82decd7d33e34eedaa2f185d4864 -b master
Already on 'master'

```

### retrieve current sheet  🟢 (success)
```bash
+ export SHEET=$(curl https://courses.inpro.informatik.uni-freiburg.de/2021-SS/c-kurs/active_exercises | head -n 1)
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed

  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
100     7  100     7    0     0    112      0 --:--:-- --:--:-- --:--:--   112
+ echo Currently active exercise directory: $SHEET
Currently active exercise directory: blatt11
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -g -Wall -c plot.c -o plot.o
gcc -g -Wall -c plot_lib.c -o plot_lib.o
gcc -g -Wall -c ../tui/tui_matrix.c -o ../tui/tui_matrix.o
gcc -g -Wall -c ../tui/tui_io.c -o ../tui/tui_io.o
gcc -g -Wall -c ../tui/ansi_codes.c -o ../tui/ansi_codes.o
gcc -g -Wall -c ../tui/tui.c -o ../tui/tui.o
gcc -g -Wall plot.o plot_lib.o -lm ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o -o plot

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0mgcc -g -Wall -c ivec_ext_test.c -o ivec_ext_test.o
gcc -g -Wall -c ivec_ext.c -o ivec_ext.o
gcc -g -Wall -c ivec.c -o ivec.o
gcc -g -Wall -c ../unity/unity.c -o ../unity/unity.o
gcc -g -Wall ivec_ext_test.o ivec_ext.o ivec.o ../unity/unity.o -o ivec_ext_test
./ivec_ext_test
ivec_ext_test.c:84:test_int_vec_filter:[42mPASS[00m
ivec_ext_test.c:85:test_ivec_sum:[42mPASS[00m
ivec_ext_test.c:86:test_ivec_product:[42mPASS[00m

-----------------------
3 Tests 0 Failures 0 Ignored 
[42mOK[00m

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet ivec.c ivec_ext.c ivec_ext_test.c plot.c plot_lib.c ivec.h ivec_ext.h plot_lib.h --
579 warnings generated.
886 warnings generated.
1426 warnings generated.
2528 warnings generated.
3630 warnings generated.
3630 warnings generated.
3630 warnings generated.
3630 warnings generated.

```

### check clang-format  🟢 (success)
```bash
+ check_clang_format -r $(cat current_sheet)
NOTE: Check for formatting temporarily disabled, since it tried to eat up all our RAM...

```

### check erfahrungen.txt  🟢 (success)
```bash
+ check_erfahrungen $(cat current_sheet)

```
