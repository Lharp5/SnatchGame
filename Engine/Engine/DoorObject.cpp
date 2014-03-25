/* DoorObject.cpp ::: Luke Harper */

#include "DoorObject.h"

DoorObject::DoorObject(): isOpen(true), WallObject()
{
}

DoorObject::DoorObject(int xL, int yL, float x, float z, WCHAR* textures[]): lockX(xL), lockY(yL), isOpen(false), WallObject(x,z,textures, 10.0f, 15.0f, 3.0f)
{
}

DoorObject::~DoorObject()
{
	shutdown();
}

bool DoorObject::doAction()
{
	wchar_t* outstring = L"Opened Door";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	isOpen = true;
	//setRenderValue(false);

	sound->PlayDesiredFile(2, false);
	
	return true;
}

bool DoorObject::getStatus()
{
 	return isOpen;
}