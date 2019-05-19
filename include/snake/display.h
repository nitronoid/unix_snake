#if !defined(SNAKE_INCLUDED_DISPLAY)
#define SNAKE_INCLUDED_DISPLAY

#include "snake/snake_state.h"

void init_borders(char* o_display, const int i_dim);

void init_display(char* o_display, const int i_dim);

void reset_display(const int i_dim);

void print_display(const char* i_display, const int i_dim);

void print_end_screen(char* o_display, const int i_dim, const int i_score);

void write_snake(const Snake* i_snake,
                 char* o_display,
                 const char c);

#endif // SNAKE_INCLUDED_DISPLAY
