#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#include "snake/snake_state.h"
#include "snake/input.h"
#include "snake/display.h"
#include "snake/collision.h"


int generate_food_position(const Snake* i_snake, const int i_dim)
{
  // Initialize the food position to the head of the snake
  int food_pos = i_snake->positions[i_snake->length - 1];
  // Regenerate the food position while it is inside the snake
  while (check_snake_collisions(i_snake, food_pos) != -1)
  {
    const int x = (rand() % (i_dim - 2)) + 1;
    const int y = (rand() % (i_dim - 2)) + 1;
    food_pos = x + y * i_dim;
  }
  return food_pos;
}

void write_food(const int i_food,
                char* o_display,
                const int i_dim,
                const char c)
{
  o_display[i_food] = c;
}

int main()
{
  const int dim = 20;
  const int npixels = dim * dim;
  // Allocate a char for every pixel, plus an extra one for the null terminator
  char display_buffer[npixels + 1];
  // Set the final char to a null terminator
  display_buffer[npixels] = '\0';
  // Initialize the rest of the buffer
  init_display(display_buffer, dim);

  // Allow the terminal to take single char input without hitting enter
  struct termios old_settings;
  struct termios new_settings = init_term_ios(&old_settings);
  set_term_ios(&new_settings);

  // Initialize our snake state
  Snake snake = make_snake(dim);

  // Create a separate thread for user input, so we don't block this one
  pthread_t input_thread = create_input_thread(&snake);

  // Two structures for the game update delay
  struct timespec sleep_duration = {0, 300000000};
  struct timespec remaining_duration;

  // Generate an initial food location
  int food = generate_food_position(&snake, dim);
  // Write the initial food location into the display buffer
  write_food(food, display_buffer, dim, 'x');

  int score = 0;
  // Main game loop
  while (!snake.quit)
  {
    // Clear the snake from the display
    write_snake(&snake, display_buffer, dim, ' ');
    // Move the snake one tick
    move_snake(&snake, dim);
    // Check for the snake eating
    if (check_food_collisions(&snake, food))
    {
      // Increment the score
      ++score;
      // Grow the snake
      grow_snake(&snake, dim);
      // Clear the current food location by writing a blank
      write_food(food, display_buffer, dim, ' ');
      // Generate a new position for the food
      food = generate_food_position(&snake, dim);
      // Write the new food location into the display buffer
      write_food(food, display_buffer, dim, 'x');
    }
    // Check whether the snake has hit itself
    snake.quit |= check_self_collisions(&snake);
    // Check whether the snake has hit a wall
    snake.quit |= check_boundary_collisions(&snake, dim);
    // Write the snake to the display
    write_snake(&snake, display_buffer, dim, 'o');
    // Print out the display string
    print_display(display_buffer, dim);
    // Move the start of stdout back to the beginning to overwrite the display
    reset_display(dim);
    // Delay the next update
    nanosleep(&sleep_duration, &remaining_duration);
  }

  // Print out a game over screen with score
  print_end_screen(display_buffer, dim, score);

  // Clean-up the snake memory
  destroy_snake(&snake);
  // Clean up the io thread
  destroy_input_thread(&input_thread);
  // Set the terminal back to the default settings
  set_term_ios(&old_settings);

  return 0;
}

