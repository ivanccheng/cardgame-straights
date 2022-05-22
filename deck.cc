#include "deck.h"
#include "card.h"
#include <vector>
#include <memory>
#include <random> 
#include <algorithm>
#include <stdio.h> 
#include <iostream>

Deck::Deck(unsigned seed) : seed {seed} {
	rng = std::make_shared<std::default_random_engine>(seed);
	createDeck();
}

/*
void Deck::createDeck() {
	for(int i = 0; i < 13; i++) {
		for(int j = 0; j < 4; j++) {
		       cards.push_back(std::make_shared<Card>(Rank(i), Suit(j)));
		}
	}
} */

void Deck::createDeck() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 13; j++) {
               cards.push_back(std::make_shared<Card>(Rank(j), Suit(i)));
        }
    }
}

void Deck::shuffle() {
	std::shuffle(cards.begin(), cards.end(), *rng);
}

void Deck::setSeed(int s) {
	seed = s;
}

int Deck::getSeed() const {
	return seed;
}

std::shared_ptr<Card> Deck::getCard(int n) const {
	return cards.at(n);
}

std::ostream& operator<< (std::ostream& out, const Deck &d) {
	for (int i = 0; i < 52; i++) {
		out << *d.getCard(i);
		if ((i + 1) % 13 == 0) {
			out << std::endl;
		} else {
			out << " ";
		}
	}
	return out;
}


