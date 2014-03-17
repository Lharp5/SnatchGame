/* DoorObject.cpp ::: Luke Harper */

#include "DoorObject.h"

DoorObject::DoorObject(): isOpen(true), WallObject()
{
}

DoorObject::DoorObject(int xL, int yL, float x, float z, WCHAR* textures[]): lockX(xL), lockY(yL), isOpen(true), WallObject(x,z,textures, 10.0f, 15.0f, 3.0f)
{
}

bool DoorObject::doAction()
{
	wchar_t* outstring = L"Opened Door\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
	isOpen = true;
	GameObject::getModel()->setRenderVal(false);
	return true;
	//change
}

bool DoorObject::getStatus()
{
	return isOpen;
}