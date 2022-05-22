#include "card.h"
#include "exception.h"
#include <iostream>
#include <sstream> 
#include <vector>
#include <string>


Card::Card(Rank r, Suit s) : rank {r}, suit {s} {}

int Card::getSuit() const {
	int index = 0;
	for (int i = 0; i < 4; i++) {
		if (Suit(i) == suit) {
			index = i;
			break;
		}
	}
	return index;
}

int Card::getRank() const { 
	int index = 0;
	for (int i = 0; i < 13; i++) {
		if (Rank(i) == rank) {
			index = i;
			break;
		}
	}
	return index;
}	

void Card::setSuit(Suit s){
	suit = s;
}

void Card::setRank(Rank r) {
	rank = r;
}

std::ostream& operator<< (std::ostream& out, const Card &c) {
	std::vector<char> r{'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	std::vector<char> s{'C', 'D', 'H', 'S'};
	out << r.at(c.getRank()) << s.at(c.getSuit());
	return out;
}

std::istream& operator>> (std::istream& is, Card &c) {
	std::string s;
	is >> s;
	if (s.length() > 2) {
		throw InvalidCard{};
	}
	char r = s.at(0);
	if (!((r == 'A') || (r == '2') || (r == '3') || (r == '4') || (r == '5') || (r == '6')
		       	|| (r == '7') || (r == '8') || (r == '9') || (r == 'T') || (r == 'J') 
			|| (r == 'Q') || (r == 'K'))) {
		throw InvalidCard{};
	}
	char st = s.at(1);
	if (!((st == 'C') || (st == 'D') || (st == 'H') || (st == 'S'))) {
		throw InvalidCard{};
	}
	std::vector<char> ranks{'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	std::vector<char> suits{'C', 'D', 'H', 'S'};
	for (int i = 0; i < ranks.size(); i++) {
		if (ranks.at(i) == r) {
			c.setRank(Rank(i));
			break;
		}
	}
	for (int i = 0; i < suits.size(); i++) {
		if (suits.at(i) == st) {
			c.setSuit(Suit(i));
			break;
		}
	}
	return is;
}

bool operator== (const Card &rhs, const Card &lhs) {
	return ((lhs.getRank() == rhs.getRank()) && 
			(lhs.getSuit() == rhs.getSuit()));
}




