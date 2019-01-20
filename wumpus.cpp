#include <iostream>
#include <time.h>

#include "agent.h"
#include "world.h"

void instructions()
{
	std::cout << "Welcome to the Wumpus World Simulator!\n\n";
	std::cout << "Player moves:\n";
	std::cout << "Move (F)orward, Turn (L)eft, Turn (R)ight, (G)rab the Gold, (S)hoot the Arrow, (C)limb.\n\n";
	std::cout << "Sensors: In the square\n";
	std::cout << "1. containing the wumpus and in the directly (not diagonally) adjacent squares, there is a (S)tench.\n";
	std::cout << "2. directly adjacent to a pit, there is a (B)reeze.\n";
	std::cout << "3. where the gold is, there is a (G)litter.\n";
	std::cout << "4. When the wumpus is killed, it (R)oars.\n\n";
	std::cout << "Environment:\n";
	std::cout << "1. one randomly located piece of gold.\n";
	std::cout << "2. one randomly located wumpus (not moving).\n";
	std::cout << "3. 20% of the randomly selected squares may have pits.\n\n";
	std::cout << "Equipment:\nThe Hunter has 1 arrow.\n\n";
	std::cout << "Notes:\n";
	std::cout << "1. The Hunter dies if he is in the square with pit.\n";
	std::cout << "2. The Hunter dies if he is in the square with a live wumpus.\n";
	std::cout << "3. A shot arrow will kill wumpus in the direction the Hunter is facing.\n";
	std::cout << "Press any key to start the simulation ...";
}

int
main(int argc, char const *argv[])
{
	srand(time(nullptr));

	instructions();

	agent a;
	all_sensors as;

	std::unique_ptr<gamer> g{new gamer{std::unique_ptr<agent> {new agent}}};

	world w(4, 4);
	w.setUserPos(std::move(g), 0, 0);
	w.setSpecialPos(PIT, 2, 0);
	w.setSpecialPos(WUMPUS, 0, 2);
	w.setSpecialPos(PIT, 2, 2);
	w.setSpecialPos(PIT, 3, 3);
	w.setSpecialPos(GOLD, 1, 2);

	do
	{
		// a.nextAction(as);
		std::cin.get();
		system("clear");
		w.Print();
	} while (w.nextStep());
	std::cout << "Final score = " << w.GetScore() << "\n";
	
	return 0;
}
