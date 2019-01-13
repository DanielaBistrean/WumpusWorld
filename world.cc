#include <iostream>
#include <stdlib.h>

#include "world.h"
#include "agent.h"

world::world(int x, int y)
: m_x{x}
, m_y{y}
, m_gamer_x{1}
, m_gamer_y{1}
{
	m_matrix = new square*[x];

	for (int i = 0; i < x; i++)
	{
		m_matrix[i] = new square[y];
	}
}

bool
world::isWumpusAlive()
{
	return m_gamer->getWumpusAlive();
}

bool
world::hasGold()
{
	return m_gamer->getGold();
}

void
world::setUserPos(std::unique_ptr<gamer>&& gamer, int gamer_x, int gamer_y)
{
	m_gamer = std::move(gamer);
	m_gamer_x = gamer_x;
	m_gamer_y = gamer_y;
}

void
world::Print()
{
	std::cout << "World size = " << m_x << "x" << m_y << "\n";
	std::cout << "+";
	for (int x = 1; x <= m_x; x++)
	{
		std::cout << "---+";
	}
	std::cout << "\n";
	for (int y = m_y - 1; y >= 0; y--)
	{
		std::cout << "|";
		for (int x = 0; x < m_x; x++)
		{
			square& s = m_matrix[x][y];

			if ((x == m_gamer_x) && (y == m_gamer_y))
			{
				if (m_gamer->getOrientation() == UP)
				{
					std::cout << " ^ ";
				}
				else if (m_gamer->getOrientation() == DOWN)
				{
					std::cout << " v ";
				}
				else if (m_gamer->getOrientation() == LEFT)
				{
					std::cout << " < ";
				}
				else if (m_gamer->getOrientation() == RIGHT)
				{
					std::cout << " > ";
				}
			}
			else if (s.getVisited())
			{
				if (s.getType() == WUMPUS)
				{
					std::cout << " W ";
				}
				else if (s.getType() == PIT)
				{
					std::cout << " P ";
				}
				else if (s.getType() == GOLD)
				{
					std::cout << " G ";
				}
				else
				{
					std::cout << "   ";
				}
			}
			else
			{
				std::cout << " ? ";
			}
			std::cout << "|";
		}
		std::cout << "\n";
		std::cout << "|";

		for (int x = 0; x < m_x; x++)
		{
			square& s = m_matrix[x][y];

			if (s.getGuess().ok)
				std::cout << "OK |";
			else if (!s.getGuess().unknown)
			{
				if (s.getGuess().wumpus)
					std::cout << "W";
				else
					std::cout << " ";

				if (s.getGuess().pit)
					std::cout << "P";
				else
					std::cout << " ";
				std::cout << " |";
			}
			else
				std::cout << "   |";
			// std::cout << "   |";
		}

		std::cout << "\n";

		std::cout << "+";
		for (int x = 0; x < m_x; x++)
		{
			std::cout << "---+";
		}
		std::cout << std::endl;
	}

	std::cout << "Current score = " << GetScore() << "\n";
	std::cout << "Agent has gold = " << m_gamer->getGold() << ", agent has arrow = " << m_gamer->getArrow() << "\n";
}

