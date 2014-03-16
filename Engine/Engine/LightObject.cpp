/* LightObject.cpp ::: Luke Harper */

#include "LightObject.h"

LightObject::LightObject(): lightOn(true), WallObject()
{
}

LightObject::LightObject(float x, float z, WCHAR* textures[]): lightOn(true), WallObject(x,z,textures)
{
}

bool LightObject::doAction()
{
	wchar_t* outstring = L"TOGGLING LIGHT";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
	lightOn = !lightOn;
	return true;
}

bool LightObject::getStatus()
{
	return lightOn;
}