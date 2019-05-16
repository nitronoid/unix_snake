#include "snake/collision.h"

int check_self_collisions(const Snake* i_snake)
{
  // Grab the position of the snake head
  const int current_position = i_snake->positions[i_snake->length - 1];

  for (int i = 0; i < i_snake->length - 1; ++i)
  {
    if (i_snake->positions[i] == current_position)
      return 1;
  }
  return 0;
}

int check_food_collisions(const Snake* i_snake, const int food_position)
{
  for (int i = 0; i < i_snake->length; ++i)
  {
    if (i_snake->positions[i] == food_position)
      return 1;
  }
  return 0;
}

int check_boundary_collisions(const Snake* i_snake, const int i_dim)
{
  // Grab the position of the snake head
  const int current_position = i_snake->positions[i_snake->length - 1];
  // Get the x and y positions
  const int x = current_position % i_dim;
  const int y = current_position / i_dim;
  // If we're on a boundary return 1
  return (x == 0 || x == (i_dim - 1)) || (y == 0 || y == (i_dim - 1));
}

