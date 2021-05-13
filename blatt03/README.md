# blatt03 (16 / 16.0)

### Aufgabe 1 - Fingerübungen

Perfekt!

**Punktzahl: 4/4**

### Aufgabe 2 - Ver- und Entschlüsseln von einzelnen Zeichen

sehr schön

**Punktzahl: 4/4**

### Aufgabe 3 - Ver- und Entschlüsseln von Strings

wunderbar

**Punktzahl: 3/3**

### Aufgabe 4 - Das symcrypt-Programm

läuft super

**Punktzahl: 3/3**

### Aufgabe 5 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**



### Weiteres Feedback

#### Makefile

Sieht super aus, bis auf zwei Dinge:

- `compile:` hat nur die file-Bedingungen die am Ende existieren sollen zum Ausführen. Also wirklich nur 
  ```makefile
  compile: warmup symcrypt
  ```
- `symcrypt_lib` brauchst du nicht zu löschen, da es hoffentlich nie existieren wird ;)

**Punktzahl: -0**

### Anmerkungen

- Wenn du Fragen zur Korrektur hast, kannst du mir gerne einfach
  eine Mail schreiben.
- Fragen zur Vorlesung und zu den Übungen solltest du aber am
  besten ins Forum stellen, damit jeder etwas von der Antwort hat.

Christian: <christian.handschuh@uranus.uni-freiburg.de>




You'll find your feedback here, when your submission has been graded.

## Build Log  🟢 (success)
### clone  🟢 (success)
```bash
Initialized empty Git repository in /drone/src/.git/
+ git fetch origin +refs/heads/master:
From https://git.inpro.informatik.uni-freiburg.de/2021-ss-c-kurs/ft101
 * branch            master     -> FETCH_HEAD
 * [new branch]      master     -> origin/master
+ git checkout a879fffe3fad585f68a170d8519844fac8c9e717 -b master
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
Currently active exercise directory: blatt03
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -c warmup.c -o warmup.o
gcc -c symcrypt_lib.c -o symcrypt_lib.o
gcc -c symcrypt_test.c -o symcrypt_test.o
gcc -c ../unity/unity.c -o ../unity/unity.o
gcc -c symcrypt.c -o symcrypt.o
gcc symcrypt.o symcrypt_lib.o -o symcrypt

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0mgcc warmup.o ../unity/unity.o -o warmup
gcc symcrypt_test.o symcrypt_lib.o ../unity/unity.o -o symcrypt_test
./warmup
warmup.c:36:test_my_strlen_1:[42mPASS[00m
warmup.c:37:test_my_strlen_2:[42mPASS[00m
warmup.c:38:test_my_strcmp_1:[42mPASS[00m
warmup.c:39:test_my_strcmp_2:[42mPASS[00m

-----------------------
4 Tests 0 Failures 0 Ignored 
[42mOK[00m
./symcrypt_test
symcrypt_test.c:61:test_encrypt_char_1:[42mPASS[00m
symcrypt_test.c:62:test_encrypt_char_2:[42mPASS[00m
symcrypt_test.c:63:test_encrypt_char_3:[42mPASS[00m
symcrypt_test.c:65:test_decrypt_char_1:[42mPASS[00m
symcrypt_test.c:66:test_decrypt_char_2:[42mPASS[00m
symcrypt_test.c:67:test_decrypt_char_3:[42mPASS[00m
symcrypt_test.c:69:test_encrypt_1:[42mPASS[00m
symcrypt_test.c:70:test_decrypt_1:[42mPASS[00m
symcrypt_test.c:71:test_encrypt_2:[42mPASS[00m
symcrypt_test.c:72:test_decrypt_2:[42mPASS[00m

-----------------------
10 Tests 0 Failures 0 Ignored 
[42mOK[00m

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet *.c *.h --
352 warnings generated.
704 warnings generated.
1139 warnings generated.
1574 warnings generated.
1574 warnings generated.

```

### check clang-format  🟢 (success)
```bash
+ check_clang_format -r $(cat current_sheet)

```

### check erfahrungen.txt  🟢 (success)
```bash
+ check_erfahrungen $(cat current_sheet)

```
