# blatt05 (16 / 16.0)

### Aufgabe 1 - Resizable Arrays
- vec_new (1/1.0)
- vec_free (0.5/0.5)
- vec_at (0.5/0.5)
- vec_length + vec_capacity (0.5/0.5)
- vec_push (2/2.0)
- vec_pop (2/2.0)
- vec_print (0.5/0.5)
- vec_min_between (2/2.0)
- vec_sort (1/1.0)

Sehr schön!

**Punktzahl: 10/10**

### Aufgabe 2 - Statistik

Klappt super

**Punktzahl: 4/4**


### Aufgabe 3 - Erfahrungen

Danke für das Feedback :)

Das stimmt. Aber es hat sich gelohnt ;)

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
+ git checkout b312bf05dc9d88c0098bf3c8cb7b7f03cb802f50 -b master
Already on 'master'

```

### retrieve current sheet  🟢 (success)
```bash
+ export SHEET=$(curl https://courses.inpro.informatik.uni-freiburg.de/2021-SS/c-kurs/active_exercises | head -n 1)
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed

  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
100     7  100     7    0     0    120      0 --:--:-- --:--:-- --:--:--   118
+ echo Currently active exercise directory: $SHEET
Currently active exercise directory: blatt05
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc  -g -c vec.c -o vec.o
gcc  -g -c vec_test.c -o vec_test.o
gcc  -g -c ../unity/unity.c -o ../unity/unity.o
gcc  -g vec_test.o vec.o ../unity/unity.o -o vec_test
gcc  -g -c statistics.c -o statistics.o
gcc  -g statistics.o vec.o -o statistics

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0m./vec_test
vec_test.c:209:test_vec_at:[42mPASS[00m
vec_test.c:210:test_vec_lenght:[42mPASS[00m
vec_test.c:211:test_vec_capacity:[42mPASS[00m
vec_test.c:212:test_vec_new:[42mPASS[00m
vec_test.c:213:test_vec_push:[42mPASS[00m
vec_test.c:214:test_vec_pop:[42mPASS[00m
vec_test.c:215:test_vec_swap_int:[42mPASS[00m
vec_test.c:216:test_vec_min_between:[42mPASS[00m
vec_test.c:217:test_vec_sort:[42mPASS[00m

Vector at address 0x55580669d2a0 has 0 elements and capacity 1.

Vector at address 0x55580669d2a0 has 1 elements and capacity 1.
  vec[0] = 0 (address 0x55580669e470)

Vector at address 0x55580669d2a0 has 2 elements and capacity 2.
  vec[0] = -2 (address 0x55580669e470)
  vec[1] = 0 (address 0x55580669e474)

Vector at address 0x55580669d2a0 has 3 elements and capacity 4.
  vec[0] = -4 (address 0x55580669e470)
  vec[1] = -2 (address 0x55580669e474)
  vec[2] = 0 (address 0x55580669e478)

Vector at address 0x55580669d2a0 has 4 elements and capacity 4.
  vec[0] = -6 (address 0x55580669e470)
  vec[1] = -4 (address 0x55580669e474)
  vec[2] = -2 (address 0x55580669e478)
  vec[3] = 0 (address 0x55580669e47c)

Vector at address 0x55580669d2a0 has 5 elements and capacity 8.
  vec[0] = -8 (address 0x55580669e470)
  vec[1] = -6 (address 0x55580669e474)
  vec[2] = -4 (address 0x55580669e478)
  vec[3] = -2 (address 0x55580669e47c)
  vec[4] = 0 (address 0x55580669e480)

Vector at address 0x55580669d2a0 has 4 elements and capacity 4.
  vec[0] = -8 (address 0x55580669e470)
  vec[1] = -6 (address 0x55580669e474)
  vec[2] = -4 (address 0x55580669e478)
  vec[3] = -2 (address 0x55580669e47c)

Vector at address 0x55580669d2a0 has 3 elements and capacity 4.
  vec[0] = -8 (address 0x55580669e470)
  vec[1] = -6 (address 0x55580669e474)
  vec[2] = -4 (address 0x55580669e478)

Vector at address 0x55580669d2a0 has 2 elements and capacity 2.
  vec[0] = -8 (address 0x55580669e470)
  vec[1] = -6 (address 0x55580669e474)

Vector at address 0x55580669d2a0 has 1 elements and capacity 1.
  vec[0] = -8 (address 0x55580669e470)

Vector at address 0x55580669d2a0 has 0 elements and capacity 1.
vec_test.c:218:test_vec_print:[42mPASS[00m

-----------------------
10 Tests 0 Failures 0 Ignored 
[42mOK[00m

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet *.c *.h --
544 warnings generated.
1123 warnings generated.
1437 warnings generated.
1437 warnings generated.

```

### check clang-format  🟢 (success)
```bash
+ check_clang_format -r $(cat current_sheet)

```

### check erfahrungen.txt  🟢 (success)
```bash
+ check_erfahrungen $(cat current_sheet)

```
