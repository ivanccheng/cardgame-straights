#include "table.h"
#include "exception.h"
#include "card.h"


#include <string>
#include <algorithm>

	

void Table::addCard(std::shared_ptr<Card> c) {
	if (!(isLegal(c))) { 
		
		std::cout << "Table Illegal: " << *c << std::endl;
		throw IllegalMove{};
       	}
	int suit = c->getSuit();
	switch (suit) {
		case 0:
			cPile.push_back(c);
			break;
		case 1: 
			dPile.push_back(c);
			break;
		case 2: 
			hPile.push_back(c);
			break;
		case 3:
			sPile.push_back(c);
			break;
	}
}


int getHighest(std::vector<std::shared_ptr<Card>> pile) {
	int max;
	bool first = true;
	for (auto card : pile) {
		if (first) {
			max = card->getRank();
			first = !(first);
		} else if (card->getRank() > max) {
			max = card->getRank();
		}
	}
	return max;
}

int getLowest(std::vector<std::shared_ptr<Card>> pile) {
	int min;
	bool first = true;
	for (auto card : pile) {
		if (first) {
			min = card->getRank();
			first = !(first);
		} else if (card->getRank() < min) {
			min = card->getRank();
		}
	}
	return min;
}


bool Table::isLegal(std::shared_ptr<Card> c) const {
	if ( c->getRank() == 6 ) {
		return true;
	} 
	int card_suit = c->getSuit();
	if (card_suit == 0) {
		if (cPile.empty()) {
			return false;
		}
		if ((c->getRank() == getLowest(cPile) - 1) || (c->getRank() == getHighest(cPile) + 1)) {
			return true;
		}
	}
	if (card_suit == 1) {
		if(dPile.empty()) {
			return false;
		}
		if ((c->getRank() == getLowest(dPile) - 1) || (c->getRank() == getHighest(dPile) + 1)) {
			return true;
		}
	}
	if (card_suit  == 2) {
		if (hPile.empty()) {
			return false;
		}
		if ((c->getRank() == getLowest(hPile) - 1) || (c->getRank() == getLowest(hPile) + 1)) {
			return true;
		}
	}
	if (card_suit  == 3) {
		if (sPile.empty()) {
			return false;
		}
		if ((c->getRank() == getLowest(sPile) - 1) || (c->getRank() == getHighest(sPile) + 1)) {
			return true;
		}
	}
	return false;
}

inline bool sortByRank(std::shared_ptr<Card> &lhs, std::shared_ptr<Card> &rhs) {
	return (lhs->getRank() < rhs->getRank());
}

char outputCard(std::shared_ptr<Card> c) {
	std::vector<char> ranks{'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	return (ranks.at(c->getRank()));
}


std::ostream& operator<< (std::ostream &out, const Table &t) {
	out << "Cards on the table: " << std::endl;
	out << "Clubs:";
	std::vector<std::shared_ptr<Card>> tmp;
	if (t.getcPile().size() > 0) {
		for (auto card : t.getcPile()) {
			tmp.push_back(card);
		}
		std::sort(tmp.begin(), tmp.end(), sortByRank);
		for (auto card : tmp) {
			out << " " << outputCard(card);
		}
	}
	tmp.clear();
	out << std::endl;
	out << "Diamonds:";
	if (t.getdPile().size() > 0) {
		for (auto card : t.getdPile()) {
			tmp.push_back(card);
		}
		std::sort(tmp.begin(), tmp.end(), sortByRank);
		for (auto card : tmp) {
			out << " " << outputCard(card);
		}
	}
	tmp.clear();
	out << std::endl;
	out << "Hearts:";
	if (t.gethPile().size() > 0) {
		for (auto card : t.gethPile()) {
			tmp.push_back(card);
		}
		std::sort(tmp.begin(), tmp.end(), sortByRank);
		for (auto card : tmp) {
			out << " " << outputCard(card);
		}
	}
	tmp.clear();	
	out << std::endl;
	out << "Spades:";
	if (t.getsPile().size() > 0) {
		for (auto card : t.getsPile()) {
			tmp.push_back(card);
		}
		std::sort(tmp.begin(), tmp.end(), sortByRank);
		for (auto card : tmp) {
			out << " " << outputCard(card);
		}
	}
	tmp.clear();	
	out << std::endl;
	return out;
}

void Table::clear() {
	cPile.clear();
	dPile.clear();
	hPile.clear();
	sPile.clear();
}

std::vector<std::shared_ptr<Card>> Table::getcPile() const {
	return cPile;
}

std::vector<std::shared_ptr<Card>> Table::getdPile() const {
	return dPile;
}

std::vector<std::shared_ptr<Card>> Table::gethPile() const {
	return hPile;
}

std::vector<std::shared_ptr<Card>> Table::getsPile() const {
	return sPile;
}

