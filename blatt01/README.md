# blatt01 (16 / 16.0)



## Feedback

Super!


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
+ git checkout 1c355d43156425a0054a665d3b2ce3386c3e2546 -b master
Already on 'master'

```

### retrieve current sheet  🟢 (success)
```bash
+ export SHEET=$(curl https://courses.inpro.informatik.uni-freiburg.de/2021-SS/c-kurs/active_exercises | head -n 1)
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0100     7  100     7    0     0    120      0 --:--:-- --:--:-- --:--:--   120
+ echo Currently active exercise directory: $SHEET
Currently active exercise directory: blatt01
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -c hello.c -o hello.o
gcc hello.o -o hello
gcc -c bye.c -o bye.o
gcc bye.o -o bye

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0mecho "Everything is ok. There are no tests, yet."
Everything is ok. There are no tests, yet.

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet *.c --
231 warnings generated.
462 warnings generated.

```

### check clang-format  🟢 (success)
```bash
+ check_clang_format -r $(cat current_sheet)

```

### check erfahrungen.txt  🟢 (success)
```bash
+ check_erfahrungen $(cat current_sheet)

```
