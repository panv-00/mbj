#ifndef PILE_H
#define PILE_H

#define DECKS 2

class Pile
{
public:
  Pile();
  ~Pile();

  void push(Card card);
  Card pop();
  void populate_full_deck();
  void dump();
  void shuffle();
  int get_length() { return length; };
  int get_allocated_size() { return allocated_size; };

private:
  int length;
  int allocated_size;
  Card *deck;
};

#endif /* PILE_H */
