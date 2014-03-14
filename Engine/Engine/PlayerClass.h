
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

	/************
	*	Function:	setPosition
	*	in:			position of where the player is.
	*	Purpose:	to set the player position in the world.
	************/
	void setPosition(int, int);


private:
	int xLocation;
	int yLocation;

};

#endif