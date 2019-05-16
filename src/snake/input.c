#include "snake/input.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct termios init_term_ios(struct termios* i_old)
{
  struct termios new;
  // Make getchar non-blocking
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  tcgetattr(0, i_old);            // grab old terminal i/o settings
  new = *i_old;                   // make new settings same as old settings
  new.c_lflag &= ~ICANON;         // disable buffered i/o
  new.c_lflag &= ~ECHO;           // set echo mode
  tcsetattr(0, TCSANOW, &new);    // apply terminal io settings
  return new;
}

void set_term_ios(const struct termios* i_settings)
{
  tcsetattr(0, TCSANOW, i_settings);
}

void* input_loop(void* io_snake_erased)
{
  // Cast the pthread arg
  Snake* io_snake = (Snake*)io_snake_erased;

  // Input loop
  while (!io_snake->quit)
  {
    // Read the user input
    const char input = getchar();
    switch (input)
    {
    case 'w':
    {
      io_snake->direction = NORTH;
      break;
    }
    case 'a':
    {
      io_snake->direction = WEST;
      break;
    }
    case 's':
    {
      io_snake->direction = SOUTH;
      break;
    }
    case 'd':
    {
      io_snake->direction = EAST;
      break;
    }
    case 'q':
    {
      io_snake->quit = 1;
      break;
    }
    default: break;
    }
  }
  pthread_exit(0);
  printf("Closing io thread\n");
  return NULL;
}

pthread_t create_input_thread(Snake* io_snake)
{
  pthread_t input_thread;
  pthread_create(&input_thread, NULL, input_loop, (void*)io_snake);
  return input_thread;
}

void destroy_input_thread(pthread_t* io_thread)
{
  pthread_join(*io_thread, NULL);
}

