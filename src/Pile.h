#ifndef PILE_H
#define PILE_H

#define DECKS 4

class Pile
{
public:
  Pile();
  ~Pile();

  void push(Card card);
  Card pop();
  Card read(int index);
  void populate_full_deck();
  void dump();
  void shuffle();
  int get_length() { return length; };
  int get_value() { return value; };
  int get_allocated_size() { return allocated_size; };
  void set_value(int new_value);
  void refresh_value();

private:
  int length;
  int value;
  int allocated_size;
  Card *deck;
};

#endif
