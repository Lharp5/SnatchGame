/* DoorObject.cpp ::: Luke Harper */

#include "DoorObject.h"

DoorObject::DoorObject(): isOpen(true), WallObject()
{
}

DoorObject::DoorObject(int xL, int yL, float x, float z, WCHAR* textures[]): lockX(xL), lockY(yL), isOpen(false), WallObject(x,z,textures, 10.0f, 15.0f, 3.0f)
{
}

bool DoorObject::doAction()
{
	wchar_t outstring[32];
	wsprintf(outstring, L"Opened Door: %d, %d\n", (int)xLocation, (int)zLocation);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
	isOpen = true;
	getModel()->setRenderVal(false);
	return true;
}

bool DoorObject::getStatus()
{
 	return isOpen;
}