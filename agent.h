#ifndef AGENT
#define AGENT 1

#include <deque>
#include <vector>
#include "square.h"
#include "world.h"

enum actions : int
{
	TURN_LEFT = 0,
	TURN_RIGHT,
	FORWARD,
	SHOOT,
	GRAB,
	CLIMB
};

class world;

class agent
{
public:
	actions nextAction(const all_sensors& as, world& w);
	void setLastX(int lx);
	int getLastX();
	void setLastY(int ly);
	int getLastY();

private:
	int m_lastX, m_lastY;
	std::deque<actions> m_stack;
	std::vector<std::pair<int,int>> m_path_home;
	actions printAndReturn();
};

#endif
