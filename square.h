#ifndef SQUARE_H
#define SQUARE_H 1

enum SquareType
{
	WUMPUS,
	PIT, 
	GOLD,
	UNKNOWN,
	OK
};

struct guess
{
	guess();
	bool wumpus;
	bool pit;
	bool unknown;
	bool ok;
	bool wumpus_cleared;
	bool pit_cleared;
};

struct all_sensors
{
	all_sensors();
	bool Stench;
	bool Breeze;
	bool Glitter;
	bool Scream;
	bool Bump;
};

class square
{
public:
	square(SquareType st = OK);
	void setStench(bool stench);
	void setBreeze(bool breeze);
	void setGlitter(bool glitter);
	void setScream(bool scream);
	void setBump(bool bump);
	bool getStench();
	bool getBreeze();
	bool getGlitter();
	bool getScream();
	bool getBump();
	bool getVisited();
	void setVisited(bool visited);
	SquareType getType();
	void setType(SquareType st);
	all_sensors getSensor();
	void setGuess(guess g);
	guess getGuess();

private:
	SquareType m_type;
	all_sensors m_sensors;
	bool m_visited = false;
	guess m_guess;
};

#endif
