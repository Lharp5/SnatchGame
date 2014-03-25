/* LockObject.cpp ::: Luke Harper */

#include "LockObject.h"

LockObject::LockObject(): isLocked(true), WallObject()
{
}

LockObject::LockObject(float x, float z, WCHAR* textures[]): isLocked(true), WallObject(x,z)
{
	wall = new CubeTexturedModel(10.0f, 15.0f, 10.0f, textures);
	wall->worldTranslate(x*10.0f, 2.0f, z*10.0f);
	XMFLOAT4 color[] = { XMFLOAT4(0.45f, 0.45f, 0.45f, 1.0f),
							XMFLOAT4(0.45f, 0.45f, 0.45f, 1.0f),
							XMFLOAT4(0.40f, 0.40f, 0.40f, 1.0f),
							XMFLOAT4(0.40f, 0.40f, 0.40f, 1.0f),
							XMFLOAT4(0.45f, 0.45f, 0.45f, 1.0f),
							XMFLOAT4(0.35f, 0.35f, 0.35f, 1.0f)};
	base = new CubeModel(1.0f, 1.0f, 1.0f, color);
	base->worldTranslate(x*10.0f, 2.0f, z*10.0f + 5.0f);
	flickSwitch = new CubeModel(2.5f, 0.5f, 0.25f, color);
	flickSwitch->worldTranslate(x*10.0f - 1.25f, 2.0f, z*10.0f + 5.25f);
	rotateAngle = 0;
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
	rotateAngle = angle;
	float x = sin(angle)*5.0f;
	float y = cos(angle)*5.0f;
	base->worldTranslate(0.0f, 0.0f, -5.0f);
	base->orientRotateY(angle);
	base->worldTranslate(x, 0.0f, y);
	x = sin(angle)*5.25f;
	y = cos(angle)*5.25f;
	flickSwitch->worldTranslate(1.25f, 0.0f, -5.25f);
	flickSwitch->orientRotateY(angle);
	if (angle == XM_PIDIV2)
		flickSwitch->worldTranslate(x, 0.0f, y + 1.25f);
	else if (angle == XM_PI)
		flickSwitch->worldTranslate(x + 1.25f, 0.0f, y);
	else if (angle == XM_PI + XM_PIDIV2)
		flickSwitch->worldTranslate(x, 0.0f, y - 1.25f);
}

bool LockObject::doAction()
{
	if (isLocked)
	{
		if (rotateAngle == 0)
		{
			base->orientRotateZ(XM_PIDIV4);
			flickSwitch->worldTranslate(1.25f, 0.0f, 0.0f);
			flickSwitch->worldRotateZ(XM_PIDIV4);
			flickSwitch->worldTranslate(-(float)sqrt(1.25), -(float)sqrt(1.25), 0.0f);
		}
		else if (rotateAngle == XM_PIDIV2)
		{
			base->orientRotateX(XM_PIDIV4);
			flickSwitch->worldTranslate(0.0f, 0.0f, -1.25f);
			flickSwitch->worldRotateX(XM_PIDIV4);
			flickSwitch->worldTranslate(0.0f, -(float)sqrt(1.25), (float)sqrt(1.25));
		}
		else if (rotateAngle == XM_PI)
		{
			base->orientRotateZ(-XM_PIDIV4);
			flickSwitch->worldTranslate(-1.25f, 0.0f, 0.0f);
			flickSwitch->worldRotateZ(-XM_PIDIV4);
			flickSwitch->worldTranslate((float)sqrt(1.25), -(float)sqrt(1.25), 0.0f);
		}
		else if (rotateAngle == XM_PI + XM_PIDIV2)
		{
			base->orientRotateX(-XM_PIDIV4);
			flickSwitch->worldTranslate(0.0f, 0.0f, 1.25f);
			flickSwitch->worldRotateX(-XM_PIDIV4);
			flickSwitch->worldTranslate(0.0f, -(float)sqrt(1.25), -(float)sqrt(1.25));
		}
		sound->PlayDesiredFile(6, false);
		isLocked = !isLocked;
	}
	return true;
}