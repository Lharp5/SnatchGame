
/* FloorObject.h ::: Luke Harper */

#ifndef FLOOROBJECT_H
#define FLOOROBJECT_H

#include "gameobject.h"

class FloorObject: public GameObject
{
public:
	FloorObject();
	FloorObject(GameModel*);
	~FloorObject();

private:

	//floor lit up or not?
	bool lit;

	//location of the source of lighting (the mechanism to turn off and/or on.)
	int sourceX;
	int sourceY;

};

#endif