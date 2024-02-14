#include "Organism.h"

Organism::Organism(Position position, int bornAt)
{
	setPosition(position);
	setBornAt(bornAt);
}

int Organism::getPower()
{
	return this->power;
}

void Organism::setPower(int power)
{
	this->power = power;
}

Position Organism::getPosition()
{
	return this->position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}

string Organism::getSpecies()
{
	return this->species;
}

void Organism::setSpecies(string spec)
{
	this->species = spec;
}

int Organism::getInitiative()
{
	return this->initiative;
}

void Organism::setInitiative(int initiative)
{
	this->initiative = initiative;
}

int Organism::getLiveLength()
{
	return this->liveLength;
}

void Organism::setLiveLength(int liveLength)
{
	this->liveLength = liveLength;
}

int Organism::getPowerToReproduce()
{
	return this->powerToReproduce;
}

void Organism::setPowerToReproduce(int powerToReproduce)
{
	this->powerToReproduce = powerToReproduce;
}

string Organism::getSign()
{
	return this->sign;
}

void Organism::setSign(string sign)
{
	this->sign = sign;
}

int Organism::getBornAt()
{
	return this->bornAt;
}

void Organism::setBornAt(int bornAt)
{
	this->bornAt = bornAt;
}

list<pair<int, int>*> Organism::getAncestors()
{
	return this->ancestors;
}

void Organism::setAncestors(list<pair<int, int>*> ancestors)
{
	this->ancestors = ancestors;
}

string Organism::toString()
{
	string ancestorsString = "[";
	auto it = ancestors.begin();
	auto end = prev(ancestors.end()); 

	for (; it != end; ++it) {
		const auto& pairPtr = *it;
		if (pairPtr->second == -1) {
			ancestorsString += "(" + to_string(pairPtr->first) + ", " + "alive" + "), ";
		}
		else {
			ancestorsString += "(" + to_string(pairPtr->first) + ", " + to_string(pairPtr->second) + "), ";
		}
	}
	ancestorsString += "]";

	return "{ sign: " + this->getSign() +
		", species: " + this->getSpecies() +
		", power: " + to_string(getPower()) +
		", position: " + getPosition().toString() +
		", initiative: " + to_string(getInitiative()) +
		", liveLength: " + to_string(getLiveLength()) +
		", powerToReproduce: " + to_string(getPowerToReproduce()) +  
		", bornAt: " + to_string(getBornAt()) +
		", \n ancestors: " + ancestorsString + "}";
}

Organism* Organism::makeReproduce(Position pos, int turn) {
	Organism* newAnimal = nullptr;
	if (Organism::ifReproduce()) {
		newAnimal = clone(turn);
		list<pair<int, int>*> newAncestors;
		for (auto& pairPtr : getAncestors()) {
			newAncestors.push_back(pairPtr);
		}
		pair<int, int>* selfLifePtr = new pair<int, int>(turn, -1);
		newAncestors.push_back(selfLifePtr);
		newAnimal->Organism::setAncestors(newAncestors);
		newAnimal->Organism::setPosition(pos);
		Organism::setPower(Organism::getPower() / 2);
	}
	return newAnimal;
}

bool Organism::ifReproduce() {
	bool res = false;

	if (Organism::getPower() >= Organism::getPowerToReproduce()) {
		res = true;
	}
	return res;
}

void Organism::move(int dx, int dy)
{
	position.move(dx, dy);
}
void Organism::makeMove(Position position, Organism* orgPtr, int turn) {}

void Organism::initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign)
{
	setPower(power);
	setInitiative(initiative);
	setLiveLength(liveLength);
	setPowerToReproduce(powerToReproduce);
	setSign(sign);
	list<pair<int, int>*> ancestors;
	pair<int, int>* pairPtr = new pair<int, int>(0, -1);
	ancestors.push_back(pairPtr);
	setAncestors(ancestors);
}
