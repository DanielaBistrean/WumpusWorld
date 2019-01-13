#ifndef GAMER_H
#define GAMER_H 1

#include <memory>

#include "agent.h"
#include "square.h"
#include "world.h"

enum orientation : int
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum actions : int;
class agent;
class world;

class gamer
{
public:
	gamer(std::unique_ptr<agent>&& agent);
	~gamer();
	orientation getOrientation();
	actions nextAction(const all_sensors& as, world& w);
	void setOrientation(orientation o);
	void setGold(bool gold);
	bool getGold();
	void setGamerAlive(bool alive);
	bool getGamerAlive();
	void setWumpusAlive(bool wumpus);
	bool getWumpusAlive();
	void setArrow(int arrow);
	int getArrow();
	void setLastY(int ly);
	void setLastX(int lx);

private:
	int m_iArrow = 1;
	orientation m_orientation;
	std::unique_ptr<agent> m_agent;
	bool m_gold = false;
	bool m_gamerAlive = true;
	bool m_wumpusAlive = true;
};

#endif
