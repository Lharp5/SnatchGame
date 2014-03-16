/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	Floorobject
*	Date:		feb. 21/14
**************************/

#include "floorobject.h"

FloorObject::FloorObject(float x, float z, WCHAR* textures):GameObject(x, -5.0f,z, new QuadTexturedModel(10.0f, 10.0f, textures))
{
	sourceX=-5;
	sourceY=-5;

	//turning it to the floor
	myModel->worldRotateX(XM_PIDIV2);
}

FloorObject::~FloorObject()
{
}

void FloorObject::createSource(int x, int y)
{
	sourceX = x;
	sourceY = y;

}

int FloorObject::getSourceX()
{
	return sourceX;
}

int FloorObject::getSourceY()
{
	return sourceY;
}

bool FloorObject::isLit()
{
	return lit;
}

void FloorObject::toggleLight(bool light)
{
	lit = light;
}