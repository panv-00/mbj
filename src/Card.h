#ifndef CARD_H
#define CARD_H

const char suits[] = "CDHS";
const char card_faces[] = "23456789TJQKA";
const int card_values[] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

class Card
{
public:
  Card();
  ~Card();

  void set_face_suit(char f, char s);
  char get_face() { return face; };
  char get_suit() { return suit; };
  int get_value() { return value; };
  void dump();
  void set_card(Card card);

private:
  int value;
  char face;
  char suit;

  int find(const char arr[], int len, char seek);
  int face_to_value(char f);
};

#endif /* CARD_H */
