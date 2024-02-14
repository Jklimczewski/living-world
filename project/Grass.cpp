#include "Grass.h"

Grass::Grass(Position position, int bornAt) : Plant(position, bornAt)
{
    initParams(0, 0, 6, 3, "G");
}

Grass::Grass() : Plant()
{

}

Grass* Grass::clone(int turn) {
    return new Grass(Position(-1, -1), turn);
}

void Grass::initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign)
{
    Organism::initParams(power, initiative, liveLength, powerToReproduce, sign);
}