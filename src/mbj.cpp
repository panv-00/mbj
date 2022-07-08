#include <stdio.h>
#include <unistd.h>

#include "Card.h"
#include "Pile.h"
#include "BJ_screen.h"

// 

void draw_table(Pile table[6])
{
  Card card;
  int tmp;

  clear_screen(BEGIN_TO_END);
  save_position();
  
  for (int i = 0; i < 7; i++)
  {
    tmp = table[i].get_length();
    for (int j = 0; j < tmp; j++)
    {
      card = table[i].read(j);
      draw_card(card, 3 + i*3, 6 + j*4);
    }
    printf("\n");
  }

  move_to(1, 1);
  draw_box(60, 25);

  move_to(2,2);
  printf("Let the game begin...");

  restore_position();

  printf("\nEnd.\n");
}

int main(int argc, char *argv[])
{
//  const int split = DECKS * 5;
  Pile pile;

  // table is an array of Piles
  // table[0] -> Dealer Pile
  // table[1] -> Slot 1 Pile
  // table[2] -> Slot 1 split Pile
  // table[3] -> Slot 2 Pile
  // table[4] -> Slot 2 split Pile
  // table[5] -> Slot 3 Pile
  // table[6] -> Slot 3 split Pile
  Pile table[7];

  pile.populate_full_deck();
//  pile.shuffle();

  // deal two cards for the dealer
  table[0].push(pile.pop());
  table[0].push(pile.pop());

  // deal one card for each slot
  table[1].push(pile.pop());
  table[3].push(pile.pop());
  table[5].push(pile.pop());

  // deal second card for each slot
  table[1].push(pile.pop());
  table[3].push(pile.pop());
  table[5].push(pile.pop());

  draw_table(table);

  return 0;
}
