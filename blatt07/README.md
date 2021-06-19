# blatt07 (22 / 16.0)

### Aufgabe 1 - Where is my ship?!

#### (a) `draw_ship`
+++
#### (b) `handle_input`
+++

**Punktzahl: 3/3**

### Aufgabe 2 - Fire up those plasma cannons!

#### (a) `handle_input`  `(c == ' ')`
+++
#### (b) `draw_projectiles`
+++
#### (c) `move_projectiles`
+++

**Punktzahl: 4/4**

### Aufgabe 3 - Asteroids everywhere!

#### (a) `spawn_asteroids`
+++
#### (b) `draw_asteroids`
+++
#### (c) `move_asteroids`
+++
#### (d) `bool collides_with_ship(Int2 ship_pos, Int2 pos)`
+++
#### (e) `handle_asteroid_ship_collisions`
+++
#### (f) `handle_projectile_asteroid_collisions`
+++

**Punktzahl: 7/7**


### Aufgabe 4 - Let’s blow some stuff up!

#### (a) `handle_projectile_asteroid_collisions` und `handle_asteroid_ship_collisions`
+++
#### (b) `move_explosions`
+++
#### (c) `draw_explosions`
+++

**Punktzahl: 3/3**


### Aufgabe 5 - Let’s blow some stuff up!

#### (a) `draw_powerups` 
+++
#### (b) `spawn_powerups`
+++
#### (c) `move_powerups`
+++
#### (d) `handle_powerup_ship_collisions`
+++
#### (e) `draw_ship`
+++
#### (f) `handle_input`
+++

**Punktzahl: 3/3**


### Aufgabe 4 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**



### Weiteres Feedback

Sehr sehr schöne Abgabe!!




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
+ git checkout 3f427e4fe17684f15e01e4305a1373c0b9c2bb76 -b master
Already on 'master'

```

### retrieve current sheet  🟢 (success)
```bash
+ export SHEET=$(curl https://courses.inpro.informatik.uni-freiburg.de/2021-SS/c-kurs/active_exercises | head -n 1)
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed

  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
100     7  100     7    0     0    114      0 --:--:-- --:--:-- --:--:--   112
+ echo Currently active exercise directory: $SHEET
Currently active exercise directory: blatt07
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -g -Wall -c game.c -o game.o
gcc -g -Wall -c game_lib.c -o game_lib.o
gcc -g -Wall -c ../tui/tui_matrix.c -o ../tui/tui_matrix.o
gcc -g -Wall -c ../tui/tui_io.c -o ../tui/tui_io.o
gcc -g -Wall -c ../tui/ansi_codes.c -o ../tui/ansi_codes.o
gcc -g -Wall -c ../tui/tui.c -o ../tui/tui.o
gcc  -g -c vec.c -o vec.o
gcc -g -Wall game.o game_lib.o ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o vec.o -o game

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0mgcc -g -Wall -c game_test.c -o game_test.o
gcc  -g -c ../unity/unity.c -o ../unity/unity.o
gcc -g -Wall game_test.o game_lib.o ../tui/tui_matrix.o ../tui/tui.o ../tui/tui_io.o ../tui/ansi_codes.o vec.o ../unity/unity.o -o game_test
./game_test

-----------------------
0 Tests 0 Failures 0 Ignored 
[42mOK[00m

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet game.c game_lib.c game_test.c vec.c game_lib.h vec.h --
978 warnings generated.
1970 warnings generated.
2286 warnings generated.
2865 warnings generated.
3096 warnings generated.
3096 warnings generated.

```

### check clang-format  🟢 (success)
```bash
+ check_clang_format -r $(cat current_sheet)

```

### check erfahrungen.txt  🟢 (success)
```bash
+ check_erfahrungen $(cat current_sheet)

```
