/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	wallObject
*	Date:		feb. 22/14
**************************/

#include "wallobject.h"

WallObject::WallObject()
{
}

WallObject::WallObject(float x, float z, WCHAR* textures[]):GameObject((new CubeTexturedModel(10.0f, 15.0f, 10.0f, textures)), x*10, 2.0f,z*10)
{
}

//light switch functions
	void WallObject::turnOn()
	{
	}
	void WallObject::turnOff()
	{
	}

	//lock controls function
	void WallObject::unlock()
	{
	}
	void WallObject::lock()
	{
	}

	//door type functions
	void WallObject::open()
	{
	}
	void WallObject::close()
	{
	}