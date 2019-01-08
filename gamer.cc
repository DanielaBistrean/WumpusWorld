#include "gamer.h"

all_sensors::all_sensors()
: Stench{false}
, Breeze{false}
, Glitter{false}
, Scream{false}
, Bump{false}
{}

gamer::gamer()
: m_iArrow{1}
, m_orientation{RIGHT}
{}

void
gamer::setStench(bool stench)
{
	m_sensors.Stench = stench;
}

void
gamer::setBreeze(bool breeze)
{
	m_sensors.Breeze = breeze;
}

void
gamer::setGlitter(bool glitter)
{
	m_sensors.Glitter = glitter;
}

void
gamer::setScream(bool scream)
{
	m_sensors.Scream = scream;
}

void
gamer::setBump(bool bump)
{
	m_sensors.Bump = bump;
}

bool
gamer::getStench()
{
	return m_sensors.Stench;
}

bool
gamer::getBreeze()
{
	return m_sensors.Breeze;
}

bool
gamer::getGlitter()
{
	return m_sensors.Glitter;
}

bool
gamer::getScream()
{
	return m_sensors.Scream;
}

bool
gamer::getBump()
{
	return m_sensors.Bump;
}

gamer::~gamer()
{}
