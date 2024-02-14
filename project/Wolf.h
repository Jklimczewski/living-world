#pragma once
#include "Animal.h"

class Wolf : public Animal
{
public:
	Wolf(Position position, int bornAt);
	Wolf();

	void initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign) override;
	Wolf* clone(int turn) override;
};
