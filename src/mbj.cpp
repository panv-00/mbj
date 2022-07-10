#include "mbj.h"

#define BOX_WIDTH 63
#define BOX_HEIGHT 24

void draw_table(const char *message, int post_delay)
{
  Card card;
  int tmp;

  clear_screen(BEGIN_TO_END);
  save_position();
  
  for (int i = 0; i < 7; i++)
  {
    if (i == 0 || slot_bet[i] > 0)
    {
      tmp = table[i].get_length();

      if (i != 0 && table[i].get_value() == 21)
      {
        set_color(COLOR_GREEN_FG);
      }
      
      if (i == 0 && dealer_turn && table[i].get_value() == 21)
      {
        set_color(COLOR_GREEN_FG);
      }
      
      if (table[i].get_value() > 21) { set_color(COLOR_RED_FG); }

      if (i == slot) { set_color(COLOR_BLUE_FG); }

      for (int j = 0; j < tmp; j++)
      {
        card = table[i].read(j);
        
        if (!dealer_turn && i == 0 && j == 1)
        {
          move_to(5, 10);
          draw_box(2,1);
        }
        else
        {
          draw_card(card, 5 + i*3, 6 + j*4);
        }
      
        if (i != 0 || dealer_turn == 1)
        {
          move_up(1);
          printf("\n  %2d", table[i].get_value());
         
          if (i != 0)
          {
            move_right(BOX_WIDTH - 17);
            printf("Bet:");
            mbj_format(slot_bet[i]);
          }
        }
      }
    
      set_color(COLOR_DEFAULT);

      printf("\n");
    }
  }

  move_to(2, 2);
  set_color(COLOR_WHITE_BG);
  set_color(COLOR_BLACK_FG);
  printf("Round:%4d    Wallet:", turn);
  mbj_format(wallet);
  printf("     Bets:");
  mbj_format(slot_bet[1] + slot_bet[2] + slot_bet[3] + slot_bet[4] + slot_bet[5] + slot_bet[6]);
  if (pile.get_length() <= split) { set_color(COLOR_RED_FG); }
  printf("    Cards:%4d", pile.get_length());
  set_color(COLOR_DEFAULT);

  move_to(3, 2);
  printf("%s", message);

  move_to(1, 1);
  draw_box(BOX_WIDTH, BOX_HEIGHT);

  restore_position();

  printf("\n> \n");
  sleep(post_delay);
}

void setup_game()
{
  // deal a cards for the dealer
  table[0].push(pile.pop());
  draw_table("Dealing a Card for the Dealer.", DELAY_1);

  // deal one card for each slot
  for (int i = 1; i <= 3; i++)
  {
    if (slot_bet[2 * (i - 1) + 1] > 0)
    {
      table[2 * (i - 1) + 1].push(pile.pop());
      draw_table("Dealing for Slots", DELAY_1);
    }
  }

  // deal a cards for the dealer
  table[0].push(pile.pop());
  draw_table("Dealing a Card for the Dealer.", DELAY_1);

  // deal second card for each slot
  for (int i = 1; i <= 3; i++)
  {
    if (slot_bet[2 * (i - 1) + 1] > 0)
    {
      table[2 * (i - 1) + 1].push(pile.pop());
      draw_table("Dealing for Slots", DELAY_1);
    }
  }
}

void draw_welcome_screen(int status, int slot, int post_delay)
{
  clear_screen(BEGIN_TO_END);
  save_position();
 
  move_to(2, 2);
  printf("Welcome to my BlackJack. A game of Passion!");

  move_to(4, 2);
  printf("You have in your Wallet: ");
  mbj_format(wallet);

  for (int i = 1; i <= 3; i++)
  {
    move_to(4 + i, 5);

    if (i == slot) { set_color(COLOR_BLUE_FG); }

    printf("Slot %d bet: ", i);
    mbj_format(slot_bet[2 * (i - 1) + 1]);

    if (i == slot) { set_color(COLOR_DEFAULT); }
  }

  if(status == STATUS_READY)
  {
    move_to(10, 2);
    printf("Setting the table!");
  }

  move_to(1, 1);
  draw_box(BOX_WIDTH, BOX_HEIGHT);

  restore_position();

  printf("\n> \n");
  sleep(post_delay);
}

