#pragma once
#include "Animal.h"

class Sheep : public Animal
{
public:
	Sheep(Position position, int bornAt);
	Sheep();

	Sheep* clone(int turn) override;

	void initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign) override;
};
