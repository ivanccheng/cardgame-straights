#ifndef _CARD_H_
#define _CARD_H_

#include <iostream> 

enum Rank {A, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, J, Q, K} ;
enum Suit {C, D, H, S};

class Card {
	private:
		Rank rank;
		Suit suit;
		

	public: 
		Card(Rank r = Rank(1), Suit s = Suit(1));
		int getSuit() const;
		int getRank() const;
		void setSuit(Suit s);
		void setRank(Rank r);
		
	
};
std::istream& operator>> (std::istream& is, Card &c);

bool operator== (const Card &rhs, const Card &lhs);

std::ostream& operator<< (std::ostream& out, const Card &c);
		

#endif


