
/* FloorObject.h ::: Luke Harper */

#ifndef FLOOROBJECT_H
#define FLOOROBJECT_H

#include "gameobject.h"
#include "quadTexturedModel.h"
class FloorObject: public GameObject
{
public:
	FloorObject();
	FloorObject(float, float);
	~FloorObject();

	void checkSource();

private:

	//floor lit up or not?
	bool lit;

	//location of the source of lighting (the mechanism to turn off and/or on.)
	int sourceX;
	int sourceY;


};

#endif