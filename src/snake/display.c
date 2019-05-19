#include "snake/display.h"
#include "snake/fill.h"
#include <stdio.h>

void init_borders(char* o_display, const int i_dim)
{
  // Initialize the top and bottom borders
  fill_n(o_display, i_dim, '*');
  fill_n(o_display + i_dim * (i_dim - 1), i_dim, '*');
  // Initialize the left and right borders
  fill_n_stride(o_display, i_dim, '*', i_dim);
  fill_n_stride(o_display + i_dim - 1, i_dim, '*', i_dim);
}

void init_display(char* o_display, const int i_dim)
{
  // Initialize everything to blank
  fill_n(o_display, i_dim * i_dim, ' ');
  // Now write the borders
  init_borders(o_display, i_dim);
}

void reset_display(const int i_dim)
{
  // Return to the beginning of the line
  printf("\r");
  for (int i = 0; i < i_dim; ++i)
  {
    // Move up back to the start of our output
    printf("\033[A");
  }
}

void print_display(const char* i_display, const int i_dim)
{
  // Scan-line print, to add a newline after each
  for (int i = 0; i < i_dim; ++i)
  {
    // Print with length provided, it's quicker
    printf("%.*s\n", i_dim, i_display + i * i_dim);
  }
}

void print_end_screen(char* o_display, const int i_dim, const int i_score)
{
  // Reset everything everything to blank
  fill_n(o_display, i_dim * i_dim, ' ');
  print_display(o_display, i_dim);
  reset_display(i_dim);
  printf("Game over!\nYou scored: %d.\n", i_score);
}

void write_snake(const Snake* i_snake,
                 char* o_display,
                 const char c)
{
  // Write out all of the positions
  for (int i = 0; i < i_snake->length; ++i)
  {
    o_display[i_snake->positions[i]] = c;
  }
}
