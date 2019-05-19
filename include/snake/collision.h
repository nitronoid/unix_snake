#if !defined(SNAKE_INCLUDED_COLLISION)
#define SNAKE_INCLUDED_COLLISION

#include "snake/snake_state.h"

int check_snake_collisions(const Snake* i_snake, const int i_pos);

int check_self_collisions(const Snake* i_snake);

int check_food_collisions(const Snake* i_snake, const int food_position);

int check_boundary_collisions(const Snake* i_snake, const int i_dim);

#endif // SNAKE_INCLUDED_COLLISION
