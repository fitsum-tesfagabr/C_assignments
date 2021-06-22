# blatt08 (16 / 16.0)

### Aufgabe 1 - Doubly Linked Lists

##### (a) `list_first`, `list_last`, `list_len`, `node_next`, `node_prev` und `node_val` **(0.5)**
+++
##### (b) `list_new` und `list_free` **(1.5)**
+++
##### (c) `list_push_back` und `list_push_front` **(2.5)**
+++
##### (d) `list_pop_back` und `list_pop_front` **(2.5)**
+++

**Punktzahl: 7/7**

### Aufgabe 2 - Merging Files to CSV Tables

##### (a) `open_files`  **(3)**
+++
##### (b) `close_files`  **(0.5)**
+++
##### (c) `merge_columns`  **(3)**
+++

Letzter Zeilenumbruch in einem File sollte das Ende der letzten Zeile darstellen. Nicht den Start einer neuen.

##### (d) `main`  **(0.5)**
+++

**Punktzahl: 7/7**

### Aufgabe 3 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**



### Weiteres Feedback


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
+ git checkout feb9517bcda3b4dc6398a2fde2ef79a0f810d138 -b master
Already on 'master'

```

### retrieve current sheet  🟢 (success)
```bash
+ export SHEET=$(curl https://courses.inpro.informatik.uni-freiburg.de/2021-SS/c-kurs/active_exercises | head -n 1)
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed

  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
100     7  100     7    0     0    116      0 --:--:-- --:--:-- --:--:--   116
+ echo Currently active exercise directory: $SHEET
Currently active exercise directory: blatt08
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -g -Wall -c table.c -o table.o
gcc -g -Wall -c table_lib.c -o table_lib.o
gcc -g -Wall table.o table_lib.o -o table

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0mgcc -g -Wall -c list_test.c -o list_test.o
gcc -g -Wall -c list.c -o list.o
gcc -g -Wall -c ../unity/unity.c -o ../unity/unity.o
gcc -g -Wall list_test.o list.o ../unity/unity.o -o list_test
./list_test
list_test.c:174:test_new_free:[42mPASS[00m
list_test.c:175:test_push_pop_back:[42mPASS[00m
list_test.c:176:test_push_pop_front:[42mPASS[00m

-----------------------
3 Tests 0 Failures 0 Ignored 
[42mOK[00m

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet list.c list_test.c table.c table_lib.c list.h table_lib.h --
579 warnings generated.
892 warnings generated.
1350 warnings generated.
1929 warnings generated.
1929 warnings generated.
2160 warnings generated.

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
