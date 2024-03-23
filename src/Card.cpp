#include <stdio.h>

#include "Card.h"

Card::Card() {}
Card::~Card() {}

void Card::SetFaceSuit(char f, char s)
{
  face = f;
  suit = s;

  if (f >= '2' && f <= '9')
  {
    value = f - '2' + 2;
  }

  else if (f == 'T' || f == 'J' || f == 'Q' || f == 'K')
  {
    value = 10;
  }

  else if (f == 'A')
  {
    value = 11;
  }

  else
  {
    value = 0;
  }
}

void Card::Dump()
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

void Card::SetCard(Card card) { SetFaceSuit(card.GetFace(), card.GetSuit()); }
