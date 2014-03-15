/* DoorObject.cpp ::: Luke Harper */

#include "DoorObject.h"

DoorObject::DoorObject(): isOpen(true), WallObject()
{
}

DoorObject::DoorObject(int xL, int yL, float x, float z, WCHAR* textures[]): lockX(xL), lockY(yL), isOpen(true), WallObject(x,z,textures, 10.0f, 15.0f, 3.0f)
{
}

void DoorObject::doAction()
{
	isOpen = !isOpen;
}