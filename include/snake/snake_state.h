#if !defined(SNAKE_INCLUDED_SNAKE_STATE)
#define SNAKE_INCLUDED_SNAKE_STATE

enum DIRECTION { NORTH, EAST, SOUTH, WEST };
typedef struct
{
  int* positions;
  int length;
  enum DIRECTION direction;
  // This is pretty lazy
  int quit;
} Snake;

Snake make_snake(const int i_dim);

void destroy_snake(Snake* i_snake);

int next_position(const int current_position,
                  const enum DIRECTION i_dir,
                  const int i_dim);

void move_snake(Snake* i_snake, const int i_dim);

void grow_snake(Snake* i_snake, const int i_dim);

#endif // SNAKE_INCLUDED_SNAKE_STATE
