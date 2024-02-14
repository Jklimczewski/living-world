#include "Wolf.h"

Wolf::Wolf(Position position, int bornAt) : Animal(position, bornAt)
{
    initParams(8, 5, 20, 16, "W");
}

Wolf::Wolf() : Animal()
{

}
Wolf* Wolf::clone(int turn) {
    return new Wolf(Position(-1, -1), turn);
}

void Wolf::initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign)
{
    Organism::initParams(power, initiative, liveLength, powerToReproduce, sign);
}