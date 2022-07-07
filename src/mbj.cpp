#include <stdio.h>
#include <unistd.h>

#include "Card.h"
#include "Pile.h"
#include "BJ_screen.h"

int main(int argc, char *argv[])
{
//  const int split = DECKS * 5;

  Pile pile;
  Card card;
//  pile.push(a_card);
//  pile.dump();


  pile.populate_full_deck();

  clear_screen(BEGIN_TO_END);
  save_position();

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 13; j++)
    {
      card = pile.pop();
      draw_card(card, 3 + i*3, 6 + j*2);
    }
  }

  move_to(1, 1);
  draw_box(60, 15);

  move_to(2,2);
  printf("Let the game begin...");


  restore_position();

  printf("\nEnd.\n");

  return 0;
}