int main(int argc, char *argv[])
{
  uint32_t temp_bet;
  uint32_t earnings;
  int allow_double;
  int allow_split;
  int allow_surrender;
  char slot_action;

  // play forever
  while (1)
  {
    while (pile.get_length() > 0) { pile.pop(); }
    pile.populate_full_deck();
    pile.shuffle();
    turn = 0;

    // while there is cards in the shoe before split.
    while (1)
    {
      slot = 7;

      for (int i = 1; i <= 3; i++)
      {
        while(1)
        {
          draw_welcome_screen(STATUS_WAITING, i, DELAY_0);
          printf("Slot %d -> ", i);
          temp_bet = mbj_get_num("Enter Your Bet: ");

          if (temp_bet >= 0 && wallet >= temp_bet)
          {
            slot_bet[2 * (i - 1) + 1] = temp_bet;
            wallet -= temp_bet;
            break;
          }
        }
      }

      draw_welcome_screen(STATUS_READY, SLOT_0_DEALER, DELAY_2);

      dealer_turn = 0;
      turn++;
      setup_game();

      slot = 1;

      while (1)
      {
        allow_double = 0;
        allow_split = 0;
        allow_surrender = 0;

        if (slot % 2 == 0 && table[slot].get_length() == 1)
        {
          table[slot].push(pile.pop());
        }

        while (table[slot].get_value() >= 21 && slot != 7) { slot++; }

        while (slot_bet[slot] == 0 && slot != 7) { slot++; }

        if (slot == 7) { break; }

        draw_table("Waiting for Action..", DELAY_0);
        printf("[ H->Hit S->Stand ");

        if (table[slot].get_length() == 2)
        {
          allow_surrender = 1;

          if (wallet >= slot_bet[slot]) { allow_double = 1; }
        }

        if (allow_surrender) { printf("R->suRrender "); }

        if (allow_double) { printf("D->Double "); }

        if (slot % 2 == 1 &&
            table[slot + 1].get_length() == 0 &&
            table[slot].get_length() == 2 &&
            wallet >= slot_bet[slot] &&
            table[slot].read(0).get_value() == table[slot].read(1).get_value())
        {
          allow_split = 1;
        }

        if (allow_split) { printf("T->spliT "); }

        slot_action = mbj_get_char("] : ");

        switch(slot_action)
        {
          case 'h':
          case 'H':
            table[slot].push(pile.pop());
            break;

          case 's':
          case 'S':
            slot++;
            break;

          case 'r':
          case 'R':
            if (allow_surrender)
            {
              wallet += slot_bet[slot] / 2;
              slot_bet[slot] = 0;
              slot++;
            }
            break;

          case 'd':
          case 'D':
            if (allow_double)
            {
              wallet -= slot_bet[slot];
              slot_bet[slot] *= 2;
              table[slot].push(pile.pop());
              slot++;
            }
            break;

          case 't':
          case 'T':
            if (allow_split && wallet >= slot_bet[slot])
            {
              table[slot + 1].push(table[slot].pop());
              slot_bet[slot + 1] = slot_bet[slot];
              wallet -= slot_bet[slot];
              table[slot].push(pile.pop());

              if (table[slot].read(0).get_face() == 'A')
              {
                slot++;
              }
            }
            break;
        }
      }

      dealer_turn = 1;

      while (table[0].get_value() < 17)
      {
        table[0].push(pile.pop());
        draw_table("Dealer Turn..", DELAY_1);
      }
      draw_table("TADA..", DELAY_1);

      earnings = 0;

      if (table[0].get_value() > 21)
      {
        for (int i = 1; i < 7; i++)
        {
          if (table[i].get_value() < 21)
          {
            earnings += slot_bet[i] * 2;
          }
          else if (table[i].get_value() == 21)
          {
            if (table[i].get_length() == 2)
            {
              earnings += slot_bet[i] * 25 / 10;
            }
            else
            {
              earnings += slot_bet[i] * 2;
            }
          }
        }
      }
      else if (table[0].get_value() == 21 && table[0].get_length() == 2)
      {
        for (int i = 1; i < 7; i++)
        {
          if (table[i].get_value() == 21 && table[i].get_length() == 2)
          {
            earnings += slot_bet[i];
          }
        }
      }
      else if (table[0].get_value() == 21)
      {
        for (int i = 1; i < 7; i++)
        {
          if (table[i].get_value() == 21 && table[i].get_length() == 2)
          {
            earnings += slot_bet[i] * 25 / 10;
          }
          else if (table[i].get_value() == 21)
          {
            earnings += slot_bet[i];
          }
        }
      }
      else
      {
        for (int i = 1; i < 7; i++)
        {
          if (table[i].get_value() == 21 && table[i].get_length() == 2)
          {
            earnings += slot_bet[i] * 25 / 10;
          }
          else if (table[i].get_value() <= 21 &&
              table[i].get_value() > table[0].get_value())
          {
            earnings += slot_bet[i] * 2;
          }
          else if (table[i].get_value() <= 21 &&
              table[i].get_value() == table[0].get_value())
          {
            earnings += slot_bet[i];
          }
        }
      }
      printf("Round Summary (CASH) ");
      mbj_format(earnings);
      mbj_get_char(" ..Press Enter to Continue..");
      wallet += earnings;

      for (int i = 0; i < 7; i++)
      {
        while (table[i].get_length() > 0)
        {
          table[i].pop();
        }
        table[i].set_value(0);
        slot_bet[i] = 0;
      }

      if (wallet == 0)
      {
        printf("You are bankrupt.. :(\n");
        return 0;
      }

      if (wallet >= 1000000)
      {
        printf("The Casino in bankrupt.. :)\n");
        return 0;
      }

      if (pile.get_length() <= split) { break; }
    }
  }
  return 0;
}
