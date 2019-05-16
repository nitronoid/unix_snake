#include "snake/fill.h"

void fill_n_stride(char* o_arr, const int N, const char c, const int step)
{
  for (int i = 0; i < N * step; i += step)
  {
    o_arr[i] = c;
  }
}

void fill_n(char* o_arr, const int N, const char c)
{
  fill_n_stride(o_arr, N, c, 1);
}

