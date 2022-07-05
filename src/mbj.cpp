#include <stdio.h>
#include <unistd.h>

#include "mbj_Card.h"
#include "mbj_Pile.h"

int main(int argc, char *argv[])
{
  Card a_card;
  Pile pile;

  a_card.set_face_suit('5', 'H');
  pile.push(a_card);
  pile.dump();

  a_card.set_face_suit('6', 'D');
  pile.push(a_card);
  pile.dump();

  a_card.set_face_suit('8', 'S');
  pile.push(a_card);
  pile.dump();

  a_card.set_face_suit('9', 'H');
  pile.push(a_card);
  pile.dump();

  a_card.set_face_suit('Q', 'C');
  pile.push(a_card);
  pile.dump();

  a_card.set_face_suit('A', 'C');
  pile.push(a_card);
  pile.dump();
  
  pile.shuffle();
  pile.dump();

  sleep(1);
  pile.shuffle();
  pile.dump();

  return 0;
}
