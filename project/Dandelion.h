#pragma once
#include "Plant.h"

class Dandelion : public Plant
{
public:
	Dandelion(Position position, int bornAt);
	Dandelion();

	void initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign) override;
	Dandelion* clone(int turn) override;
};

