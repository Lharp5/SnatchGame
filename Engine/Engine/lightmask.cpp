#include "gamemodel.h"
#include "modelclass.h"
#include "quadmodel.h"
#include "lightmask.h"


LightMask::LightMask(void)
{
	m_QuadModel = new QuadModel(1.0f, 1.0f, &XMFLOAT4(0.0f, 0.5f, 1.0f, 0.1f));
}

LightMask::LightMask(float lengthX, float lengthY, XMFLOAT4 * pColor)
{
	m_QuadModel = new QuadModel(lengthX, lengthY, pColor);
}

LightMask::~LightMask(void)
{
}

void LightMask::Translate(float deltaX, float deltaY, float deltaZ)
{
	m_QuadModel->orientTranslate(deltaX, deltaY, deltaZ);
}

void LightMask::RotateX(float radianAngle)
{
	Translate(0.0f, 0.0f, -0.1f);
	m_QuadModel->orientRotateX(radianAngle);
	Translate(0.0f, 0.0f, 0.1f);
}

void LightMask::RotateY(float radianAngle)
{
	Translate(0.0f, 0.0f, -0.1f);
	m_QuadModel->orientRotateY(radianAngle);
	Translate(0.0f, 0.0f, 0.1f);
}

void LightMask::RotateZ(float radianAngle)
{
	Translate(0.0f, 0.0f, -0.1f);
	m_QuadModel->orientRotateZ(radianAngle);
	Translate(0.0f, 0.0f, 0.1f);
}

QuadModel* LightMask::GetQuadModel()
{
	return m_QuadModel;
}

void LightMask::Shutdown()
{
	if (m_QuadModel)
	{
		m_QuadModel->Shutdown();
		delete m_QuadModel;
		m_QuadModel = 0;
	}

}
