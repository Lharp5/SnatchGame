/*	PlayerClass ::: LukeHarper	*/

#include "PlayerClass.h"

PlayerClass::PlayerClass()
{
}
PlayerClass::~PlayerClass()
{
}


void PlayerClass::setPosition(int x, int y)
{
	xLocation =x;
	yLocation =y;
}
int PlayerClass::getXLocation()
{
	return xLocation;
}
int PlayerClass::getYLocation()
{
	return yLocation;
}