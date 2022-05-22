#include "controller.h"
#include "deck.h"
#include "card.h"
#include "exception.h"
#include "table.h" 
#include "human.h"
#include "computer.h"

#include <vector>
#include <memory>
#include <iostream>
#include <ostream>
#include <algorithm>


Controller::Controller(std::shared_ptr<Deck> deck, unsigned seed) : deck(deck), seed (seed) {
}

std::shared_ptr<Table> Controller::getTable() const {
		return table;
}

void Controller::dealCards() {
	for (int i = 0; i < 52; i++) {
		if (i < 13) {
			players.at(0)->addCard(deck->getCard(i));
		} else if (i < 26) {
			players.at(1)->addCard(deck->getCard(i));
		} else if (i < 39) {
			players.at(2)->addCard(deck->getCard(i));
		} else {
			players.at(3)->addCard(deck->getCard(i));
		}
	}
}

void Controller::initGame() {
	table = std::make_shared<Table>();
	for (int i = 0; i < 4; i++) {
		std::cout << "Is Player" << i+1 << " a human (h) or a computer (c)?" << std::endl;
		char param; 
		std::cin >> param;
		if (param == 'h') {
			std::shared_ptr<Player> p = std::make_shared<Human>(table, i, 'h');
			players.push_back(p);
		} else if (param == 'c') {
			std::shared_ptr<Player> p = std::make_shared<Computer>(table, i, 'c');
			players.push_back(p);
		} else {
			players.clear();
			throw InvalidInput();
		} 
	}
	deck->shuffle();
	dealCards();
	firstPlayer();
}

void Controller::initRound() {
	for (auto player : players) {
		player->clearPiles();
	}
	table->clear();
	deck->shuffle();
	dealCards();
	firstPlayer();
}


void Controller::firstPlayer() {
	int first;
	Card seven_spades{Rank::Seven, Suit:S};
	for (int i = 0; i < 4; i++)  {
		for (auto card : players.at(i)->getHand()) {
			if (*card == seven_spades) {
				first = i;
			}
		}
	}
	turn = first;
}

int Controller::getFirst() const  {
	return turn;
}


int Controller::getTurn() const {
	return turn;
}


bool Controller::gameIsOver() const {
	bool over = 0;
	for (auto player : players) {
		if (player->getScore() >= 80) {
			over = true;
			break;
		}
	}
	return over;
}

void Controller::nextPlayer() {
	if (turn == 3) {
		turn = 0;
	} else { 
		turn++;
	}
}


bool Controller::roundIsOver() const {
	for (auto player : players) {
		if (!(player->getHand().empty())) {
			return false;
		}
	}
	return true;
}

int Controller::playTurn(int n) {
	if (players.at(n)->getType() == 'c') {
		//std::cout<< *players.at(n) << std::endl;
		players.at(n)->playTurn();
		nextPlayer();
		return 1;
	} 
	std::cout << *players.at(n);
	std::string cmd;
	while (!(std::cin.fail())) {
		std::cin >> cmd;
		if (cmd == "quit") {
			return -1;
		} else if (cmd == "deck") {
			std::cout << *deck;
		} else if (cmd == "hand") {
			for (auto c : players.at(n)->getHand()) {
				std::cout << *c << " ";
			}
			std::cout << std::endl;
		} else if (cmd == "table") {
			std::cout << *players.at(n)->getTable();
		} else if (cmd == "ragequit") {
			auto p = std::make_shared<Computer>(table, n, 'c');
			p->setHand(players.at(n)->getHand());
			p->setDiscards(players.at(n)->getDiscards());
			p->setScore(players.at(n)->getScore());
			players.at(n) = p;
			std::cout << "Player" << n + 1 << " ragequits. A computer will now take over." << std::endl;
			playTurn(n);

			return 0;
		} else if (cmd == "play" || cmd == "p") {			
			try {
				Card c;
				std::cin >> c;
				players.at(n)->playCard(c);
				nextPlayer();
				return 0;
			} catch (InvalidCard &e) { 
				std::cout << "Invalid card" << std::endl;
			} catch (...) {
				std::cout << "This is not a legal play." << std::endl;
			}
		} else if (cmd == "discard" || cmd == "d") {
			if (players.at(n)->hasLegalMoves()) {
				std::cout << "You have a legal play. You may not discard." << std::endl;
			} else {
				try {
					Card c;
					std::cin >> c;
					players.at(n)->discard(c);
					nextPlayer();
					return 0;
				} catch (...) {
					std::cout << "This is not a legal play." << std::endl;
				}
			}
		} else { 
			std::cout << "Invalid command" << std::endl;
		}
		cmd.clear();
	}
	return -1;
}



void Controller::updateScores() {
	for (auto player : players) {
		player->updateScore();
	}
}

void Controller::getWinners() {
	std::vector<int> winners;
	int min;
	for (int i = 0; i < players.size(); i++) { 
			if (i == 0) {
			min = players.at(i)->getScore();
			winners.push_back(0);
		} else if (players.at(i)->getScore() < min) {
			winners.clear();
			winners.push_back(i);
			min = players.at(i)->getScore();
		} else if (players.at(i)->getScore() == min) {
			winners.push_back(i);
		} 
	}
	for ( auto winner : winners) {
		std::cout << "Player" << winner + 1 << " wins!" <<std::endl;
	}
}

std::shared_ptr<Player> Controller::getPlayer(int n) {
	return players.at(n);
}	

			
