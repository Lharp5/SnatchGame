
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
	WallObject(float, float, WCHAR**);
	~WallObject();


	//light switch functions
	virtual void turnOn();
	virtual void turnOff();

	//lock controls function
	virtual void unlock();
	virtual void lock();

	//door type functions
	virtual void open();
	virtual void close();

};
#endif