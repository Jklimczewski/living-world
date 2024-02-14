#pragma once
#include "Plant.h"

class Toadstool : public Plant
{
public:
	Toadstool(Position position, int bornAt);
	Toadstool();

	Toadstool* clone(int turn) override;

	void initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign) override;
};

