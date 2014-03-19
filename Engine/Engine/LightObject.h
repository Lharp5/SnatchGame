/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	LightObject
*	Date:		Mar 13/14
**************************/

#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "WallObject.h"
#include "cubemodel.h"

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

	virtual ArrayList<GameModel> GetGameModels();

	/***********
	*	Function:	rotate
	*	Purpose:	To rotate this object about the Y axis
	*	Note:		Only works once, as the purpose is for placement of object in world.
					Results will be odd if used more than once.
	************/
	virtual void rotate(float);

private:
	CubeTexturedModel* wall;
	CubeModel* base;
	CubeModel* flickSwitch;
	ArrayList<GameModel> gameModels;
	bool lightOn;
};

#endif