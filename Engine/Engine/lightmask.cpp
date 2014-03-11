#include "gamemodel.h"
#include "modelclass.h"
#include "quadmodel.h"
#include "lightmask.h"


LightMask::LightMask(XMFLOAT3 camPos)
{
	camPosition = camPos;
	for (int i = 0; i < 6; i++)
	{
		m_faces[i] = new QuadTexturedModel(0.4f, 0.4f, L"../Engine/textures/LightMask.dds");
		switch (i)
		{
		case 0:
			m_faces[i]->orientTranslate(0.0f, 0.0f, 0.2f - 20.0f);
			break;
		case 1:
			m_faces[i]->orientTranslate(0.0f, 0.0f, -0.2f - 20.0f);
			m_faces[i]->orientRotateY(XM_PI);
			break;
		case 2:
			m_faces[i]->orientTranslate(0.0f, 0.2f, 0.0f - 20.0f);
			m_faces[i]->orientRotateX(-XM_PIDIV2);
			break;
		case 3:
			m_faces[i]->orientTranslate(0.0f, -0.2f, 0.0f - 20.0f);
			m_faces[i]->orientRotateX(XM_PIDIV2);
			break;
		case 4:
			m_faces[i]->orientTranslate(0.2f, 0.0f, 0.0f - 20.0f);
			m_faces[i]->orientRotateY(XM_PIDIV2);
			break;
		case 5:
			m_faces[i]->orientTranslate(-0.2f, 0.0f, 0.0f - 20.0f);
			m_faces[i]->orientRotateY(-XM_PIDIV2);
			break;
		}
		m_faces[i]->setBlend(0.0f);
	}
}

LightMask::~LightMask(void)
{
}

void LightMask::Translate(float deltaX, float deltaY, float deltaZ)
{
	for (int i = 0; i < 6; i++)
	{
		m_faces[i]->orientTranslate(deltaX, deltaY, deltaZ);
	}
}

void LightMask::RotateX(float radianAngle)
{
	for (int i = 0; i < 6; i++)
	{
		Translate(0.0f, 0.0f, -0.1f);
		m_faces[i]->orientRotateX(radianAngle);
		Translate(0.0f, 0.0f, 0.1f);
	}
}

void LightMask::RotateY(float radianAngle)
{
	for (int i = 0; i < 6; i++)
	{
		Translate(0.0f, 0.0f, -0.1f);
		m_faces[i]->orientRotateY(radianAngle);
		Translate(0.0f, 0.0f, 0.1f);
	}
}

void LightMask::RotateZ(float radianAngle)
{
	for (int i = 0; i < 6; i++)
	{
		Translate(0.0f, 0.0f, -0.1f);
		m_faces[i]->orientRotateZ(radianAngle);
		Translate(0.0f, 0.0f, 0.1f);
	}
}

void LightMask::setLight(float light)
{
	for (int i = 0; i < 6; i++)
	{
		m_faces[i]->setBlend(light);
	}
}

void LightMask::frame(XMFLOAT3 camPos)
{
	float dx = camPos.x - camPosition.x;
	float dy = camPos.y - camPosition.y;
	float dz = camPos.z - camPosition.z;
	Translate(dx, dy, dz);
	camPosition = camPos;
}

ArrayList<GameModel> LightMask::GetModels()
{
	ArrayList<GameModel> list;
	for (int i = 0; i < 6; i++)
	{
		list.add(m_faces[i]);
	}
	return list;
}

void LightMask::Shutdown()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_faces[i])
		{
			m_faces[i]->Shutdown();
			delete m_faces[i];
			m_faces[i] = 0;
		}
	}

}
