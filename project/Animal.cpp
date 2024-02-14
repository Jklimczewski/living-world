#include "Animal.h"
#include <iostream>

Animal::Animal(Position position, int bornAt) : Organism(position, bornAt)
{
	setSpecies("A");
	setLastPosition(position);
}

Animal::Animal() : Organism()
{
	setSpecies("A");
}

Position Animal::getLastPosition()
{
	return this->lastPosition;
}

void Animal::setLastPosition(Position position)
{
	this->lastPosition = position;
}

void Animal::move(int dx, int dy)
{
	setLastPosition(Organism::getPosition());
	Organism::move(dx, dy);
}

void Animal::makeMove(Position position, Organism* orgPtr, int turn) {
	setLastPosition(getPosition());
	if (orgPtr == nullptr) {
		setPosition(position);
	}
	else {
		Organism& metOrganism = *orgPtr;
		if (getPower() > metOrganism.getPower()) {
			metOrganism.setPosition(Position{ -1, -1 });
			pair<int, int>* metOrgLifePtr = metOrganism.getAncestors().back();
			metOrgLifePtr->second = turn;
			if (metOrganism.getSign()[0] == 'T') {
				cout << getSign() + " ate a Toadstool at: " + position.toString() << endl;
				setPosition(Position{ -1, -1 });
				pair<int, int>* selfLifePtr = getAncestors().back();
				selfLifePtr->second = turn;
			}
			else {
				setPosition(position);
			}
			cout << metOrganism.getSign() + " has been eaten by " + getSign() + " at: " + position.toString() << endl;
		}
		else {
			pair<int, int>* selfLifePtr = getAncestors().back();
			selfLifePtr->second = turn;
			setPosition(Position {-1, -1});
			cout << getSign() + " has been eaten by " + metOrganism.getSign() + " at: " + position.toString() << endl;
		}
	}
}


