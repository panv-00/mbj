#include <stdio.h>

#include "Card.h"

Card::Card()
{

}

Card::~Card()
{

}

int Card::find(const char arr[], int len, char seek)
{
  for (int i = 0; i < len; ++i)
  {
    if (arr[i] == seek) return i;
  }

  return -1;
}

int Card::face_to_value(char f)
{
  int face_index = find(card_faces, 13, f);

  return card_values[face_index];
}

void Card::set_face_suit(char f, char s)
{
  face = f;
  suit = s;
  value = face_to_value(f);
}

void Card::dump()
{
  printf("%c", face);
  
  switch (suit)
  {
    case 'H':
      printf("♥");
      break;
  
    case 'S':
      printf("♠");
      break;
    
    case 'D':
      printf("♦");
      break;
    
    case 'C':
      printf("♣");
      break;
  }
}

void Card::set_card(Card card)
{
  set_face_suit(card.get_face(), card.get_suit());
}
