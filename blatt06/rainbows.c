#include "./ansi_codes.h"
#include "./tui.h"
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {

  char c = '!';
  size_t t = 0;
  char* input_text = "";
  char* fg_colors = "";

  tui_init();

  if (argc > 1) {
    /* First arguement of argc is file name,
     * Second arguement is the input others are
     * simply omitted.
     */
    input_text = argv[1];

    while (1) {
      if (stdin_has_changed()) {
        c = read_from_stdin();
        if (c == 'q')
          break;
      }

      Size2 size = tui_size();

      tui_clear();

      Cell* cell1[strlen(input_text)];

      /* The first for loop defines the number of rows, whereas
       * the second for loop iterates and assigns the appropriate
       * Metadatas to the cell.
       */
      for (int j = 0; j < 3; j++) {
        for (int i = 0; i < strlen(input_text); i++) {
          /* With the help of switch, the color of the text
           * is set for every column.
           * Since the TUI colors does not complete the rainbow
           * colors, there are only six selected. But the main
           * thing important is the functionality!.
           */
          switch (i % 6) {
          case 0:
            fg_colors = FG_RED;
            break;
          case 1:
            fg_colors = FG_YELLOW;
            break;
          case 2:
            fg_colors = FG_GREEN;
            break;
          case 3:
            fg_colors = FG_BLUE;
            break;
          case 4:
            fg_colors = FG_MAGENTA;
            break;
          case 5:
            fg_colors = FG_CYAN;
            break;
          }

          cell1[i] = tui_cell_at(1 + ((t + i + size.x - j) % (size.x)),
                                 (2 - j) + size.y / 2);
          cell1[i]->content = input_text[i];
          cell1[i]->text_color = fg_colors;
          cell1[i]->background_color = BG_BLACK;
        }
      }

      tui_update();

      t += 1;

      usleep(100000);
    }
  } else { /* This will be executed if the user forget to enter string */

    while (1) {
      if (stdin_has_changed()) {
        c = read_from_stdin();
        if (c == 'q')
          break;
      }

      Size2 size = tui_size();

      tui_clear();

      Cell* cell2 = tui_cell_at(1 + ((t + size.x) % (size.x)), size.y / 2);
      cell2->content = c;
      cell2->text_color = FG_RED;
      cell2->background_color = BG_BLACK;

      tui_update();

      t += 1;

      usleep(10000);
    }
  }

  tui_shutdown();

  return 0;
} // end of program
