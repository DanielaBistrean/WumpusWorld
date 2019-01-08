#include <iostream>
#include "agent.h"

#include <stdlib.h>

actions
agent::nextAction(const all_sensors& as)
{
	std::cout << "Sensors:\n";
	std::cout << "Stench:"  << as.Stench << "\n";
	std::cout << "Breeze:"  << as.Breeze << "\n";
	std::cout << "Glitter:"  << as.Glitter << "\n";
	std::cout << "Scream:"  << as.Scream << "\n";
	std::cout << "Bump:"  << as.Bump << "\n";

	std::cout << "Please enter your action: ";
	char a;

	while (1)
	{
		std::cin >> a;
		
		switch(a)
		{
			case 'f':
				return FORWARD;
			case 'l':
				return TURN_LEFT;
			case 'r':
				return TURN_RIGHT;
			case 's':
				return SHOOT;
			case 'g':
				return GRAB;
			case 'e':
				exit(1);
			default:
				std::cout << "Unknown action. Please try again using the action presented\n";
		}
	}

}
