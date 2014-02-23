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

WallObject::WallObject(WALL_TYPE t, float x, float z):GameObject((new QuadTexturedModel(10.0f, 15.0f, L"../Engine/textures/wood_texture.dds")), x, 2.0f,z)
{
	myType = t;
}