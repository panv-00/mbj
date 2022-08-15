#ifndef MBJ_H
#define MBJ_H

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "Card.h"
#include "Pile.h"
#include "lwnlib_screen.h"
#include "mbj_get_input.h"
#include "mbj_format_number.h"

#define BOX_WIDTH 63
#define BOX_HEIGHT 24


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

enum SlotStatus
{
  SLOT_BUST = -1,
  SLOT_CAN_HIT,
  SLOT_BJ,
  SLOT_CAN_STAND
};

class mbj
{
public:
  mbj();
  ~mbj();

  void draw_card(Card card, int row, int col, bool show_card);
  void draw_table(const char *message, int post_delay);
  void setup_game();
  void draw_welcome_screen(int status, int slot, int post_delay);
  int set_bets();
  int analyze_dealer_hand();
  int analyze_slot(int slot_index);
  bool slots_available();
  void play_dealer_slot();

  int get_pile_length() { return pile.get_length(); }
  Card pop_pile() { return pile.pop(); }
  void populate_full_deck() { pile.populate_full_deck(); }
  void shuffle_pile() { pile.shuffle(); }

  int get_table_length(int s) { return table[s].get_length(); }
  void deal_to_table(int s) { table[s].push(pile.pop()); }
  void deal_table_to_table(int s1, int s2) { table[s2].push(table[s1].pop()); }
  void set_table_value(int s, int value) { table[s].set_value(value); }
  int get_table_value(int s) { return table[s].get_value(); }
  Card read_from_table(int s, int index) { return table[s].read(index); }
  void clear_table(int s)
  {
    while (table[s].get_length() > 0)
    {
      table[s].pop();
    } 
  }

  int get_split() { return split; }
 
  void set_wallet(int32_t value) { wallet = value; }
  int32_t get_wallet() { return wallet; }
  void increment_wallet(int32_t value) { wallet += value; }
  void decrement_wallet(int32_t value) { wallet -= value; }

  int32_t get_slot_bet(int s) { return slot_bet[s]; }
  void set_slot_bet(int s, int32_t bet) { slot_bet[s] = bet; }

  void set_slot(int s) { slot = s; }
  int get_slot() { return slot; }
  bool slot_is_even() { return slot % 2 == 0; }
  void increment_slot() { slot++; }

  void set_turn(int t) { turn = t; }
  void increment_turn() { turn++; }
  int get_turn() { return turn; }

  void set_dealer_turn (bool turn) { dealer_turn = turn; }
  bool get_dealer_turn() { return dealer_turn; }

private:
  Pile pile;
  Pile table[7];
  const int split = 77 + DECKS * 5;
  int32_t wallet = 1000;
  int32_t slot_bet[7] = {0};
  int slot;
  int turn;
  bool dealer_turn;

};

#endif
