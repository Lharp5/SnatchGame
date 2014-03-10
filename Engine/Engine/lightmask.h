#pragma once
#include <DirectXMath.h>
#include "vertextype.h"
#include "modelclass.h"
#include "gamemodel.h"
#include "quadModel.h"


#include <string>

using namespace DirectX;

class LightMask
{
public:
	LightMask(void);
	LightMask(float lengthX, float lengthY, XMFLOAT4 * pColor = 0);
	virtual ~LightMask(void);
	virtual void Translate(float deltaX, float deltaY, float deltaZ);
	virtual void RotateX(float radianAngle);
	virtual void RotateY(float radianAngle);
	virtual void RotateZ(float radianAngle);
	virtual void Shutdown();
	QuadModel* GetQuadModel();

protected:
	QuadModel* m_QuadModel;

};

