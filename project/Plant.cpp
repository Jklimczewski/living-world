#include "Plant.h"

Plant::Plant(Position position, int bornAt) : Organism(position, bornAt)
{
	setSpecies("P");
}

Plant::Plant() : Organism()
{
	setSpecies("P");
}

void Plant::move(int dx, int dy)
{
	Organism::move(0, 0);
}
void Plant::makeMove(Position position, Organism* orgPtr, int turn) {}