bool
world::nextStep()
{
	square& s = m_matrix[m_gamer_x][m_gamer_y];

	actions a = m_gamer->nextAction(s.getSensor(), *this);

	numActions++;
	s.setBump(false);

	switch(a)
	{
		case FORWARD:
		{
			m_matrix[m_gamer_x][m_gamer_y].setVisited(true);
			m_gamer->setLastX(m_gamer_x);
			m_gamer->setLastY(m_gamer_y);
			if (m_gamer->getOrientation() == RIGHT)
			{
				if (m_gamer_x < m_x - 1)
				{
					m_gamer_x++;
				}
				else
				{
					s.setBump(true);
				}
			} else if (m_gamer->getOrientation() == UP)
			{
				if (m_gamer_y < m_y - 1)
				{
					m_gamer_y++;
				}
				else 
				{
					s.setBump(true);
				}
			}
			else if (m_gamer->getOrientation() == LEFT)
			{
				if (m_gamer_x > 0)
				{
					m_gamer_x--;
				}
				else
				{
					s.setBump(true);
				}
			}
			else if (m_gamer->getOrientation() == DOWN)
			{
				if (m_gamer_y > 0)
				{
					m_gamer_y--;
				}
				else
				{
					s.setBump(true);
				}
			}

			s.setVisited(true);

			square& n = m_matrix[m_gamer_x][m_gamer_y];

			if (n.getType() == PIT || n.getType() == WUMPUS)
			{
				std::cout << "It's over\n";
				m_gamer->setGamerAlive(false);
				return false;
			}

			break;
		}

		case TURN_LEFT:
		{
			if (m_gamer->getOrientation() == RIGHT)
			{
				m_gamer->setOrientation(UP);
			}
			else if (m_gamer->getOrientation() == UP)
			{
				m_gamer->setOrientation(LEFT);
			}
			else if (m_gamer->getOrientation() == LEFT)
			{
				m_gamer->setOrientation(DOWN);
			}
			else if (m_gamer->getOrientation() == DOWN)
			{
				m_gamer->setOrientation(RIGHT);
			}
			break;
		}

		case TURN_RIGHT:
		{
			if (m_gamer->getOrientation() == RIGHT)
			{
				m_gamer->setOrientation(DOWN);
			}
			else if (m_gamer->getOrientation() == UP)
			{
				m_gamer->setOrientation(RIGHT);
			}
			else if (m_gamer->getOrientation() == LEFT)
			{
				m_gamer->setOrientation(UP);
			}
			else if (m_gamer->getOrientation() == DOWN)
			{
				m_gamer->setOrientation(LEFT);
			}
			break;
		}

		case GRAB:
		{
			square& l = m_matrix[m_gamer_x][m_gamer_y];

			if ((! m_gamer->getGold()) && (m_matrix[m_gamer_x][m_gamer_y].getType() == GOLD))
			{
				m_gamer->setGold(true);
				l.setGlitter(false);
			}
			break;
		}
		case CLIMB:
		{
			if (m_gamer_x == 0 && m_gamer_y == 0)
			{
				if (m_gamer->getWumpusAlive() == false && m_gamer->getGold() == true)
				{
					std::cout << "You are the winner!\n";
				}
				return false;
			}
			break;
		}
		case SHOOT:
		{
			square& p = m_matrix[m_gamer_x][m_gamer_y];

			if (m_gamer->getArrow())
			{
				m_gamer->setArrow(0);

				if (m_gamer->getWumpusAlive())
				{
					if ((m_gamer->getOrientation() == RIGHT) && (m_gamer_x+1 < m_x) && (m_matrix[m_gamer_x+1][m_gamer_y].getType() == WUMPUS))
					{
						m_gamer->setWumpusAlive(false);
						p.setScream(true);
						m_matrix[m_gamer_x+1][m_gamer_y].setType(OK);
						setSpecialPos(WUMPUS, m_gamer_x+1, m_gamer_y, false);
					}
					if ((m_gamer->getOrientation() == UP) && (m_gamer_y+1 < m_y) && (m_matrix[m_gamer_x][m_gamer_y+1].getType() == WUMPUS))
					{
						m_gamer->setWumpusAlive(false);
						p.setScream(true);
						m_matrix[m_gamer_x][m_gamer_y+1].setType(OK);
						setSpecialPos(WUMPUS, m_gamer_x, m_gamer_y+1, false);
					}
					if ((m_gamer->getOrientation() == LEFT) && (m_gamer_x-1 < m_x) && (m_matrix[m_gamer_x-1][m_gamer_y].getType() == WUMPUS))
					{
						m_gamer->setWumpusAlive(false);
						p.setScream(true);
						m_matrix[m_gamer_x-1][m_gamer_y].setType(OK);
						setSpecialPos(WUMPUS, m_gamer_x-1, m_gamer_y, false);
					}
					if ((m_gamer->getOrientation() == DOWN) && (m_gamer_y-1 < m_y) && (m_matrix[m_gamer_x][m_gamer_y-1].getType() == WUMPUS))
					{
						m_gamer->setWumpusAlive(false);
						p.setScream(true);
						m_matrix[m_gamer_x][m_gamer_y-1].setType(OK);
						setSpecialPos(WUMPUS, m_gamer_x, m_gamer_y-1, false);
					}
				}
			}

			break;
		}
	}
	return true;
}

