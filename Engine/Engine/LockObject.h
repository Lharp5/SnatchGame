/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	LockObject
*	Date:		Mar 13/14
**************************/

#ifndef LOCKOBJECT_H
#define LOCKOBJECT_H

#include "WallObject.h"
#include "cubemodel.h"

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

	virtual ArrayList<GameModel> GetGameModels();

	/***********
	*	Function:	rotate
	*	Purpose:	To rotate this object about the Y axis
	*	Note:		Only works once, as the purpose is for placement of object in world.
					Results will be odd if used more than once.
	************/
	virtual void rotate(float);

	virtual bool IsLocked();

private:
	CubeTexturedModel* wall;
	CubeModel* base;
	CubeModel* flickSwitch;
	float rotateAngle;
	ArrayList<GameModel> gameModels;
	bool isLocked;
};

#endif