#ifndef GAMER_H
#define GAMER_H 1

enum orientation
{
	LEFT,
	RIGHT,
	UP,
	DOWN
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

class gamer
{
public:
	gamer();
	~gamer();
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

private:
	int m_iArrow;
	orientation m_orientation;
	all_sensors m_sensors;
	
};

#endif
