#include <stdio.h>
#include <unistd.h>

#include "Card.h"
#include "Pile.h"
#include "BJ_screen.h"

int main(int argc, char *argv[])
{
  const int split = DECKS * 5;

//  Card a_card;
//  Pile pile;
//  a_card.set_face_suit('5', 'H');
//  pile.push(a_card);
//  pile.dump();

  clear_screen(BEGIN_TO_END);
  move_to(1, 1);
  draw_box(60, 15);

  save_position();
  move_to(2,2);
  printf("Let the game begin...");
  restore_position();

  printf("\nEnd.\n");

  return 0;
}
