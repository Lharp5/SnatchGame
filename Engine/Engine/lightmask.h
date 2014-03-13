#pragma once
#include <DirectXMath.h>
#include "arraylist.h"
#include "vertextype.h"
#include "modelclass.h"
#include "gamemodel.h"
#include "quadModel.h"
#include "quadTexturedModel.h"


#include <string>

using namespace DirectX;

enum LightState
{
	ON,
	OFF
};


class LightMask
{
	public:
		static LightState lightState;

		LightMask(XMFLOAT3 camPos = XMFLOAT3(0.0f,0.0f,0.0f));
		virtual ~LightMask(void);
		virtual void Translate(float deltaX, float deltaY, float deltaZ);
		virtual void RotateX(float radianAngle);
		virtual void RotateY(float radianAngle);
		virtual void RotateZ(float radianAngle);
		virtual void setLight(float light);
		virtual void frame(XMFLOAT3 camPos);
		virtual void Shutdown();
		ArrayList<GameModel> GetModels();

	protected:
		QuadTexturedModel* m_faces[6];
		XMFLOAT3 camPosition;

};

