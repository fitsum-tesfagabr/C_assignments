# blatt09 16 / 16.0)

### Aufgabe 1 - Unions und Enums

+++

**Punktzahl: ?/3**

### Aufgabe 2 - Merging Files to CSV Tables

##### `json_to_highscores`

+++

##### `highscore_to_json`

+++

**Punktzahl: ?/11**

### Aufgabe 3 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**



### Weiteres Feedback

Sehr schhöne Abgabe!

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
+ git checkout b4c34bfa981280254a835f3b3ebc7e2e1efe8f0a -b master
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
Currently active exercise directory: blatt09
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -g -Wall -c game.c -o game.o
gcc -g -Wall -c game_lib.c -o game_lib.o
gcc -g -Wall -c game_highscores.c -o game_highscores.o
gcc -g -Wall -c json_data.c -o json_data.o
gcc -g -Wall -c json_reader.c -o json_reader.o
gcc -g -Wall -c json_printer.c -o json_printer.o
gcc -g -Wall -c memtools.c -o memtools.o
gcc -g -Wall -c reader.c -o reader.o
gcc -g -Wall -g -c vec.c -o vec.o
gcc -g -Wall -c ../tui/tui_matrix.c -o ../tui/tui_matrix.o
gcc -g -Wall -c ../tui/tui_io.c -o ../tui/tui_io.o
gcc -g -Wall -c ../tui/ansi_codes.c -o ../tui/ansi_codes.o
gcc -g -Wall -c ../tui/tui.c -o ../tui/tui.o
gcc -g -Wall game.o game_lib.o game_highscores.o json_data.o json_reader.o json_printer.o memtools.o reader.o vec.o ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o -o game
gcc -g -Wall -c event_example.c -o event_example.o
gcc -g -Wall -c event.c -o event.o
gcc -g -Wall event_example.o event.o -o event_example

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0mgcc -g -Wall -c game_highscores_test.c -o game_highscores_test.o
gcc -g -Wall -g -c ../unity/unity.c -o ../unity/unity.o
gcc -g -Wall game_highscores_test.o game_highscores.o vec.o json_data.o json_reader.o json_printer.o reader.o memtools.o ../unity/unity.o -o game_highscores_test
./game_highscores_test

{
  "name": "foo",
  "points": 112,
  "distance": 308
}
{
  "name": "bar",
  "points": 23232,
  "distance": 190308
}
game_highscores_test.c:153:test_highscore_to_json:[42mPASS[00m

[0;30m[43mJson Data to be converted to Highscores[0m
{
  "0": {
    "name": "bar",
    "points": 65,
    "distance": 308
  },
  "1": {
    "name": "foo",
    "points": 55,
    "distance": 198
  },
  "2": {
    "name": "xxx",
    "points": 23,
    "distance": 1308
  },
  "3": {
    "name": "AAA",
    "points": 22,
    "distance": 1889
  }
}
game_highscores_test.c:154:test_json_to_highscores:[42mPASS[00m

-----------------------
2 Tests 0 Failures 0 Ignored 
[42mOK[00m

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet event.c event_example.c game.c game_highscores.c game_highscores_test.c game_lib.c json_data.c json_printer.c json_reader.c memtools.c reader.c vec.c event.h game_highscores.h game_lib.h json_data.h json_printer.h json_reader.h memtools.h reader.h vec.h --
231 warnings generated.
231 warnings generated.
1329 warnings generated.
1908 warnings generated.
2447 warnings generated.
2919 warnings generated.
3498 warnings generated.
3729 warnings generated.
4336 warnings generated.
4751 warnings generated.
5359 warnings generated.
5938 warnings generated.
5938 warnings generated.
6169 warnings generated.
6400 warnings generated.
6400 warnings generated.
6631 warnings generated.
6925 warnings generated.
7219 warnings generated.
7450 warnings generated.
7450 warnings generated.

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
