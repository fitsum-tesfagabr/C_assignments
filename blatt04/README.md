# blatt04 (16 / 16.0)

### Aufgabe 1 - Fingerübungen: `structs` und Zeiger

(b) Z.25 kannst du auch wie Z.24 schreiben.

Sehr schön

**Punktzahl: 3/3**

### Aufgabe 2 - Fingerübungen: `malloc` und `free`

So macht korrigieren Spaß =) Wunderbar!

**Punktzahl: 11/11**


### Aufgabe 3 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**



### Weiteres Feedback

#### Makefile



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
+ git checkout f5a77e77f3865fb2407eb9c0edb33c53b4c84501 -b master
Already on 'master'

```

### retrieve current sheet  🟢 (success)
```bash
+ export SHEET=$(curl https://courses.inpro.informatik.uni-freiburg.de/2021-SS/c-kurs/active_exercises | head -n 1)
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed

  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
100     7  100     7    0     0    118      0 --:--:-- --:--:-- --:--:--   118
+ echo Currently active exercise directory: $SHEET
Currently active exercise directory: blatt04
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -c warmup_structs.c -o warmup_structs.o
gcc -c ../unity/unity.c -o ../unity/unity.o
gcc warmup_structs.o ../unity/unity.o -o warmup_structs
gcc -c warmup_malloc.c -o warmup_malloc.o
gcc warmup_malloc.o ../unity/unity.o -o warmup_malloc

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0m./warmup_structs
warmup_structs.c:75:test_add_3_1:[42mPASS[00m
warmup_structs.c:76:test_add_assign_3_1:[42mPASS[00m
warmup_structs.c:77:test_add_point_1:[42mPASS[00m
warmup_structs.c:78:test_add_assign_point_1:[42mPASS[00m
warmup_structs.c:79:test_find_char_1:[42mPASS[00m

-----------------------
5 Tests 0 Failures 0 Ignored 
[42mOK[00m
./warmup_malloc
warmup_malloc.c:297:test_fib_fast_0:[42mPASS[00m
warmup_malloc.c:298:test_fib_fast_1:[42mPASS[00m
warmup_malloc.c:299:test_fib_fast_15:[42mPASS[00m
warmup_malloc.c:301:test_repeat_foo_3_times:[42mPASS[00m
warmup_malloc.c:302:test_repeat_cpp_5_times:[42mPASS[00m
warmup_malloc.c:303:test_join_1:[42mPASS[00m
warmup_malloc.c:304:test_join_2:[42mPASS[00m
warmup_malloc.c:305:test_join_3:[42mPASS[00m
warmup_malloc.c:307:test_join_alternative_1:[42mPASS[00m
warmup_malloc.c:308:test_join_alternative_2:[42mPASS[00m
warmup_malloc.c:309:test_join_alternative_3:[42mPASS[00m
warmup_malloc.c:311:test_find_quoted_1:[42mPASS[00m
warmup_malloc.c:312:test_find_quoted_2:[42mPASS[00m
warmup_malloc.c:313:test_find_quoted_3:[42mPASS[00m

-----------------------
14 Tests 0 Failures 0 Ignored 
[42mOK[00m

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet *.c --
664 warnings generated.
1325 warnings generated.

```

### check clang-format  🟢 (success)
```bash
+ check_clang_format -r $(cat current_sheet)

```

### check erfahrungen.txt  🟢 (success)
```bash
+ check_erfahrungen $(cat current_sheet)

```
