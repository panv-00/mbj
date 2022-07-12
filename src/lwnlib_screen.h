#ifndef LWNLIB_SCREEN_H
#define LWNLIB_SCREEN_H

#include <stdio.h>

enum color_codes
{
  COLOR_DEFAULT = 0,
  COLOR_BLACK_FG = 30,
  COLOR_RED_FG,
  COLOR_GREEN_FG,
  COLOR_YELLOW_FG,
  COLOR_BLUE_FG,
  COLOR_MAGNETA_FG,
  COLOR_CYAN_FG,
  COLOR_WHITE_FG,
  COLOR_BLACK_BG = 40,
  COLOR_RED_BG,
  COLOR_GREEN_BG,
  COLOR_YELLOW_BG,
  COLOR_BLUE_BG,
  COLOR_MAGNETA_BG,
  COLOR_CYAN_BG,
  COLOR_WHITE_BG
};

enum clear_codes
{
  CURSOR_TO_END,
  CURSOR_TO_BEGIN,
  BEGIN_TO_END
};

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

void draw_line(
    int width,
    const int start_char,
    const int center_char, 
    const int end_char)
{
  printf("%c", start_char);
  for (int i = 0; i < width; i++)
  {
    printf("%c", center_char);
  }
  printf("%c", end_char);
}

void draw_shape(
    int width,
    int height,
    const int top_start_char,
    const int top_center_char,
    const int top_end_char,
    const int mid_start_char,
    const int mid_end_char,
    const int bottom_start_char,
    const int bottom_center_char,
    const int bottom_end_char
    )
{
  save_position();
  
  draw_line(
      width,
      top_start_char,
      top_center_char,
      top_end_char);
  
  restore_position();
  move_down(1);
  
  for (int i = 0; i < height; i++)
  {
    printf("%c", mid_start_char);
    move_right(width);
    printf("%c", mid_end_char);
    move_left(width + 2);
    move_down(1); 
  }

  save_position();

  draw_line(
      width,
      bottom_start_char,
      bottom_center_char,
      bottom_end_char);
  
  restore_position();
  move_down(1);
}

void draw_box(int width, int height)
{
  draw_shape(
      width,
      height,
      '+', '-', '+',
      '|', '|',
      '+','-','+');
}

#endif /* LWNLIB_SCREEN_H */

