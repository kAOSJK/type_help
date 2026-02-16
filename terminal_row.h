#ifndef TERMINAL_ROW_H
#define TERMINAL_ROW_H

#define MAX_CHAR_LEN 80
#define MAX_PROMPT_LEN 60 

struct Row
{
    char str[MAX_CHAR_LEN+1];
    size_t len;
    int has_prompt;
} typedef Row;

extern Row row_input;
extern Row *rows;
extern size_t row_count;

void add_terminal_row_input(char c);
void remove_terminal_row_input();
void reset_terminal_row_input();
const Row *append_terminal_row(const char *str, int has_prompt);
void clear_terminal_row();

#endif
