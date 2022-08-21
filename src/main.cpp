#include "mbj.h"
#include "FileReaderWriter.h"

int32_t read_wallet_from_file()
{
  int c;
  int mult = 1;
  int32_t num = 0;
  FileReaderWriter frw;

  if (frw.open(".score", "rb"))
  {
    while (true)
    {
      c = frw.read_byte();
      
      if (c == EOF) { break; }
      
      num = num + mult * (c);
      mult *= 10;
    }

    frw.close();
  }

  return num;
}

void save_wallet_to_file(int32_t wallet)
{
  int32_t num;
  FileReaderWriter frw;

  if (frw.open(".score", "wb"))
  {
    while (wallet > 0)
    {
      num = wallet % 10;
      wallet /= 10;
      frw.write_byte(num);
    }

    frw.close();
    printf("[ SUCCESS ] - Wallet saved to disc!\n");
  }

  else
  {
    printf("[ WARNING ] - Could not open file to save your wallet!\n");
  }
}

int main(int argc, char *argv[])
{
  mbj MBJ;
  mbj_get_input mgi;

  bool allow_double;
  bool allow_split;
  bool allow_surrender;
  char slot_action;

  clear_screen(BEGIN_TO_END);

  int32_t old_wallet = read_wallet_from_file();

  if (old_wallet != 0) { MBJ.set_wallet(old_wallet); }

  // play forever
  while (true)
  {
    while (MBJ.get_pile_length() > 0) { MBJ.pop_pile(); }
    MBJ.populate_full_deck();
    MBJ.shuffle_pile();
    MBJ.set_turn(0);

    // while there is cards in the shoe before split.
    while (true)
    {
      MBJ.set_slot(7);

      if (MBJ.set_bets() == -1)
      {
        printf("\nLeaving so soon?\n");

        // try to save wallet to file
        save_wallet_to_file(MBJ.get_wallet());
        return 0;
      }

      MBJ.draw_welcome_screen(STATUS_READY, SLOT_0_DEALER, DELAY_2);
      MBJ.set_dealer_turn(false);
      MBJ.increment_turn();
      MBJ.setup_game();

      MBJ.set_slot(1);

      while (1)
      {
        allow_double = false;
        allow_split = false;
        allow_surrender = false;

        if (MBJ.slot_is_even() && MBJ.get_table_length(MBJ.get_slot()) == 1)
        {
          MBJ.deal_to_table(MBJ.get_slot());
        }

        while ((MBJ.get_table_value(MBJ.get_slot()) >= 21 || MBJ.get_slot_bet(MBJ.get_slot()) == 0) &&
            MBJ.get_slot() != 7)
        {
          MBJ.increment_slot();
        }

        if (MBJ.get_slot() == 7) { break; }

        MBJ.draw_table("Waiting for Action..", DELAY_0);
        printf("[ Q->Quit H->Hit S->Stand ");

        if (MBJ.get_table_length(MBJ.get_slot()) == 2)
        {
          allow_surrender = true;

          if (MBJ.get_wallet() >= MBJ.get_slot_bet(MBJ.get_slot())) { allow_double = true; }
        }

        if (allow_surrender) { printf("R->suRrender "); }

        if (allow_double) { printf("D->Double "); }

        if (!MBJ.slot_is_even() &&
            MBJ.get_table_length(MBJ.get_slot() + 1) == 0 &&
            MBJ.get_table_length(MBJ.get_slot()) == 2 &&
            MBJ.get_wallet() >= MBJ.get_slot_bet(MBJ.get_slot()) &&
            MBJ.read_from_table(MBJ.get_slot(), 0).get_value() == MBJ.read_from_table(MBJ.get_slot(), 1).get_value())
        {
          allow_split = true;
        }

        if (allow_split) { printf("T->spliT "); }

        slot_action = mgi.mbj_get_char("] : ");

        switch(slot_action)
        {
          case 'q':
          case 'Q':
            printf("\nLeaving so soon?\n");
            // try to save wallet to file
            save_wallet_to_file(MBJ.get_wallet());
            return 0;
            
          case 'h':
          case 'H':
            MBJ.deal_to_table(MBJ.get_slot());
            break;

          case 's':
          case 'S':
            MBJ.increment_slot();
            break;

          case 'r':
          case 'R':
            if (allow_surrender)
            {
              MBJ.increment_wallet(MBJ.get_slot_bet(MBJ.get_slot()) / 2);
              MBJ.set_slot_bet(MBJ.get_slot(), 0);
              MBJ.increment_slot();
            }
            break;

          case 'd':
          case 'D':
            if (allow_double)
            {
              MBJ.decrement_wallet(MBJ.get_slot_bet(MBJ.get_slot()));
              MBJ.set_slot_bet(
                  MBJ.get_slot(),
                  2 * MBJ.get_slot_bet(MBJ.get_slot()));
              MBJ.deal_to_table(MBJ.get_slot());
              MBJ.increment_slot();
            }
            break;

          case 't':
          case 'T':
            if (allow_split)
            {
              MBJ.deal_table_to_table(MBJ.get_slot(), MBJ.get_slot() + 1);
              MBJ.set_slot_bet(MBJ.get_slot() + 1, MBJ.get_slot_bet(MBJ.get_slot()));
              MBJ.decrement_wallet(MBJ.get_slot_bet(MBJ.get_slot()));
              MBJ.deal_to_table(MBJ.get_slot());

              if (MBJ.read_from_table(MBJ.get_slot(), 0).get_face() == 'A')
              {
                MBJ.increment_slot();
              }
            }
            break;
        }
      }

      if (MBJ.slots_available()) { MBJ.play_dealer_slot(); }

      for (int i = 0; i < 7; i++)
      {
        MBJ.clear_table(i);
        MBJ.set_table_value(i, 0);
        MBJ.set_slot_bet(i, 0);
      }

      if (MBJ.get_wallet() == 0)
      {
        printf("You are bankrupt.. :(\n");
        save_wallet_to_file(1000);
        
        return 0;
      }

      if (MBJ.get_wallet() >= 1000000)
      {
        printf("The Casino in bankrupt.. :)\n");
        save_wallet_to_file(1000);

        return 0;
      }

      if (MBJ.get_pile_length() <= MBJ.get_split()) { break; }
    }
  }
  return 0;
}

