# projekt (78 / 80.0)

### Aufgabe 1 - Basic Game

#### Zeichnen des Spielfeldes und Cursor Bewegen - 4P
+++

#### Uncovering mit 'space' - 14P
  - Rekursive Aufdecken der Nachbarfelder (12P)
  - Mine treffen -> game lost (2P)
  
+++

#### Anzahl Minen in der Nachbarschaft sind korrekt - 6P
+++

#### Game over -> Alle felder werden aufgedeckt - 4P
+++

#### Game over -> Spielfeld eingefroren - 2P
+++

#### Erkennung von gewonnenem Spiel - 2P
+++

#### Fahnen - 4P
  - Felder mit Fahnen können nicht mehr aufgedeckt werden (2P)
  - Fahnen werden korrekt gezeichnet mit verschiedenen Farben beim Aufdecken (2P)
  
**<span style="color: red"> [-2P] </span>** Leider werden die Fahnen gelöscht nach Spielende.

#### Spiel wird mit 'q' beendet - 1P
+++

#### Minen werden initial sinnvoll zufällig mit richtiger Wahrscheinlichkeit verteilt - 1P
+++


**Punktzahl: 36/38**


### Aufgabe 2 - Menü & Einstellungen

#### Keybindings werden geprintet - 1P
+++

#### Menü mit Item-Navigation funktioniert - 3P
+++

#### Das Verändern der Einstellungen funktioniert - 3P
+++ Mit sinnvollen Grenznen und korrekten Werden. Grade Wahrscheinlichkeit [0,1] ist richtig und nicht [0,100] ohne "%"

#### Settings werden in Datei gespeichert und geladen (Persistenz)- 8P
+++

#### Settings zeigen im Spiel Effekt und das Spiel läuft mit Einstellungen korrekt (also die Punkte aus Aufgabenteil 1 funktionieren noch korrekt) - 5P
  - Skalieren vom Spielfeld
  - Wahrscheinlichtkeit der Minen
  - Rekursives Aufdecken darf nicht kaputtgehen
  
+++


**Punktzahl: 20/20**

### Aufgabe 3 - Highscores

#### Zeitanzeige - 4P
  - Zeit stoppt nicht bei game over (-1P)
  
+++
#### Highscores werden angezeigt - 2P
+++

#### Sortierung funktionert - 6P
+++

#### Max. 10 Highscores werden angezeigt - 2P
+++

#### Speichern/Laden der Highscores - 6P
+++

**Punktzahl: 20/20**


### Aufgabe 4 - Erfahrungen

Danke für das Feedback :)

**Punktzahl: 2/2**



### Weiteres Feedback

Sehr sehr gute Abgabe! Es läuft super stabil. Es ist stimmig. Sogar mit Highscores. Respekt! =)

**Punktzahl: -0P**

### Anmerkungen

- Wenn du Fragen zur Korrektur hast, kannst du mir gerne einfach
  eine Mail schreiben.

Christian: <christian.handschuh@uranus.uni-freiburg.de>


## Build Log  🟢 (success)
### clone  🟢 (success)
```bash
Initialized empty Git repository in /drone/src/.git/
+ git fetch origin +refs/heads/master:
From https://git.inpro.informatik.uni-freiburg.de/2021-ss-c-kurs/ft101
 * branch            master     -> FETCH_HEAD
 * [new branch]      master     -> origin/master
+ git checkout 16286a724a44bd25982c36305782824a6ef99aec -b master
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
Currently active exercise directory: projekt
+ echo $SHEET > current_sheet

```

### make compile  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make compile
[0mgcc -g -Wall -c mini_sweeper.c -o mini_sweeper.o
gcc  -g -c game_matrix.c -o game_matrix.o
gcc -g -Wall -c mini_sweeper_lib.c -o mini_sweeper_lib.o
gcc -g -Wall -c memtools.c -o memtools.o
gcc -g -Wall -c json_data.c -o json_data.o
gcc -g -Wall -c json_reader.c -o json_reader.o
gcc -g -Wall -c json_printer.c -o json_printer.o
gcc -g -Wall -c reader.c -o reader.o
gcc -g -Wall -c menu.c -o menu.o
gcc -g -Wall -c ../tui/tui_matrix.c -o ../tui/tui_matrix.o
gcc -g -Wall -c ../tui/tui_io.c -o ../tui/tui_io.o
gcc -g -Wall -c ../tui/ansi_codes.c -o ../tui/ansi_codes.o
gcc -g -Wall -c ../tui/tui.c -o ../tui/tui.o
gcc  -g -c vec.c -o vec.o
gcc -g -Wall mini_sweeper.o mini_sweeper_lib.o memtools.o json_data.o json_reader.o json_printer.o reader.o menu.o game_matrix.o ../tui/tui_matrix.o ../tui/tui_io.o ../tui/ansi_codes.o ../tui/tui.o vec.o -o mini_sweeper

```

### make test  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make test
[0mecho "Check if Program runs appropraitely"
Check if Program runs appropraitely

```

### make checkstyle  🟢 (success)
```bash
+ cd $(cat current_sheet)
+ make checkstyle
[0mclang-tidy --quiet game_matrix.c json_data.c json_printer.c json_reader.c memtools.c menu.c mini_sweeper.c mini_sweeper_lib.c reader.c vec.c game_matrix.h json_data.h json_printer.h json_reader.h memtools.h menu.h mini_sweeper_lib.h reader.h vec.h --
592 warnings generated.
1171 warnings generated.
1402 warnings generated.
2009 warnings generated.
2424 warnings generated.
3522 warnings generated.
4621 warnings generated.
5719 warnings generated.
6327 warnings generated.
6906 warnings generated.
7137 warnings generated.
7137 warnings generated.
7368 warnings generated.
7662 warnings generated.
7956 warnings generated.
8535 warnings generated.
9114 warnings generated.
9345 warnings generated.
9345 warnings generated.

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
