#ifndef MBJ_SCREEN_H
#define MBJ_SCREEN_H

#include "Card.h"

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

void clear_screen(int clear_code);
void clear_line(int clear_code);
void set_color(int color_code);
void move_up(int count);
void move_down(int count);
void move_right(int count);
void move_left(int count);
void move_to(int row, int col);
void save_position();
void restore_position();
void draw_box(int width, int height);
void draw_card(Card card, int row, int col);

#endif /* MBJ_SCREEN_H */
