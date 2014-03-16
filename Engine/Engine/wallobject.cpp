/* WallObject.CPP ::: Luke Harper */

#include "wallobject.h"

WallObject::WallObject(): GameObject()
{
}

WallObject::WallObject(float x, float z, WCHAR* textures[], float width, float height, float depth):GameObject(x*10, 2.0f,z*10, (new CubeTexturedModel(width, height, depth, textures)))
{
}

void WallObject::doAction()
{
}