
/* WallObject.h ::: Luke Harper */



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
	WallObject(WALL_TYPE, float, float, WCHAR**);
	~WallObject();


	//light switch functions
	void turnOn();
	void turnOff();

	//lock controls function
	void unLock();
	void lock();

	//door type functions
	void open();
	void close();

private:
	bool lightOn;
	bool doorLock;
	WALL_TYPE myType;

};
#endif