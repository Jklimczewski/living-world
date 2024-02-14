#pragma once
#include "Plant.h"

class Grass : public Plant
{
public:
	Grass(Position position, int bornAt);
	Grass();

	void initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign) override;
	Grass* clone(int turn) override;
};

