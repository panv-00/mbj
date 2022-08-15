#ifndef MBJ_GET_INPUT_H
#define MBJ_GET_INPUT_H

#define MAX_TOKEN_LENGTH 80

class mbj_get_input
{
public:
  mbj_get_input();
  ~mbj_get_input();

  int32_t mbj_get_num(const char *prompt);
  char mbj_get_char(const char *prompt);

private:
  int32_t to_int(const char *s);
  char to_char(const char *s);
  int is_whitespace(int c);
  void skip_whitespaces();
  int get_token();

  char token[MAX_TOKEN_LENGTH];
  int token_length;
};

#endif
