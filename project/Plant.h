#pragma once
#include "Organism.h"

class Plant : public Organism
{
public:
	Plant(Position position, int bornAt);
	Plant();

	virtual ~Plant() {}

	void move(int dx, int dy);
	void makeMove(Position position, Organism* orgPtr, int turn);
};