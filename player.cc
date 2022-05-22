#include "player.h"
#include "card.h"
#include "exception.h"
#include "table.h"
#include "deck.h"

#include <vector>
#include <string>
#include <iostream>

Player::Player(std::shared_ptr<Table> t, int id, char type) : table {t}, id {id}, type {type} {
}

std::vector<std::shared_ptr<Card>> Player::getHand() const {
	return hand;
}

std::vector<std::shared_ptr<Card>> Player::getDiscards() const {
	return discards;
}
std::vector<std::shared_ptr<Card>> Player::legalMoves() const {
	std::vector<std::shared_ptr<Card>> moves;
	for (auto card : hand) {
		if (table->isLegal(card)) {
			moves.push_back(card);
		}
	}
	auto c = std::make_shared<Card>(Rank::Seven, Suit::S);
	if (moves.empty()) {
		return moves;
	}
	for (int i = 0; i < moves.size(); i++) {
		if (*moves.at(i) == *c) {
			moves.clear();
			moves.push_back(c);
			break;
		}
	}
	return moves;
}

void Player::discard(Card c) { 
	int i = 0;
	for (auto card : hand) {
		if (c == *card) {
			discards.push_back(hand.at(i));
			hand.erase(hand.begin() + i);
			std::cout << "Player" << id + 1 << " discards " << c << "." << std::endl;
			return;
		}
		i++;
	}
	throw IllegalMove{};
}

void Player::playCard(Card c) {
	for (int i = 0; i < legalMoves().size(); i++) {
		if (c == *legalMoves().at(i)) {
			table->addCard(legalMoves().at(i));
			for (int j = 0; j < hand.size(); j++) {
				if (*hand.at(j) == c) {
					hand.erase(hand.begin() + j);
					break;
				}
			}
			std::cout << "Player" << id + 1 << " plays " << c << "." << std::endl;
			return;
		}
	}
	throw IllegalMove{};
}
		
	
void Player::addCard(std::shared_ptr<Card> c) {
	hand.push_back(c);
}

void Player::clearPiles() {
	hand.clear();
	discards.clear();
}

void Player::updateScore() {
	int old_score = score;
	std::cout << "Player" << id + 1 << "'s discards:";
	for (auto card : discards) {
		std::cout << " " << *card;
		score += (card->getRank() + 1);
	}
	std::cout << std::endl << "Player" << id + 1 << "'s score: " << old_score;
	std::cout << " + " << score - old_score << " = " << score << std::endl; 
}

int Player::getScore() const {
	return score;
}

std::shared_ptr<Table> Player::getTable() const{
	return table;
}

void Player::setScore(int n) {
	score = n;
}

void Player::setHand(std::vector<std::shared_ptr<Card>> c) {
	hand = c;	
}

void Player::setDiscards(std::vector<std::shared_ptr<Card>> c) {
	discards = c;
}


bool Player::hasLegalMoves() const {
	return (!(legalMoves().empty()));
}

char Player::getType() const{
	return type;
}

std::ostream &operator<< (std::ostream &out, const Player &p){
	out << *p.getTable();
	out << "Your hand:";
	for (auto card : p.getHand()) {
		out << " " << *card;
	}
	out << std::endl;
	out << "Legal plays:";
	for (auto card : p.legalMoves()) {
		out << " " << *card;
	}
	out << std::endl;
	return out;
}







	
