#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Card.h"
#include "Pile.h"

Pile::Pile() : length{0}, value{0}, allocated_size{52 * DECKS}
{
  deck = (Card *)malloc(allocated_size * sizeof(Card));
}

Pile::~Pile() { free(deck); }

void Pile::push(Card card)
{
  int can_diminish = 0;
  int clean_value = 0;

  deck[length++].SetCard(card);

  for (int i = 0; i < length; i++)
  {
    clean_value += read(i).GetValue();
    if (read(i).GetValue() == 11)
    {
      can_diminish++;
    }
  }

  while (can_diminish > 0 && clean_value > 21)
  {
    clean_value -= 10;
    can_diminish--;
  }

  value = clean_value;
}

Card Pile::pop()
{
  Card card = deck[--length];

  if (card.GetValue() == 11)
  {
    value -= 1;
  }

  else
  {
    value -= card.GetValue();
  }

  return card;
}

Card Pile::read(int index) { return deck[index]; }

void Pile::dump()
{
  printf("\n");

  for (int i = 0; i < length; i++)
  {
    deck[i].Dump();
    printf("(%d)", deck[i].GetValue());
  }

  printf("==>%d\n", value);
}

void Pile::populate_full_deck()
{
  Card card;

  for (int i = 0; i < 4 * DECKS; i++)
  {
    for (int j = 0; j < 13; j++)
    {
      card.SetFaceSuit(FACES[j], SUITS[i % 4]);
      push(card);
    }
  }
}

void Pile::shuffle()
{
  short shuffle_array[length];

  srand(time(NULL));

  for (int i = 0; i < length; i++)
  {
    shuffle_array[i] = 1;
  }

  for (int i = 0; i < length / 2; i++)
  {
    int index_1 = i;
    int index_2 = rand() % length;
    Card tmp_card;

    while (shuffle_array[index_1] == 0)
    {
      index_1 = (index_1 + 1) % length;
    }

    while (shuffle_array[index_2] == 0 || index_1 == index_2)
    {
      index_2 = (index_2 + 1) % length;
    }

    tmp_card.SetCard(deck[index_1]);
    deck[index_1].SetCard(deck[index_2]);
    deck[index_2].SetCard(tmp_card);

    shuffle_array[index_1] = 0;
    shuffle_array[index_2] = 0;
  }
}

void Pile::set_value(int new_value) { value = new_value; }
