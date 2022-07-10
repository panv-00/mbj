#ifndef MBJ_H
#define MBJ_H

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "Card.h"
#include "Pile.h"
#include "BJ_screen.h"
#include "mbj_get_input.h"
#include "mbj_format_number.h"

enum Slots
{
  SLOT_0_DEALER = 0,
  SLOT_1_MAIN,
  SLOT_1_SPLIT,
  SLOT_2_MAIN,
  SLOT_2_SPLIT,
  SLOT_3_MAIN,
  SLOT_3_SPLIT
};

enum Delays
{
  DELAY_0 = 0,
  DELAY_1,
  DELAY_2
};

enum Statuses
{
  STATUS_WAITING = 0,
  STATUS_READY
};

Pile pile;
const int split = 77 + DECKS * 5;
uint32_t wallet = 1000;
uint32_t slot_bet[7] = {0};

// table[0] -> Dealer Pile
// table[1] -> Slot 1 Pile
// table[2] -> Slot 1 split Pile
// table[3] -> Slot 2 Pile
// table[4] -> Slot 2 split Pile
// table[5] -> Slot 3 Pile
// table[6] -> Slot 3 split Pile
Pile table[7];

int slot;
int turn;
int dealer_turn;

void draw_table(const char *message, int post_delay);
void setup_game();
void draw_welcome_screen();

#endif /* MBJ_H */
