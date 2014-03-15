/* WallObject.CPP ::: Luke Harper */

#include "wallobject.h"

WallObject::WallObject(): GameObject()
{
}

WallObject::WallObject(float x, float z, WCHAR* textures[], float width, float height, float depth):GameObject((new CubeTexturedModel(width, height, depth, textures)), x*10, 2.0f,z*10)
{
}

void WallObject::doAction()
{
}