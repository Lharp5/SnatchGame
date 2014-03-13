/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	DoorObject
*	Date:		Mar 13/14
**************************/

#ifndef DOOROBJECT_H
#define DOOROBJECT_H

#include "WallObject.h"

class DoorObject: public WallObject
{
public:
	DoorObject();
	DoorObject(int, int, float, float, WCHAR**);
	~DoorObject();

	/*********** 
	*	Function:	Do Action
	*	Purpose:	To do the appropriate action when the player uses an action on the wall
	*	Additionally:	Will  turn light on/off
	*************/
	void doAction();

private:
	bool isOpen;

	//co-ordinates on map of the door Lock, -1 if no lock.
	int lockX;
	int lockY;
};

#endif