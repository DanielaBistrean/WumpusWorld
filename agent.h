#ifndef AGENT
#define AGENT 1

#include "gamer.h"

enum actions
{
	TURN_LEFT,
	TURN_RIGHT,
	FORWARD,
	SHOOT,
	GRAB
};

class agent
{
public:
	actions nextAction(const all_sensors& as);
};

#endif
