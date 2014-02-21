/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	Floorobject
*	Date:		feb. 21/14
**************************/

#include "floorobject.h"

FloorObject::FloorObject(float x, float z):GameObject((new QuadTexturedModel(10.0f, 10.0f, L"../Engine/textures/die1.dds")), x, -5.0f,z)
{
	sourceX=-5;
	sourceY=-5;

	myModel->worldRotateX(XM_PIDIV2);
}

FloorObject::~FloorObject()
{
}