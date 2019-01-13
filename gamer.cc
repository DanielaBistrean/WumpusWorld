#include "gamer.h"

gamer::gamer(std::unique_ptr<agent>&& agent)
: m_iArrow{1}
, m_orientation{RIGHT}
, m_agent{std::move(agent)}
{}

orientation
gamer::getOrientation()
{
	return m_orientation;
}

actions
gamer::nextAction(const all_sensors& as, world& w)
{
	m_agent->nextAction(as, w);
}

void
gamer::setOrientation(orientation o)
{
	m_orientation = o;
}

void
gamer::setGold(bool gold)
{
	m_gold = gold;
}

bool
gamer::getGold()
{
	return m_gold;
}

void
gamer::setGamerAlive(bool alive)
{
	m_gamerAlive = alive;
}

bool
gamer::getGamerAlive()
{
	return m_gamerAlive;
}

void
gamer::setWumpusAlive(bool wumpus)
{
	m_wumpusAlive = wumpus;
}

bool
gamer::getWumpusAlive()
{
	return m_wumpusAlive;
}

void
gamer::setArrow(int arrow)
{
	m_iArrow = arrow;
}

int
gamer::getArrow()
{
	return m_iArrow;
}

void
gamer::setLastY(int ly)
{
	m_agent->setLastY(ly);
}

void
gamer::setLastX(int lx)
{
	m_agent->setLastX(lx);
}

gamer::~gamer()
{}
