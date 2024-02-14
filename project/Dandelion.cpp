#include "Dandelion.h"

Dandelion::Dandelion(Position position, int bornAt) : Plant(position, bornAt)
{
    initParams(0, 0, 6, 2, "D");
}

Dandelion::Dandelion() : Plant()
{

}

Dandelion* Dandelion::clone(int turn) {
    return new Dandelion(Position(-1, -1), turn);
}

void Dandelion::initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign)
{
    Organism::initParams(power, initiative, liveLength, powerToReproduce, sign);
}