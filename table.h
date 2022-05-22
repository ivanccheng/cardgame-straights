#ifndef _TABLE_H_
#define _TABLE_H_

#include <memory>
#include <vector>

class Card;

class Table { 
	private: 
		std::vector<std::shared_ptr<Card>> cPile;
		std::vector<std::shared_ptr<Card>> dPile;
		std::vector<std::shared_ptr<Card>> hPile;
		std::vector<std::shared_ptr<Card>> sPile;
	public: 
		void addCard(std::shared_ptr<Card> c);
		bool isLegal(std::shared_ptr<Card> c) const;
		void clear();
		std::vector<std::shared_ptr<Card>> getcPile() const;
		std::vector<std::shared_ptr<Card>> getdPile() const;
		std::vector<std::shared_ptr<Card>> gethPile() const;
		std::vector<std::shared_ptr<Card>> getsPile() const;

};	

std::ostream& operator<< (std::ostream &out, const Table &t);


#endif
