#include "mbj.h"

mbj::mbj()
{

}

mbj::~mbj()
{

}

void mbj::draw_card(Card card, int row, int col, bool show_card)
{
  move_to(row, col);
  draw_thin_box(2, 1);
  move_to(row + 1, col + 1);
  if (show_card) { card.dump(); }
}

void mbj::draw_table(const char *message, int post_delay)
{
  Card card;
  int tmp;
  bool show_card;

  soft_clear_screen(MAX_ROWS);
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
        show_card = true;
        
        if (!dealer_turn && i == 0 && j == 1)
        {
          show_card = false;
        }
     
        draw_card(card, 5 + i*3, 6 + j*4, show_card);
      
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

void mbj::setup_game()
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

void mbj::draw_welcome_screen(int status, int slot, int post_delay)
{
  soft_clear_screen(MAX_ROWS);
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

int mbj::set_bets()
{
  int32_t temp_bet;
  mbj_get_input mgi;

  for (int i = 1; i <= 3; i++)
  {
    while(1)
    {
      draw_welcome_screen(STATUS_WAITING, i, DELAY_0);
      printf("Slot %d -> ", i);
      temp_bet = mgi.mbj_get_num("Q->Quit, or Enter Your Bet: ");

      if (temp_bet == -1)
      {
        return -1;
      }

      if (temp_bet >= 0 && wallet >= temp_bet)
      {
        slot_bet[2 * (i - 1) + 1] = temp_bet;
        wallet -= temp_bet;
        break;
      }
    }
  }

  return 0;
}

int mbj::analyze_slot(int slot_index)
{
  if (slot_index > 0 && get_slot_bet(slot_index) == 0) 
  {
    return SLOT_BUST; 
  }

  if (table[slot_index].get_value() < 17) { return SLOT_CAN_HIT; }

  if (table[slot_index].get_value() < 21 ||
        (table[slot_index].get_value() == 21 &&
         table[slot_index].get_length() != 2)) { return SLOT_CAN_STAND; }

  if (table[slot_index].get_value() == 21) { return SLOT_BJ; }

  return SLOT_BUST;
}

bool mbj::slots_available()
{
  bool return_value = false;

  for (int i = 1; i < 7; i++)
  {
    if (analyze_slot(i) == SLOT_CAN_HIT || analyze_slot(i) == SLOT_CAN_STAND)
    {
      return_value = true;
      break;
    }
  }

  return return_value;
}

void mbj::play_dealer_slot()
{
  uint32_t earnings;
  mbj_get_input mgi;
  
  dealer_turn = true;
  draw_table("Dealer Turn..", DELAY_1);

  while (slots_available() && analyze_slot(SLOT_0_DEALER) == SLOT_CAN_HIT)
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
  mgi.mbj_get_char(" ..Press Enter to Continue..");
  wallet += earnings;
}

