#include "square.h"

all_sensors::all_sensors()
: Stench{false}
, Breeze{false}
, Glitter{false}
, Scream{false}
, Bump{false}
{}

guess::guess()
: wumpus{true}
, pit{true}
, unknown{true}
, ok{false}
, wumpus_cleared{false}
, pit_cleared{false}
{}

void
square::setStench(bool stench)
{
	m_sensors.Stench = stench;
}

void
square::setBreeze(bool breeze)
{
	m_sensors.Breeze = breeze;
}

void
square::setGlitter(bool glitter)
{
	m_sensors.Glitter = glitter;
}

void
square::setScream(bool scream)
{
	m_sensors.Scream = scream;
}

void
square::setBump(bool bump)
{
	m_sensors.Bump = bump;
}

bool
square::getStench()
{
	return m_sensors.Stench;
}

bool
square::getBreeze()
{
	return m_sensors.Breeze;
}

bool
square::getGlitter()
{
	return m_sensors.Glitter;
}

bool
square::getScream()
{
	return m_sensors.Scream;
}

bool
square::getBump()
{
	return m_sensors.Bump;
}

bool
square::getVisited()
{
	return m_visited;
}

void
square::setVisited(bool visited)
{
	m_visited = visited;
}

SquareType
square::getType()
{
	return m_type;
}

void
square::setType(SquareType st)
{
	m_type = st;
}

square::square(SquareType st)
: m_type{st}
{}

all_sensors
square::getSensor()
{
	return m_sensors;
}

void
square::setGuess(guess g)
{
	m_guess = g;
}

guess
square::getGuess()
{
	return m_guess;
}
