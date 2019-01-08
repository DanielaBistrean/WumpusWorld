#include "world.h"

world::world(int x, int y)
: m_x{x}
, m_y{y}
, m_gamer_x{1}
, m_gamer_y{1}
{
	m_matrix = new int*[x];

	for (int i = 0; i < x; i++)
	{
		m_matrix[i] = new int[y];
	}
}

void
world::setUserPos(std::unique_ptr<gamer>&& gamer, int gamer_x, int gamer_y)
{
	m_gamer = std::move(gamer);
	m_gamer_x = gamer_x;
	m_gamer_y = gamer_y;

}

world::~world()
{
	for (int i = 0; i < m_x; i++)
	{
		delete [] m_matrix[i];
	}
	delete [] m_matrix;
}
