#include <stdio.h>
#include <stdint.h>

#include "mbj_get_input.h"

char token[MAX_TOKEN_LENGTH];
int token_length;

static uint32_t to_int(const char *s)
{
  uint32_t num = 0;
  uint32_t max_num = 1000000;
  
  if (s[0] == 0) { return 0; }
  
  while (*s != 0 && *s != ' ')
  {
    if (*s < '0' || *s > '9')
    {
      num = 0;
      break; 
    }
    num = 10 * num + (*s - '0');
    if (num >= max_num) { return max_num; }
    s++;
  }

  return num;
}

static char to_char(const char *s)
{
  return s[0];
}

static int is_whitespace(int c)
{
  if (c == ' ' || c == '\t') { return 1; }

  return 0;
}

static void skip_whitespaces()
{
  int c;

  do
  {
    c = getc(stdin);
    if (!is_whitespace(c)) { break; }
  } while (1);

  ungetc(c, stdin);
}

static int get_token()
{
  int c;
  int return_value = 0;

  token[0] = '\0';
  token_length = 0;

  skip_whitespaces();

  while (1)
  {
    if (token_length == MAX_TOKEN_LENGTH)
    {
      return_value = 1;
      break;
    }
    
    c = getc(stdin);

    if (c == '\n')
    {
      token[token_length] = '\0';
      break;
    }

    token[token_length++] = c;
  }

  return return_value;
}

uint32_t mbj_get_num(const char *prompt)
{
  int read;

  printf("%s", prompt);
  read = get_token();

  if (read == 1)
  {
    while (read == 1)
    {
      read = get_token();
    }
    return 0;
  }

  return to_int(token);
}

char mbj_get_char(const char *prompt)
{
  int read;

  printf("%s", prompt);
  read = get_token();

  if (read == 1)
  {
    while (read == 1)
    {
      read = get_token();
    }
    return 0;
  }

  return to_char(token);
}

