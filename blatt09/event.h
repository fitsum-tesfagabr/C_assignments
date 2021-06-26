#ifndef EVENT_H
#define EVENT_H

typedef enum Eventtype { MOUSE_EVENT, KEY_EVENT } Eventtype;

struct E {
  Eventtype type;
  union event {
    int mouse_pos[2];
    char key;
  } event;
};

typedef struct E Event;

Event mouse_click_event(int x, int y);
Event key_press_event(char key);

void print_event(Event e);

#endif
