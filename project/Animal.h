#pragma once
#include "Organism.h"

using namespace std;

class Animal : public Organism
{
private:
	Position lastPosition;
public:
	Animal(Position position, int bornAt);
	Animal();

	Position getLastPosition();
	void setLastPosition(Position position);

	void move(int dx, int dy);
	void makeMove(Position position, Organism* orgPtr, int turn);

	virtual ~Animal() {}
};

