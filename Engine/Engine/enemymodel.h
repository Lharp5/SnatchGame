#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "gamemodel.h"
#include "cubeTexturedModel.h"
#include "arraylist.h"

#include <string>

using namespace DirectX;

enum SteppingState { LEFT, RIGHT };

class EnemyModel
{
public:
	EnemyModel(float x=0.0f, float y=0.0f, float z=0.0f, float s=1.0f);
	virtual ~EnemyModel(void);
	virtual void Shutdown();
	ArrayList<GameModel> GetGameModels();

	void TurnLeft();
	void TurnRight();
	void TurnLeft90();
	void TurnRight90();
	void Turn(float rotationRadianAngle);
	void MoveForward();
	void MoveForwardDelta(float);
	void Transform(float, float, float);
	void WalkAnimation();
	void ResetPose();

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
	XMFLOAT3 m_upDirectionVector;
	XMFLOAT3 m_InitialPosition;

	float m_scale;
	float torsoLength;
	float leftRotationAngle;
	float rightRotationAngle;

	SteppingState step;
};
