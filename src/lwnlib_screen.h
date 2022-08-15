#ifndef LWNLIB_SCREEN_H
#define LWNLIB_SCREEN_H

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

void save_position();
void restore_position();
void clear_screen(int code);
void clear_line(int code);
void set_color(int color);
void move_up(int count);
void move_down(int count);
void move_right(int count);
void move_left(int count);
void move_to(int r, int c);

void draw_line(
    int width,
    const int start_char,
    const int center_char, 
    const int end_char
    );

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
    );

void draw_box(int width, int height);

#endif

