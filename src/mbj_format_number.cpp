#include <stdio.h>
#include <stdint.h>

#include "mbj_format_number.h"

void mbj_format(uint32_t number)
{
  char output[10] = {'.','.','.','.','.','.','.','.','0',0};
  int index = -1;

  while (number > 0)
  {
    index++;

    if (index % 3 == 0 && index != 0)
    {
      output[8 - index] = ',';
    }
    else
    {
      output[8 - index] = '0' + number % 10;
      number /= 10;
    }
  }
  
  printf("%s", output);
}

