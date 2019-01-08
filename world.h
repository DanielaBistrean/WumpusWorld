#ifndef WORLD_H
#define WORLD_H 1

#include <memory>

#include "gamer.h"

// the world holds the player position and reference
class world
{
public:
	world(int x, int y);
	~world();
	void setUserPos(std::unique_ptr<gamer>&& gamer, int gamer_x, int gamer_y);

private:
	int m_x, m_y;
	int** m_matrix;
	int m_gamer_x, m_gamer_y;
	std::unique_ptr<gamer> m_gamer;
};

#endif
