#ifndef TERMINAL_RENDERER_H
#define TERMINAL_RENDERER_H

#define COLS 80
#define ROWS 24
#define PROMPT "apollo13@houston:~$ "
#define PROMPT_LEN 20

int *open_terminal_font();
int init_terminal_renderer(SDL_Renderer *renderer);
int render_terminal(SDL_Renderer *renderer, int window_height);
void quit_terminal_renderer();

#endif
