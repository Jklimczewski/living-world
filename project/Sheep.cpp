#include "Sheep.h"

Sheep::Sheep(Position position, int bornAt) : Animal(position, bornAt)
{
    initParams(3, 3, 10, 6, "S");
}

Sheep::Sheep() : Animal()
{

}
Sheep* Sheep::clone(int turn) {
    return new Sheep(Position(-1, -1), turn);
}

void Sheep::initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign)
{
    Organism::initParams(power, initiative, liveLength, powerToReproduce, sign);
}
