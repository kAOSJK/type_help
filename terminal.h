#ifndef TERMINAL_H
#define TERMINAL_H

#include <SDL3/SDL.h>

int app_init_terminal(SDL_Renderer *renderer);
int app_event_terminal(SDL_Event *event);
int app_render_terminal(SDL_Renderer *renderer);
void app_quit_terminal();

#endif
