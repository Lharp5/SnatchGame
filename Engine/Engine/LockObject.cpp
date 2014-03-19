/* LockObject.cpp ::: Luke Harper */

#include "LockObject.h"

LockObject::LockObject(): isLocked(true), WallObject()
{
}

LockObject::LockObject(float x, float z, WCHAR* textures[]): isLocked(true), WallObject(x,z)
{
	wall = new CubeTexturedModel(10.0f, 15.0f, 10.0f, textures);
	wall->worldTranslate(x*10.0f, 2.0f, z*10.0f);
	XMFLOAT4 baseColor[] = { XMFLOAT4(0.95f, 0.95f, 0.95f, 1.0f),
							XMFLOAT4(0.95f, 0.95f, 0.95f, 1.0f),
							XMFLOAT4(0.95f, 0.95f, 0.95f, 1.0f),
							XMFLOAT4(0.95f, 0.95f, 0.95f, 1.0f),
							XMFLOAT4(0.95f, 0.95f, 0.95f, 1.0f),
							XMFLOAT4(0.95f, 0.95f, 0.95f, 1.0f)};
	base = new CubeModel(2.0f, 2.5f, 0.5f, baseColor);
	base->worldTranslate(x*10.0f, 2.0f, z*10.0f + 5.0f);
	XMFLOAT4 switchColor[] = { XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
								XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
								XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
								XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
								XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
								XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) };
	flickSwitch = new CubeModel(0.5f, 0.5f, 1.0f, switchColor);
	flickSwitch->worldTranslate(x*10.0f, 2.0f, z*10.0f + 5.0f);
}

ArrayList<GameModel> LockObject::GetGameModels()
{
	ArrayList<GameModel> list;
	list.add(wall);
	list.add(base);
	list.add(flickSwitch);
	return list;
}

void LockObject::rotate(float angle)
{
	float x = sin(angle)*5.0f;
	float y = cos(angle)*5.0f;
	wall->worldRotateY(angle);
	base->worldTranslate(0.0f, 0.0f, -5.0f);
	base->worldRotateY(angle);
	base->worldTranslate(x, 0.0f, y);
	flickSwitch->worldTranslate(0.0f, 0.0f, -5.0f);
	flickSwitch->worldRotateY(angle);
	flickSwitch->worldTranslate(x, 0.0f, y);
}

bool LockObject::doAction()
{
	isLocked = !isLocked;
	return true;
}