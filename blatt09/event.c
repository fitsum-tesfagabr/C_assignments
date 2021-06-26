#include "./event.h"
#include <stdio.h>

Event mouse_click_event(int x, int y) {
  Event mouse_event;
  mouse_event.type = MOUSE_EVENT;
  mouse_event.event.mouse_pos[0] = x;
  mouse_event.event.mouse_pos[1] = y;
  return mouse_event;
}

Event key_press_event(char key) {
  Event key_pressed;
  key_pressed.type = KEY_EVENT;
  key_pressed.event.key = key;
  return key_pressed;
}

void print_event(Event e) {
  switch (e.type) {
  case MOUSE_EVENT:
    printf("Mouse clicked at (%d, %d).\n", e.event.mouse_pos[0],
           e.event.mouse_pos[1]);
    break;
  case KEY_EVENT:
    printf("Key \'%c\' pressed.\n", e.event.key);
  }
}
