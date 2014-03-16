/* WallObject.CPP ::: Luke Harper */

#include "wallobject.h"

WallObject::WallObject(): GameObject()
{
}

WallObject::WallObject(float x, float z, WCHAR* textures[], float width, float height, float depth):GameObject(x, 2.0f,z, (new CubeTexturedModel(width, height, depth, textures)))
{
}

bool WallObject::doAction()
{
	return false;
}