#include "snake/snake_state.h"
#include "stdlib.h"

Snake make_snake(const int i_dim)
{
  Snake snake;
  snake.length = 1;
  snake.direction = WEST;
  snake.positions = malloc((i_dim - 1) * (i_dim - 1) * sizeof(int));
  snake.positions[0] = i_dim * (i_dim + 1) / 2;
  snake.quit = 0;
  return snake;
}

void destroy_snake(Snake* i_snake)
{
  free(i_snake->positions);
}

int next_position(const int current_position,
                  const enum DIRECTION i_dir,
                  const int i_dim)
{
  const int horizontal_movement = (i_dir & 1) * -(i_dir - 2);
  const int vertical_movement = ((i_dir + 1) & 1) * (i_dir - 1);
  return current_position + horizontal_movement + vertical_movement * i_dim;
}

void move_snake(Snake* i_snake, const int i_dim)
{
  // Copy all positions back one place in the array, except the head
  for (int i = 0; i < i_snake->length - 1; ++i)
  {
    i_snake->positions[i] = i_snake->positions[i + 1];
  }
  // Grab the position of the snake head
  const int current_position = i_snake->positions[i_snake->length - 1];
  // Write the next position to the back of the positions array
  i_snake->positions[i_snake->length - 1] =
    next_position(current_position, i_snake->direction, i_dim);
}

void grow_snake(Snake* i_snake, const int i_dim)
{
  // Grab the position of the snake head
  const int current_position = i_snake->positions[i_snake->length - 1];
  // Add a new position to the positions array and extend the length by one
  i_snake->positions[i_snake->length++] =
    next_position(current_position, i_snake->direction, i_dim);
}

