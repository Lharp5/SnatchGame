/* WallObject.CPP ::: Luke Harper */

#include "wallobject.h"

WallObject::WallObject(): GameObject()
{
}

WallObject::WallObject(float x, float z, WCHAR* textures[]):GameObject((new CubeTexturedModel(10.0f, 15.0f, 10.0f, textures)), x*10, 2.0f,z*10)
{
}

void WallObject::doAction()
{
}