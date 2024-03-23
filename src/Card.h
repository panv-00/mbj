#ifndef CARD_H
#define CARD_H

#define SUITS "CDHS"
#define FACES "23456789TJQKA"

class Card
{
public:
  Card();
  ~Card();

  void SetFaceSuit(char f, char s);
  char GetFace() { return face; };
  char GetSuit() { return suit; };
  int GetValue() { return value; };
  void Dump();
  void SetCard(Card card);

private:
  int value;
  char face;
  char suit;
};

#endif
