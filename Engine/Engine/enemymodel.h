#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "gamemodel.h"
#include "cubeTexturedModel.h"
#include "arraylist.h"


#include <string>

using namespace DirectX;

class EnemyModel
{
public:
	EnemyModel(void);
	EnemyModel(float x, float y, float z, float s);
	virtual ~EnemyModel(void);
	virtual void Shutdown();
	ArrayList<GameModel> GetGameModels();

	void TurnLeft();
	void TurnRight();
	void MoveForward();
	void WalkAnimation();

protected:
	virtual void InitializeModel(); //construct the airplane from component parts

private:
	
	CubeTexturedModel* m_Head;
	CubeTexturedModel* m_Torso;
	CubeTexturedModel* m_LeftArm;
	CubeTexturedModel* m_RightArm;
	CubeTexturedModel* m_LeftLeg;
	CubeTexturedModel* m_RightLeg;

	XMFLOAT3 m_directionVector; //direction plane is facing when constructed
	XMFLOAT3 m_InitialPosition;
	float m_scale;
};

