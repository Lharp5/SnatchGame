/* DoorObject.cpp ::: Luke Harper */

#include "DoorObject.h"

DoorObject::DoorObject(): isOpen(true), finishedOpening(false), WallObject()
{
}

DoorObject::DoorObject(int xL, int yL, float x, float z, WCHAR* textures[]): lockX(xL), lockY(yL), isOpen(false), finishedOpening(false), WallObject(x,z,textures, 10.0f, 15.0f, 3.0f)
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

	//setRenderValue(false);

	if (!isOpen)
	{
		sound->PlayDesiredFile(3, false);
	}

	isOpen = true;
	
	return true;
}

bool DoorObject::getStatus()
{
 	return isOpen;
}