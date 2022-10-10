#ifndef LWNLIB_SCREEN_H
#define LWNLIB_SCREEN_H

#include "lwnlib_screen.h"
#include <stdio.h>

void save_position()        { printf("\x1b%d", 7);         }
void restore_position()     { printf("\x1b%d", 8);         }
void clear_screen(int code) { printf("\x1b[%dJ", code);    }
void clear_line(int code)   { printf("\x1b[%dK", code);    }
void set_color(int color)   { printf("\x1b[%dm", color);   }
void move_up(int count)     { printf("\x1b[%dA", count);   }
void move_down(int count)   { printf("\x1b[%dB", count);   }
void move_right(int count)  { printf("\x1b[%dC", count);   }
void move_left(int count)   { printf("\x1b[%dD", count);   }
void move_to(int r, int c)  { printf("\x1b[%d;%df", r, c); }

void soft_clear_screen(int max_row)
{
  for (int i = 1; i <= max_row; i++)
  {
    move_to(i, 1);
    clear_line(2);
  }
  
  move_to(1, 1);
}

void draw_thin_box(int width, int height)
{
  save_position();

  printf("╭");
  for (int i = 0; i < width; i++) { printf("─"); }
  printf("╮");

  restore_position();
  move_down(1);
  
  for (int i = 0; i < height; i++)
  {
    printf("│");
    move_right(width);
    printf("│");
    move_left(width + 2);
    move_down(1); 
  }

  save_position();

  printf("╰");
  for (int i = 0; i < width; i++) { printf("─"); }
  printf("╯");

  restore_position();
  move_down(1);
}

void draw_box(int width, int height)
{
  save_position();

  printf("┏");
  for (int i = 0; i < width; i++) { printf("━"); }
  printf("┓");

  restore_position();
  move_down(1);
  
  for (int i = 0; i < height; i++)
  {
    printf("┃");
    move_right(width);
    printf("┃");
    move_left(width + 2);
    move_down(1); 
  }

  save_position();

  printf("┗");
  for (int i = 0; i < width; i++) { printf("━"); }
  printf("┛");

  restore_position();
  move_down(1);
}

#endif

