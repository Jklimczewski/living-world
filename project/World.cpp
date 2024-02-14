#include <fstream>
#include <iostream>
#include <algorithm>
#include "World.h"
#include "Grass.h"
#include "Toadstool.h"
#include "Dandelion.h"
#include "Wolf.h"
#include "Sheep.h"

using namespace std;

string World::getOrganismFromPosition(int x, int y)
{
	for (auto organismPtr : organisms) {
		Organism& organism = *organismPtr;
		if (organism.getPosition().getX() == x && organism.getPosition().getY() == y)
			return organism.getSign();
	}
	return "";
}

Organism* World::getOrganismFromPosition(Position position)
{
	for (auto organismPtr : organisms) {
		Organism& organism = *organismPtr;
		if (organism.getPosition().getX() == position.getX() && organism.getPosition().getY() == position.getY())
			return organismPtr;
	}
}

bool World::isPositionOnWorld(int x, int y)
{
	return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
	return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

vector<Position> World::getVectorOfFreePositionsAround(Position position)
{
	int pos_x = position.getX(), pos_y = position.getY();
	vector<Position> result;
	for (int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
				result.push_back(Position(pos_x + x, pos_y + y));
			}
	auto iter = remove_if(result.begin(), result.end(),
		[this](Position pos) {return !isPositionFree(pos); });
	result.erase(iter, result.end());

	return result;
}

vector<Position> World::getVectorOfPositionsAround(Position position)
{
	int pos_x = position.getX(), pos_y = position.getY();
	vector<Position> result;
	for (int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
				result.push_back(Position(pos_x + x, pos_y + y));
			}

	return result;
}

World::World(int worldX, int worldY)
{
	setWorldX(worldX);
	setWorldY(worldY);
}

int World::getWorldX()
{
	return this->worldX;
}

void World::setWorldX(int worldX)
{
	this->worldX = worldX;
}

int World::getWorldY()
{
	return this->worldY;
}

void World::setWorldY(int worldY)
{
	this->worldY = worldY;
}

int World::getTurn()
{
	return this->turn;
}

void World::addOrganism(Organism* organism)
{
	this->organisms.push_back(organism);
}

void World::makeTurn()
{
	sort(organisms.begin(), organisms.end(), 
		[](Organism* a, Organism* b) { return a->getInitiative() > b->getInitiative(); });

	Position currPosition;
	vector<Position> newPositions;
	vector<Position> newBirthPositions;
	vector<Organism*> newOrganisms;
	int numberOfNewPositions;
	int numberOfNewBirthPositions;
	int randomIndex;

	srand(time(0));
	for (auto organismPtr : this->organisms) {
		Organism& organism = *organismPtr;
		currPosition = organism.getPosition();
		if (isPositionOnWorld(currPosition.getX(), currPosition.getY())) {
			newPositions = getVectorOfPositionsAround(currPosition);
			numberOfNewPositions = newPositions.size();	
			if (numberOfNewPositions > 0) {
				randomIndex = rand() % numberOfNewPositions;
				Position chosenPos = newPositions[randomIndex];
				bool isFree = isPositionFree(chosenPos);
				if (isFree) {
					organism.makeMove(chosenPos, nullptr, turn);
				}
				else {
					Organism* metOrganismPtr = getOrganismFromPosition(chosenPos);
					organism.makeMove(chosenPos, metOrganismPtr, turn);
				}
			}

			if (isPositionOnWorld(organism.getPosition().getX(), organism.getPosition().getY())) {
				newBirthPositions = getVectorOfFreePositionsAround(currPosition);
				numberOfNewBirthPositions = newBirthPositions.size();
				if (numberOfNewBirthPositions > 0) {
					randomIndex = rand() % numberOfNewBirthPositions;
					Position chosenBirthPos = newBirthPositions[randomIndex];
					Organism* newAnimal = organism.makeReproduce(chosenBirthPos, turn);
					if (newAnimal != nullptr) {
						newOrganisms.push_back(newAnimal);
						cout << organism.getSign() + " has born a baby at: " + chosenBirthPos.toString() << endl;
					}
				}
			}
			organism.setPower(organism.getPower() + 1);
			organism.setLiveLength(organism.getLiveLength() - 1);
			if (organism.getLiveLength() == 0) {
				cout << organism.getSign() + " died of old age at: " + organism.getPosition().toString() << endl;
				pair<int, int>* selfLifePairPtr = organism.getAncestors().back();
				selfLifePairPtr->second = turn;
			}
		}
	}
	this->organisms.erase(remove_if(this->organisms.begin(), this->organisms.end(),
		[](Organism* o) { return o->getLiveLength() <= 0; }),
		this->organisms.end());
	this->organisms.erase(remove_if(this->organisms.begin(), this->organisms.end(),
		[](Organism* o) { return o->getPosition().getX() < 0; }),
		this->organisms.end());

	for (auto organismPtr : newOrganisms) {
		World::addOrganism(organismPtr);
	}
	turn++;
}

void World::writeWorld(string fileName)
{
	fstream my_file;
	my_file.open(fileName, ios::out | ios::binary);
	if (my_file.is_open()) {
		my_file.write((char*)&this->worldX, sizeof(int));
		my_file.write((char*)&this->worldY, sizeof(int));
		my_file.write((char*)&this->turn, sizeof(int));
		int orgs_size = static_cast<int>(this->organisms.size());
		my_file.write((char*)&orgs_size, sizeof(int));
		for (int i = 0; i < orgs_size; i++) {
			int data;
			data = this->organisms[i]->getPower();
			my_file.write((char*)&data, sizeof(int));
			data = this->organisms[i]->getPosition().getX();
			my_file.write((char*)&data, sizeof(int));
			data = this->organisms[i]->getPosition().getY();
			my_file.write((char*)&data, sizeof(int));
			data = this->organisms[i]->getInitiative();
			my_file.write((char*)&data, sizeof(int));
			data = this->organisms[i]->getLiveLength();
			my_file.write((char*)&data, sizeof(int));
			data = this->organisms[i]->getPowerToReproduce();
			my_file.write((char*)&data, sizeof(int));
			string s_data = this->organisms[i]->getSpecies();
			int s_size = s_data.size();
			my_file.write((char*)&s_size, sizeof(int));
			my_file.write(s_data.data(), s_data.size());
			string s_data2 = this->organisms[i]->getSign();
			int s_size2 = s_data2.size();
			my_file.write((char*)&s_size2, sizeof(int));
			my_file.write(s_data2.data(), s_data2.size());
			data = this->organisms[i]->getBornAt();
			my_file.write((char*)&data, sizeof(int));
			
		}
		my_file.close();
	}
}

void World::readWorld(string fileName)
{
	fstream my_file;
	my_file.open(fileName, ios::in | ios::binary);
	if (my_file.is_open()) {
		int result;
		my_file.read((char*)&result, sizeof(int));
		this->worldX = (int)result;
		my_file.read((char*)&result, sizeof(int));
		this->worldY = (int)result;
		my_file.read((char*)&result, sizeof(int));
		this->turn = (int)result;
		my_file.read((char*)&result, sizeof(int));
		int orgs_size = (int)result;
		vector<Organism*> new_organisms;
		for (int i = 0; i < orgs_size; i++) {
			int power;
			my_file.read((char*)&result, sizeof(int));
			power = (int)result;

			int pos_x;
			my_file.read((char*)&result, sizeof(int));
			pos_x = (int)result;
			int pos_y;
			my_file.read((char*)&result, sizeof(int));
			pos_y = (int)result;
			Position pos{ pos_x, pos_y };

			int initiative;
			my_file.read((char*)&result, sizeof(int));
			initiative = (int)result;

			int liveLength;
			my_file.read((char*)&result, sizeof(int));
			liveLength = (int)result;

			int powerToReproduce;
			my_file.read((char*)&result, sizeof(int));
			powerToReproduce = (int)result;

			int s_size;
			my_file.read((char*)&result, sizeof(int));
			s_size = (int)result;
			string species;
			species.resize(s_size);
			my_file.read((char*)&species[0], s_size);

			int s_size2;
			my_file.read((char*)&result, sizeof(int));
			s_size2 = (int)result;
			string sign;
			sign.resize(s_size2);
			my_file.read((char*)&sign[0], s_size2);

			int bornAt;
			my_file.read((char*)&result, sizeof(int));
			bornAt = (int)result;

			Organism* org = nullptr;
			switch(sign[0]) {
				case 'S':
					org = new Sheep{ pos, bornAt };
					break;
				case 'G':
					org = new Grass{ pos, bornAt };
					break;
				case 'D':
					org = new Dandelion{ pos, bornAt };
					break;
				case 'W':
					org = new Wolf{ pos, bornAt };
					break;
				case 'T':
					org = new Toadstool{ pos, bornAt };
					break;
				default:
					cout << "Bad sign" << endl;
					break;
			}
			if (org) {
				org->initParams(power, initiative, liveLength, powerToReproduce, sign);
				org->setSpecies(species);
				new_organisms.push_back(org);
			}
		}
		this->organisms = new_organisms;
		my_file.close();
	}
}

void World::listAllLivingAnimals() {
	for (auto organismPtr : organisms) {
		Organism& organism = *organismPtr;
		cout << organism.toString() << endl;
	}
}

string World::toString()
{
	string result = "\nturn: " + to_string(getTurn()) + "\n";
	string spec;

	for (int wY = 0; wY < getWorldY(); ++wY) {
		for (int wX = 0; wX < getWorldX(); ++wX) {
			spec = getOrganismFromPosition(wX, wY);
			if (spec != "")
				result += spec;
			else
				result += separator;
		};
		result += "\n";
	}
	return result;
}

