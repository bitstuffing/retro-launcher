#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

typedef enum {
    INPUT_NONE,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_SELECT,
    INPUT_BACK
} InputAction;

void init_input();
InputAction get_input_action();
void update_menu(InputAction action, int *selected_option);

#endif