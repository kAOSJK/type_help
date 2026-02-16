#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL3/SDL_stdinc.h>

#include "terminal_row.h"

Row row_input;
Row *rows = NULL;
size_t row_count = 0;

void add_terminal_row_input(char c)
{
    if (row_input.len == MAX_PROMPT_LEN-1)
    {
        return;
    }

    row_input.str[row_input.len] = c;
    row_input.str[row_input.len+1] = '\0';
    row_input.len++;
}

void remove_terminal_row_input()
{
    if (row_input.len == 0)
    {
        return;
    }

    row_input.str[row_input.len-1] = '\0';
    row_input.len--;
}

void reset_terminal_row_input()
{
    row_input.str[0] = '\0';
    row_input.len = 0;
}

const Row *append_terminal_row(const char *str, int has_prompt)
{
    row_count++;
    rows = (Row *)realloc(rows, row_count * (sizeof(Row)));
    if (rows == NULL)
    {
        return NULL;
    }

    Row row;
    row.len = SDL_strlcpy(row.str, str, sizeof(row.str));
    row.has_prompt = has_prompt;

    if (row.len >= sizeof(row.str))
    {
        printf("TH error: newly created Row has too long str entry for some reasons.\n");
    }

    rows[row_count-1] = row;

    return &rows[row_count-1];
}

void clear_terminal_row()
{
    free(rows);
    rows = NULL;
    row_count = 0;
}
