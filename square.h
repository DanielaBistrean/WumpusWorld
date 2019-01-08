#ifndef SQUARE_H
#define SQUARE_H 1

enum SquareType
{
	WUMPUS,
	PIT, 
	GOLD,
	GAMER,
	OK
};

class square
{
public:
	square(SquareType st);

private:
	SquareType m_type;
};

#endif
