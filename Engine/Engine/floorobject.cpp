/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	Floorobject
*	Date:		feb. 21/14
**************************/

#include "floorobject.h"

FloorObject::FloorObject(float x, float z, WCHAR* textures):GameObject(new QuadTexturedModel(10.0f, 10.0f, textures), x, -5.0f,z)
{
	sourceX=-5;
	sourceY=-5;

	myModel->worldRotateX(XM_PIDIV2);
}

FloorObject::~FloorObject()
{
}