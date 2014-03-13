
/* PlayerClass.h ::: Luke Harper */

#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

class PlayerClass
{
public:
	PlayerClass();
	~PlayerClass();

	int getXLocation();
	int getYLocation();

private:
	int xLocation;
	int yLocation;

};

#endif