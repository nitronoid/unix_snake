#if !defined(SNAKE_INCLUDED_INPUT)
#define SNAKE_INCLUDED_INPUT

#include "snake/snake_state.h"
#include <termios.h>
#include <pthread.h>

struct termios init_term_ios(struct termios* i_old);

void set_term_ios(const struct termios* i_settings);

void* input_loop(void* io_snake_erased);

pthread_t create_input_thread(Snake* io_snake);

void destroy_input_thread(pthread_t* io_thread);

#endif //SNAKE_INCLUDED_INPUT
