#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

typedef enum {
    INPUT_NONE,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_SELECT,
    INPUT_BACK
} InputAction;

void init_input();
InputAction get_input_action();

#endif