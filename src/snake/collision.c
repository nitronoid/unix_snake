#include "snake/collision.h"

/// Finds the position of the snake which intersects i_pos
int check_snake_collisions(const Snake* i_snake, const int i_pos)
{
  for (int i = 0; i < i_snake->length; ++i)
  {
    if (i_snake->positions[i] == i_pos)
      return i;
  }
  return -1;
}

int check_self_collisions(const Snake* i_snake)
{
  // Grab the position of the snake head
  const int head_pos = i_snake->positions[i_snake->length - 1];
  // Check if the head collides with the snake
  int collision_pos = check_snake_collisions(i_snake, head_pos);
  // This will have found at least the head colliding with the head, but if 
  // another position was found, we need to kill the game
  if (collision_pos != i_snake->length - 1)
    return 1;

  return 0;
}

int check_food_collisions(const Snake* i_snake, const int food_position)
{
  const int current_position = i_snake->positions[i_snake->length - 1];
  return current_position == food_position;
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