void
world::setSpecialPos(SquareType st, int x, int y, bool value)
{
	square& s = m_matrix[x][y];
	s.setType(st);

	if (st == GOLD)
	{
		s.setGlitter(value);
	}

	if (x + 1 < m_x)
	{
		if (st == PIT)
			m_matrix[x+1][y].setBreeze(value);
		// else if (st == GOLD)
		// 	m_matrix[x+1][y].setGlitter(true);
		else if (st == WUMPUS)
			m_matrix[x+1][y].setStench(value);
	}

	if (x - 1 >= 0)
	{
		if (st == PIT)
			m_matrix[x-1][y].setBreeze(value);
		// else if (st == GOLD)
		// 	m_matrix[x-1][y].setGlitter(true);
		else if (st == WUMPUS)
			m_matrix[x-1][y].setStench(value);
	}

	if (y + 1 < m_y)
	{
		if (st == PIT)
			m_matrix[x][y+1].setBreeze(value);
		// else if (st == GOLD)
		// 	m_matrix[x][y+1].setGlitter(true);
		else if (st == WUMPUS)
			m_matrix[x][y+1].setStench(value);
	}

	if (y - 1 >= 0)
	{
		if (st == PIT)
			m_matrix[x][y-1].setBreeze(value);
		// else if (st == GOLD)
		// 	m_matrix[x][y-1].setGlitter(true);
		else if (st == WUMPUS)
			m_matrix[x][y-1].setStench(value);
	}
}

int
world::GetScore()
{
	int score = 0;

	// -1 for each action
	score = score - numActions;

	if (!m_gamer->getArrow())
	{
		score = score - 10;
	}

	if (m_gamer->getGold())
	{
		score = score + 1000;
	}

	if (!m_gamer->getGamerAlive())
	{
		score = score - 1000;
	}

	return score;
}

int
world::getGamerX()
{
	return m_gamer_x;
}

int
world::getGamerY()
{
	return m_gamer_y;
}

bool
world::positionIsValid(int x, int y)
{
	if ((x < m_x && y < m_y) && (x >= 0 && y >= 0))
		return true;

	return false;
}

void
world::setGuessPos(SquareType st, int x, int y)
{
	square& s = m_matrix[x][y];
	guess g = s.getGuess();
	switch (st)
	{
		case WUMPUS:
			if (!g.wumpus_cleared)
			{
				g.wumpus = true;
				g.ok = false;
				g.unknown = false;
			}
			break;
		case PIT:
			if (!g.pit_cleared)
			{
				g.pit = true;
				g.ok = false;
				g.unknown = false;
			}
			break;
		case OK:
			g.ok = true;
			g.pit = false;
			g.wumpus = false;
			g.unknown = false;
			break;
		default:
			g.unknown = true;
			g.ok = false;
			g.pit = false;
			g.unknown = false;
			break;
	}
	s.setGuess(g);

}

void
world::clearGuessPos(SquareType st, int x, int y)
{
	square& s = m_matrix[x][y];
	guess g = s.getGuess();
	switch (st)
	{
		case WUMPUS:
			g.wumpus = false;
			g.wumpus_cleared = true;
			if (!g.pit)
				g.ok = true;
			break;
		case PIT:
			g.pit = false;
			g.pit_cleared = true;
			if (!g.wumpus)
				g.ok = true;
			break;
		default:
			g.unknown = true;
			g.ok = false;
			g.pit = false;
			g.unknown = false;
			break;
	}
	s.setGuess(g);
}

guess
world::getGuessPos(int x, int y)
{
	return m_matrix[x][y].getGuess(); 
}

bool
world::getVisitedPos(int x, int y)
{
	return m_matrix[x][y].getVisited();
}

void
world::setVisitedPos(bool visited, int x, int y)
{
	m_matrix[x][y].setVisited(true);
}

orientation
world::getGamerOrientation()
{
	return m_gamer->getOrientation();
}

world::~world()
{
	for (int i = 0; i < m_x; i++)
	{
		delete [] m_matrix[i];
	}
	delete [] m_matrix;
}
