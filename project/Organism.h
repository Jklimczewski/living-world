#pragma once
#include <string>
#include "Position.h"
#include <list>
#include <utility>

using namespace std;

class Organism
{
private:
	int power;
	string species;
	int initiative;
	int liveLength;
	int powerToReproduce;
	string sign;
	Position position;
	int bornAt;
	list<pair<int, int>*> ancestors;

public:
	Organism(Position position, int bornAt);
	Organism() : power(0), species("O"), initiative(0), liveLength(0), powerToReproduce(0), sign("NA"), position(0, 0), bornAt(0), ancestors() {
		pair<int, int>* pairPtr = new pair<int, int>(0, 0);
		ancestors.push_back(pairPtr);
	};

	int getPower();
	void setPower(int power);
	string getSpecies();
	void setSpecies(string spec);
	int getInitiative();
	void setInitiative(int initiative);
	int getLiveLength();
	void setLiveLength(int liveLength);
	int getPowerToReproduce();
	void setPowerToReproduce(int powerToReproduce);
	string getSign();
	void setSign(string sign);
	Position getPosition();
	void setPosition(Position position);
	int getBornAt();
	void setBornAt(int bornAt);
	list<pair<int, int>*> getAncestors();
	void setAncestors(list<pair<int,int>*> ancestors);

	string toString();

	Organism* makeReproduce(Position pos, int turn);
	bool ifReproduce();

	virtual ~Organism() {}
	virtual void makeMove(Position position, Organism* orgPtr, int turn) = 0;
	virtual void move(int dx, int dy);
	virtual void initParams(int power, int initiative, int liveLength, int powerToReproduce, string sign) = 0;
	virtual Organism* clone(int turn) = 0;
};