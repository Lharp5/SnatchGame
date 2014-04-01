
/* FloorObject.h ::: Luke Harper */

#ifndef FLOOROBJECT_H
#define FLOOROBJECT_H

#include "gameobject.h"
#include "quadTexturedModel.h"
class FloorObject: public GameObject
{
public:
	FloorObject();
	FloorObject(float, float, WCHAR*);
	~FloorObject();

	/************
	*	Function:	CreateSource
	*	in:			x and y map positions of source
	*	Purpose:	To assign the source of the light.
	*************/
	void createSource(int, int);

	/************
	*	Function:	getSourceX
	*	out:		sourceX as int
	*	Purpose:	To get the X Location of the Source
	*************/
	int getSourceX();

	/************
	*	Function:	getSourceY
	*	out:		sourceY as int
	*	Purpose:	To get the Y Location of the Source
	*************/
	int getSourceY();

	/************
	*	Function:	isLit
	*	out:		boolean
	*	Purpose:	To see whether the floor is lit
	*************/
	bool isLit();

	/************
	*	Function:	toggleLight
	*	Purpose:	Turns the light either on or off
	*************/
	void toggleLight(bool);

	/************
	*	Function:	 setWinTile
	*	Purpose: to check whether it is the final tile.
	*************/
	void setWinTile();

private:

	//floor lit up or not?
	bool lit;

	

	//location of the source of lighting (the mechanism to turn off and/or on.)
	int sourceX;
	int sourceY;


};

#endif