#include "./event.h"

int main(void) {

  print_event(mouse_click_event(2, 3));
  print_event(key_press_event('x'));
  print_event(mouse_click_event(0, 3));
  print_event(key_press_event(' '));
  print_event(mouse_click_event(-5, 13));
  print_event(key_press_event('Q'));

  return 0;
}
