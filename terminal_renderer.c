#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

#include "terminal_renderer.h"
#include "terminal_row.h"

#define LINE_HEIGHT 20 

char font_name[] = "./src/DejaVuSansMono.ttf";
TTF_Font *font = NULL;
TTF_TextEngine *engine = NULL;
TTF_Text *text = NULL;
int font_height = 0;
int font_width = 0;

int *open_terminal_font()
{
    const float ptsize = 12.0f;

    if (!TTF_Init())
    {
        SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
        return NULL;
    }

    font = TTF_OpenFont(font_name, ptsize);
    if (font == NULL)
    {
        SDL_Log("Couln't load %g pt font from %s: %s", ptsize, font_name, SDL_GetError());
        return NULL;
    }

    TTF_SetFontHinting(font, TTF_HINTING_NORMAL);
    
    SDL_DisplayID display_id = SDL_GetPrimaryDisplay();
    float scale = SDL_GetDisplayContentScale(display_id);
    
    int screen_dpi = (int)(96.0f * scale);
    TTF_SetFontSizeDPI(font, ptsize, screen_dpi, screen_dpi);

    int *wh = (int *)malloc(sizeof(int)*2);

    TTF_GetStringSize(font, "$", 1, &font_width, &font_height);
    
    *(wh) = COLS*font_width;
    *(wh+1) = (ROWS+1)*TTF_GetFontLineSkip(font);

    return wh;
}

int init_terminal_renderer(SDL_Renderer *renderer)
{
    engine = TTF_CreateRendererTextEngine(renderer);
    if (engine == NULL)
    {
        SDL_Log("Couldn't create renderer text engine: %s", SDL_GetError()); 
        return 1;
    }

    text = TTF_CreateText(engine, font, font_name, 0); 
    if (text == NULL)
    {
        SDL_Log("Couldn't create text: %s", SDL_GetError());
        return 1;
    }

    return 0;
}

int render_terminal(SDL_Renderer *renderer, int window_height)
{
    int prompt_width = font_width * PROMPT_LEN;

    Row *begin = NULL;
    if (row_count > ROWS)
    {
        begin = rows + row_count - ROWS + 1;
    }
    else
    {
        begin = rows;
    }

    Row *end = rows + row_count;
    Row *iter = begin;
    int i = 0;

    while (iter < end)
    {
        int x_position = 0;
        if ((*iter).has_prompt == 0)
        {
            TTF_SetTextColor(text, 0, 255, 0, SDL_ALPHA_OPAQUE);
            TTF_SetTextString(text, PROMPT, 0);
            TTF_DrawRendererText(text, 0, LINE_HEIGHT*i);

            x_position = prompt_width;
        }

        TTF_SetTextColor(text, 255, 255, 255, SDL_ALPHA_OPAQUE);
        TTF_SetTextString(text, (*iter).str, 0);
        TTF_DrawRendererText(text, x_position, LINE_HEIGHT*i);

        i++;
        iter++;
    }

    TTF_SetTextColor(text, 0, 255, 0, SDL_ALPHA_OPAQUE);
    TTF_SetTextString(text, PROMPT, 0);
    TTF_DrawRendererText(text, 0, LINE_HEIGHT*i);

    TTF_SetTextColor(text, 255, 255, 255, SDL_ALPHA_OPAQUE);
    TTF_SetTextString(text, row_input.str, 0);
    TTF_DrawRendererText(text, font_width*PROMPT_LEN, LINE_HEIGHT*i);

    SDL_FRect rect;
    rect.x = (font_width * row_input.len)+prompt_width;
    rect.y = LINE_HEIGHT*i;
    rect.w = font_width;
    rect.h = font_height;
    SDL_RenderFillRect(renderer, &rect);

    return 0;
}

void quit_terminal_renderer()
{
    if (text != NULL)
    {
        TTF_DestroyText(text);
    }

    if (engine != NULL)
    {
        TTF_DestroyRendererTextEngine(engine);
    }

    if (font != NULL)
    {
        TTF_CloseFont(font);
    }

    TTF_Quit();
}
