/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	DoorObject
*	Date:		Mar 13/14
**************************/

#ifndef DOOROBJECT_H
#define DOOROBJECT_H

#include "WallObject.h"
#include "LockObject.h"

class DoorObject: public WallObject
{
public:
	DoorObject();
	DoorObject(int, int, float, float, WCHAR**);
	~DoorObject();

	virtual void createLock(LockObject*);
	virtual LockObject* getLock();

	/*********** 
	*	Function:	Do Action
	*	Purpose:	To do the appropriate action when the player uses an action on the wall
	*	Additionally:	Will  turn light on/off
	*************/
	bool doAction();
	bool getStatus();
	bool finishedOpening;
private:
	bool isOpen;

	//co-ordinates on map of the door Lock, -1 if no lock.
	int lockX;
	int lockY;
	LockObject* lock;
};

#endif