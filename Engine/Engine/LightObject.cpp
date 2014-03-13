/* LightObject.cpp ::: Luke Harper */

#include "LightObject.h"

LightObject::LightObject(): lightOn(true), WallObject()
{
}

LightObject::LightObject(float x, float z, WCHAR* textures[]): lightOn(true), WallObject(x,z,textures)
{
}

void LightObject::doAction()
{
	lightOn = !lightOn;
}