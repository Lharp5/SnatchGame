/* LockObject.cpp ::: Luke Harper */

#include "LockObject.h"

LockObject::LockObject(): isLocked(true), WallObject()
{
}

LockObject::LockObject(float x, float z, WCHAR* textures[]): isLocked(true), WallObject(x,z,textures)
{
}

bool LockObject::doAction()
{
	isLocked = !isLocked;
	return true;
}