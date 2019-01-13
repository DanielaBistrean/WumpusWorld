#include <iostream>
#include <memory>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
#include <utility>
#include <vector>

#include "agent.h"

actions
agent::nextAction(const all_sensors& as, world& w)
{

	std::cout << "[Stench=" << as.Stench << ", "
		 << "Breeze=" << as.Breeze << ", "
		 << "Glitter=" << as.Glitter << ", "
		 << "Bump=" << as.Bump << ", "
		 << "Scream=" << as.Scream << "]\n";

	bool danger = false;
	int gamerX = w.getGamerX();
	int gamerY = w.getGamerY();
	w.setGuessPos(OK, gamerX, gamerY);

	int num_wumpus = 0;
	orientation relWumpus;
	if (as.Stench)
	{

		// std::cout << "VALID======" << w.positionIsValid(gamerX + 1, gamerY) << "\n";
		// std::cout << "ISLAST=====" << ((gamerX + 1) != m_lastX && gamerY != m_lastY) << "\n";
		// std::cout << "NOTVISITED=" << !w.getVisitedPos(gamerX + 1,gamerY) << "\n";
		if (w.positionIsValid(gamerX + 1, gamerY) && ((gamerX + 1) != m_lastX || gamerY != m_lastY) && !w.getVisitedPos(gamerX + 1,gamerY))
		{
			if (w.getGuessPos(gamerX+1, gamerY).wumpus)
			{
				num_wumpus++;
				relWumpus = RIGHT;
			}
			else
				w.setGuessPos(WUMPUS, gamerX+1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY+1) && (gamerX != m_lastX || gamerY+1 != m_lastY) && !w.getVisitedPos(gamerX,gamerY+1))
		{
			if (w.getGuessPos(gamerX, gamerY+1).wumpus)
			{
				num_wumpus++;
				relWumpus = UP;
			}
			else
				w.setGuessPos(WUMPUS, gamerX, gamerY+1);
		}

		if (w.positionIsValid(gamerX - 1, gamerY) && ((gamerX - 1) != m_lastX || gamerY != m_lastY) && !w.getVisitedPos(gamerX - 1,gamerY))
		{
			if (w.getGuessPos(gamerX-1, gamerY).wumpus)
			{
				num_wumpus++;
				relWumpus = LEFT;
			}
			else
				w.setGuessPos(WUMPUS, gamerX-1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY-1) && (gamerX != m_lastX || gamerY-1 != m_lastY) && !w.getVisitedPos(gamerX,gamerY-1))
		{
			if (w.getGuessPos(gamerX, gamerY-1).wumpus)
			{
				num_wumpus++;
				relWumpus = DOWN;
			}
			else
			w.setGuessPos(WUMPUS, gamerX, gamerY-1);
		}

		if (num_wumpus == 1)
		{
			orientation o = w.getGamerOrientation();

			if (relWumpus == o)
				m_stack.push_back(SHOOT);
			else if ((o == UP && relWumpus == DOWN) ||
				(o == DOWN && relWumpus == UP) ||
				(o == LEFT && relWumpus == RIGHT) ||
				(o == RIGHT && relWumpus == LEFT))
			{
				m_stack.push_back(TURN_RIGHT);
				m_stack.push_back(TURN_RIGHT);
				m_stack.push_back(SHOOT);
			}
			else if ((o == UP && relWumpus == RIGHT) ||
				(o == RIGHT && relWumpus == DOWN) ||
				(o == DOWN && relWumpus == LEFT) ||
				(o == LEFT && relWumpus == UP))
			{
				m_stack.push_back(TURN_RIGHT);
				m_stack.push_back(SHOOT);
			}
			else
			{
				m_stack.push_back(TURN_LEFT);
				m_stack.push_back(SHOOT);
			}

			return printAndReturn();
		}

		danger = true;
	}
	else
	{
		if (w.positionIsValid(gamerX + 1, gamerY) && ((gamerX + 1) != m_lastX || gamerY != m_lastY) && !w.getVisitedPos(gamerX + 1,gamerY))
		{
			// std::cout << "SET GUESS WUMPUS RIGHT\n";
			w.clearGuessPos(WUMPUS, gamerX+1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY+1) && (gamerX != m_lastX || gamerY+1 != m_lastY) && !w.getVisitedPos(gamerX,gamerY+1))
		{
			// std::cout << "SET GUESS WUMPUS UP\n";
			w.clearGuessPos(WUMPUS, gamerX, gamerY+1);
		}

		if (w.positionIsValid(gamerX - 1, gamerY) && ((gamerX - 1) != m_lastX || gamerY != m_lastY) && !w.getVisitedPos(gamerX - 1,gamerY))
		{
			// std::cout << "SET GUESS WUMPUS LEFT\n";
			w.clearGuessPos(WUMPUS, gamerX-1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY-1) && (gamerX != m_lastX || gamerY-1 != m_lastY) && !w.getVisitedPos(gamerX,gamerY-1))
		{
			// std::cout << "SET GUESS WUMPUS DOWN\n";
			w.clearGuessPos(WUMPUS, gamerX, gamerY-1);
		}	
	}

	if (as.Breeze)
	{
		if (w.positionIsValid(gamerX+1, gamerY) && (gamerX+1 != m_lastX || gamerY != m_lastY) && !w.getVisitedPos(gamerX+1,gamerY))
		{
			w.setGuessPos(PIT, gamerX+1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY+1) && (gamerX != m_lastX || gamerY+1 != m_lastY) && !w.getVisitedPos(gamerX,gamerY+1))
		{
			w.setGuessPos(PIT, gamerX, gamerY+1);
		}

		if (w.positionIsValid(gamerX-1, gamerY) && (gamerX-1 != m_lastX || gamerY != m_lastY) && !w.getVisitedPos(gamerX-1,gamerY))
		{
			w.setGuessPos(PIT, gamerX-1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY-1) && (gamerX != m_lastX || gamerY-1 != m_lastY) && !w.getVisitedPos(gamerX,gamerY-1))
		{
			w.setGuessPos(PIT, gamerX, gamerY-1);
		}
		danger = true;
	}
	else
	{
		if (w.positionIsValid(gamerX+1, gamerY) && (gamerX+1 != m_lastX || gamerY != m_lastY) && !w.getVisitedPos(gamerX+1,gamerY))
		{
			w.clearGuessPos(PIT, gamerX+1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY+1) && (gamerX != m_lastX || gamerY+1 != m_lastY) && !w.getVisitedPos(gamerX,gamerY+1))
		{
			w.clearGuessPos(PIT, gamerX, gamerY+1);
		}

		if (w.positionIsValid(gamerX-1, gamerY) && (gamerX-1 != m_lastX || gamerY != m_lastY) && !w.getVisitedPos(gamerX-1,gamerY))
		{
			w.clearGuessPos(PIT, gamerX-1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY-1) && (gamerX != m_lastX || gamerY-1 != m_lastY) && !w.getVisitedPos(gamerX,gamerY-1))
		{
			w.clearGuessPos(PIT, gamerX, gamerY-1);
		}	
	}

	if (!danger)
	{
		if (w.positionIsValid(gamerX+1, gamerY))
		{
			w.setGuessPos(OK, gamerX+1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY+1))
		{
			w.setGuessPos(OK, gamerX, gamerY+1);
		}

		if (w.positionIsValid(gamerX-1, gamerY))
		{
			w.setGuessPos(OK, gamerX-1, gamerY);
		}

		if (w.positionIsValid(gamerX, gamerY-1))
		{
			w.setGuessPos(OK, gamerX, gamerY-1);
		}
	}

	if (!m_stack.empty())
	{
		return printAndReturn();
	}

	if (w.hasGold() && !w.isWumpusAlive())
	{
		std::pair<int,int> current = std::make_pair(gamerX, gamerY);
		orientation o = w.getGamerOrientation();
		while (!m_path_home.empty())
		{
			std::pair<int,int> nextPos = m_path_home.back();
			m_path_home.pop_back();

			orientation relNext;

			if (nextPos.first == current.first)
			{
				if (nextPos.second < current.second)
					relNext = DOWN;
				else
					relNext = UP;
			}
			else
			{
				if (nextPos.first < current.first)
					relNext = LEFT;
				else
					relNext = RIGHT;
			}

			if (relNext == o)
				m_stack.push_back(FORWARD);
			else if ((o == UP && relNext == DOWN) ||
				(o == DOWN && relNext == UP) ||
				(o == LEFT && relNext == RIGHT) ||
				(o == RIGHT && relNext == LEFT))
			{
				m_stack.push_back(TURN_RIGHT);
				m_stack.push_back(TURN_RIGHT);
				m_stack.push_back(FORWARD);
			}
			else if ((o == UP && relNext == RIGHT) ||
				(o == RIGHT && relNext == DOWN) ||
				(o == DOWN && relNext == LEFT) ||
				(o == LEFT && relNext == UP))
			{
				m_stack.push_back(TURN_RIGHT);
				m_stack.push_back(FORWARD);
			}
			else
			{
				m_stack.push_back(TURN_LEFT);
				m_stack.push_back(FORWARD);
			}

			current = nextPos;
			o = relNext;		
		}

		m_stack.push_back(CLIMB);
		return printAndReturn();
	}

	if (as.Glitter)
	{
		m_stack.push_back(GRAB);
		return printAndReturn();
	}

	std::vector <std::pair <int, int>> next;
	if (w.positionIsValid(gamerX+1, gamerY) && w.getGuessPos(gamerX+1, gamerY).ok)
	{
		next.push_back(std::make_pair(gamerX+1, gamerY));
	}

	if (w.positionIsValid(gamerX, gamerY+1) && w.getGuessPos(gamerX, gamerY+1).ok)
	{
		next.push_back(std::make_pair(gamerX, gamerY+1));
	}

	if (w.positionIsValid(gamerX-1, gamerY) && w.getGuessPos(gamerX-1, gamerY).ok)
	{
		next.push_back(std::make_pair(gamerX-1, gamerY));
	}

	if (w.positionIsValid(gamerX, gamerY-1) && w.getGuessPos(gamerX, gamerY-1).ok)
	{
		next.push_back(std::make_pair(gamerX, gamerY-1));
	}

	std::pair<int, int> nextPos;
	bool found = false;
	if (next.empty())
		return CLIMB;
	
	for (std::pair<int, int> pos : next)
	{
		if (!w.getVisitedPos(pos.first, pos.second))
		{
			nextPos = pos;
			found = true;
			break;
		}
	}

	if (!found)
	{
		int index = rand() % next.size();
		nextPos = next[index];
	}
	
	// std::cout << "nextPos: " << nextPos.first << " , " << nextPos.second << "\n";
	orientation o = w.getGamerOrientation();
	orientation relNext;

	if (nextPos.first == gamerX)
	{
		if (nextPos.second < gamerY)
			relNext = DOWN;
		else
			relNext = UP;
	}
	else
	{
		if (nextPos.first < gamerX)
			relNext = LEFT;
		else
			relNext = RIGHT;
	}

	// std::cout << "player orientation: " << o << "\n";
	// std::cout << "relNext orientation: " << relNext << "\n";

	if (relNext == o)
		m_stack.push_back(FORWARD);
	else if ((o == UP && relNext == DOWN) ||
		(o == DOWN && relNext == UP) ||
		(o == LEFT && relNext == RIGHT) ||
		(o == RIGHT && relNext == LEFT))
	{
		m_stack.push_back(TURN_RIGHT);
		m_stack.push_back(TURN_RIGHT);
		m_stack.push_back(FORWARD);
	}
	else if ((o == UP && relNext == RIGHT) ||
		(o == RIGHT && relNext == DOWN) ||
		(o == DOWN && relNext == LEFT) ||
		(o == LEFT && relNext == UP))
	{
		m_stack.push_back(TURN_RIGHT);
		m_stack.push_back(FORWARD);
	}
	else
	{
		m_stack.push_back(TURN_LEFT);
		m_stack.push_back(FORWARD);
	}

	std::pair<int, int> current = std::make_pair(gamerX, gamerY);
	auto it = std::find(m_path_home.begin(), m_path_home.end(), nextPos);
	if (it != m_path_home.end())
	{
		while (it != m_path_home.end())
			it = m_path_home.erase(it);
	}
	else
		m_path_home.push_back(current);

	return printAndReturn();
}

actions
agent::printAndReturn()
{
	// sleep(1);
	actions a = m_stack.front();
	m_stack.pop_front();
	std::cout << "Action: " << a << "\n";
	std::cout << "Planned:";
	for (actions b : m_stack)
	{
		std::cout << " " << b;
	}
	std::cout << "\n";
	std::cout << "PATH HOME:";
	for (auto b : m_path_home)
	{
		std::cout << " (" << b.first << "," << b.second << ")";
	}
	std::cout << "\n";
	return a;

}

void
agent::setLastX(int lx)
{
	m_lastX = lx;
}

int
agent::getLastX()
{
	return m_lastX;
}

void
agent::setLastY(int ly)
{
	m_lastY = ly;
}

int
agent::getLastY()
{
	return m_lastY;
}



