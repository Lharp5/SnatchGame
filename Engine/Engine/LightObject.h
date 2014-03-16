/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	LightObject
*	Date:		Mar 13/14
**************************/

#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "WallObject.h"

class LightObject: public WallObject
{
public:
	LightObject();
	LightObject(float, float, WCHAR**);
	~LightObject();

	/*********** 
	*	Function:	Do Action
	*	Purpose:	To do the appropriate action when the player uses an action on the wall
	*	Additionally:	Will  turn light on/off
	*************/
	bool doAction();
	
	/**********
	*	Function:	getStatus
	*	Purpose:	to return whether lightswitch is turned on (true) or off.
	***********/
	bool getStatus();

private:
	bool lightOn;
};

#endif