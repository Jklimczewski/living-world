#include "Toadstool.h"

Toadstool::Toadstool(Position position, int bornAt) : Plant(position, bornAt)
{
    initParams(0, 0, 12, 4, "T");
}

Toadstool::Toadstool() : Plant()
{

}

Toadstool* Toadstool::clone(int turn) {
    return new Toadstool(Position(-1, -1), turn);
}

void Toadstool::initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign)
{
    Organism::initParams(power, initiative, liveLength, powerToReproduce, sign);
}