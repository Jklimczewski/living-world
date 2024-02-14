#include <iostream>
#include "Position.h"
#include "World.h"
#include "Grass.h"
#include "Toadstool.h"
#include "Dandelion.h"
#include "Wolf.h"
#include "Sheep.h"

using namespace std;

int main()
{
	// Position 
	Position p1{ 0, 0 };
	Position p2{ 1, 1 };
	Position p3{ 5, 2 };
	Position p4{ 1, 3 };
	Position p5{ 1, 4 };
	Position p6{ 2, 1 };

	// Plant & Animal
	Grass grass { p1, 0 };
	Toadstool toadstool{ p3, 0 };
	Dandelion dandelion{ p2, 0 };
	Wolf wolf{ p4, 0 };
	Sheep sheep{ p5, 0 };
	//Animal animal {p1};

	// Organisms test
	cout << "Organisms test" << endl;
	cout << grass.toString() << endl;
	grass.move(3, 4);
	dandelion.move(10, 10);
	toadstool.move(10, 10);
	wolf.move(-1, -1);
	sheep.move(5, 5);
	cout << grass.toString() << endl;
	cout << dandelion.toString() << endl;
	cout << toadstool.toString() << endl;
	cout << wolf.toString() << endl;
	cout << sheep.toString() << endl;
	sheep.move(1, 1);
	cout << sheep.toString() << endl;
	cout << sheep.getLastPosition().toString() << endl;

	// World test
	cout << endl << "World test" << endl;
	World world{12, 12};
	world.addOrganism(&grass);
	world.addOrganism(&dandelion);
	world.addOrganism(&toadstool);
	world.addOrganism(&wolf);
	world.addOrganism(&sheep);

	auto positions = world.getVectorOfFreePositionsAround(Position(0, 1));

	for (auto pos : positions)
		cout << pos.toString() << endl;

	// Tura 0
	cout << world.toString() << endl;

	// Tura 1
	world.makeTurn();
	cout << world.toString() << endl;

	// Tura 2
	world.makeTurn();
	cout << world.toString() << endl;

	world.writeWorld("world.bin");
	world.listAllLivingAnimals();

	// Tura 3
	world.makeTurn();
	cout << world.toString() << endl;
	world.listAllLivingAnimals();

	// powrot do Tury 2
	world.readWorld("world.bin");
	cout << world.toString() << endl;
	world.listAllLivingAnimals();

	world.makeTurn();
	cout << world.toString() << endl;
	world.makeTurn();
	cout << world.toString() << endl;
	world.makeTurn();
	cout << world.toString() << endl;
	world.listAllLivingAnimals();
	world.makeTurn();
	world.makeTurn();
	world.makeTurn();
	world.makeTurn();
	world.makeTurn();
	cout << world.toString() << endl;
	world.listAllLivingAnimals();

	return 0;
}
