
/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	wallObject
*	Date:		feb. 22/14
**************************/

#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "gameobject.h"
#include "worldDefs.h"
#include "quadTexturedModel.h"
#include "cubeTexturedModel.h"

class WallObject: public  GameObject
{
public:
	WallObject();
	WallObject(float, float, WCHAR**);
	~WallObject();

	/*********** 
	*	Function:	Do Action
	*	Purpose:	To do the appropriate action when the player uses an action on the wall
	*	Additionally:	Implementation will call either light, door, or lock functions.
	*************/
	virtual void doAction();
};
#endif