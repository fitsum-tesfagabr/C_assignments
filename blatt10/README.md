# blatt10 (18.5 / 16.0)

### Aufgabe 1 - Game of Life



##### (a) `q`: Quit Game

+++

##### (b) living cell `#` and dead cell ` ` with white text / black background.

+++

##### (c) `w,a,s,d`: `gs->cursor_pos`

+++

##### (d) `n`: living cell <-> dead cell

+++

##### (e) ` `: Pause

+++

##### (f) `+`,`-`: `gs->speed`

- extrem kleine Schritte, funktioniert aber

##### (g) `c`: kill all cells

+++

##### (h) `update()`: current state `gs->m_cur` and new state `gs->m_next`  

+++

##### (i) `u,i,o,U,I,O`: save & load 

+++

**Punktzahl: 14/14**

### Aufgabe 2 - Bonus

Das Zeichnen der Auswahl klappt nicht immer, wenn es bei Spalte/Zeile 0 beginnt, aber manchmal auch so bricht es ab. Dementsprechend macht es beim Speichern Probleme.

Das Laden der Files sollte dann eigentlich immer von der Cursor-Position abhängig sein, da man unabhängig von `selection_active` die Auswahl einfügen möchte, denn sonst verkleinert sich das Feld. 

**Punktzahl: 2.5/4**

### Aufgabe 3 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**



### Weiteres Feedback

Schöne Abgabe!

**Punktzahl: -0**

### Anmerkungen

- Wenn du Fragen zur Korrektur hast, kannst du mir gerne einfach
  eine Mail schreiben.
- Fragen zur Vorlesung und zu den Übungen solltest du aber am
  besten ins Forum stellen, damit jeder etwas von der Antwort hat.

Christian: <christian.handschuh@uranus.uni-freiburg.de>+



### clone  🟢 (success)
```bash
Initialized empty Git repository in /drone/src/.git/
+ git fetch origin +refs/heads/master:
From https://git.inpro.informatik.uni-freiburg.de/2021-ss-c-kurs/ft101
 * branch            master     -> FETCH_HEAD
 * [new branch]      master     -> origin/master
+ git checkout 0d25dc54c229075eabe6d24e85d69075cda26c26 -b master
Already on 'master'

```

### retrieve current sheet  🟢 (success)
```bash
+ export SHEET=$(curl https://courses.inpro.informatik.uni-freiburg.de/2021-SS/c-kurs/active_exercises | head -n 1)
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed

  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
100     7  100     7    0     0    118      0 --:--:-- --:--:-- --:--:--   120
+ echo Currently active exercise directory: $SHEET
Currently active exercise directory: blatt10
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -g -Wall -c game_of_life.c -o game_of_life.o
gcc -g -Wall -c game_of_life_lib.c -o game_of_life_lib.o
gcc -g -Wall -c bool_matrix.c -o bool_matrix.o
gcc -g -Wall -c ../tui/tui_matrix.c -o ../tui/tui_matrix.o
gcc -g -Wall -c ../tui/tui_io.c -o ../tui/tui_io.o
gcc -g -Wall -c ../tui/ansi_codes.c -o ../tui/ansi_codes.o
gcc -g -Wall -c ../tui/tui.c -o ../tui/tui.o
gcc -g -Wall game_of_life.o game_of_life_lib.o bool_matrix.o -lm ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o -o game_of_life

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0mecho "Let's Play the Game of Live and Prove if it works correctly!"
Let's Play the Game of Live and Prove if it works correctly!

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet bool_matrix.c game_of_life.c game_of_life_lib.c bool_matrix.h game_of_life_lib.h --
592 warnings generated.
1694 warnings generated.
2798 warnings generated.
2798 warnings generated.
3256 warnings generated.

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
