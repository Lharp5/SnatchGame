/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	LockObject
*	Date:		Mar 13/14
**************************/

#ifndef LOCKOBJECT_H
#define LOCKOBJECT_H

#include "WallObject.h"

class LockObject: public WallObject
{
public:
	LockObject();
	LockObject(float, float, WCHAR**);
	~LockObject();

	/*********** 
	*	Function:	Do Action
	*	Purpose:	To do the appropriate action when the player uses an action on the wall
	*	Additionally:	Will  lock/unlock
	*************/
	bool doAction();

private:
	bool isLocked;
};

#endif