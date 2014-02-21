#include "gamemodel.h"
#include "modelclass.h"
#include "enemymodel.h"
#include "arraylist.h"
#include "worldDefs.h"

EnemyModel::EnemyModel(void)
{
	m_Head = 0;
	m_Torso = 0;
	m_LeftArm = 0;
	m_RightArm = 0;
	m_LeftLeg = 0;
	m_RightLeg = 0;

	m_InitialPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);

	InitializeModel();
}


EnemyModel::EnemyModel(float x, float y, float z, float s)
{
	m_Head = 0;
	m_Torso = 0;
	m_LeftArm = 0;
	m_RightArm = 0;
	m_LeftLeg = 0;
	m_RightLeg = 0;

	m_InitialPosition = XMFLOAT3(x, y, z);
	m_scale = s;

	InitializeModel();
}


EnemyModel::~EnemyModel(void)
{
	Shutdown();
}

ArrayList<GameModel> EnemyModel::GetGameModels()
{

	ArrayList<GameModel> list;

	list.add(m_Head);
	list.add(m_Torso);
	list.add(m_LeftArm);
	list.add(m_RightArm);
	list.add(m_LeftLeg);
	list.add(m_RightLeg);

	return list;

}


void EnemyModel::InitializeModel()
{

    m_directionVector = XMFLOAT3(0.0f,0.0f,1.0f); //face in positive Z direction
	m_upDirectionVector = XMFLOAT3(0.0f, 1.0f, 0.0f);
	torsoLength = 0.5f;
	step = LEFT;
	leftRotationAngle = -XM_PIDIV2;
	rightRotationAngle = -XM_PIDIV2;

    WCHAR * placeholderFileNames[] = {
		 L"../Engine/textures/wood_texture.dds", 
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/end_grain.dds",
		 L"../Engine/textures/end_grain.dds",
	};

	m_Head = new CubeTexturedModel(m_scale * (torsoLength * 0.7f),
									m_scale * (torsoLength * 0.7f),
									m_scale * (torsoLength * 0.7f),
									placeholderFileNames);
	m_Head->orientTranslate(0.0f, m_scale * (torsoLength / 2.0f + (torsoLength * 0.7f) / 2.0f), 0.0f);
	m_Head->worldTranslate(m_InitialPosition.x, m_InitialPosition.y, m_InitialPosition.z);
	

	m_Torso = new CubeTexturedModel(m_scale * (torsoLength / 2.0f),
									m_scale * (torsoLength),
									m_scale * (torsoLength / 2.0f),
									placeholderFileNames);
	m_Torso->worldTranslate(m_InitialPosition.x, m_InitialPosition.y, m_InitialPosition.z);

	
	m_LeftArm = new CubeTexturedModel(m_scale * (torsoLength / 5.0f),
										m_scale * (torsoLength * 0.9f),
										m_scale * (torsoLength / 3.0f),
										placeholderFileNames);
	m_LeftArm->orientTranslate(-m_scale * (torsoLength / 2.0f - (torsoLength / 4.0f) / 2.0f), m_scale * (torsoLength * 0.05f), 0.0f);
	m_LeftArm->worldTranslate(m_InitialPosition.x, m_InitialPosition.y, m_InitialPosition.z);

	
	m_RightArm = new CubeTexturedModel(m_scale * (torsoLength / 5.0f),
										m_scale * (torsoLength * 0.9f),
										m_scale * (torsoLength / 3.0f),
										placeholderFileNames);
	m_RightArm->orientTranslate(m_scale * (torsoLength / 2.0f - (torsoLength / 4.0f) / 2.0f), m_scale * (torsoLength * 0.05f), 0.0f);
	m_RightArm->worldTranslate(m_InitialPosition.x, m_InitialPosition.y, m_InitialPosition.z);

	
	m_LeftLeg = new CubeTexturedModel(m_scale * (torsoLength / 5.0f),
										m_scale * (torsoLength * 0.9f),
										m_scale * (torsoLength / 2.5f),
										placeholderFileNames);
	m_LeftLeg->orientTranslate(-m_scale * (torsoLength / 8.0f), -m_scale * (torsoLength - torsoLength * 0.05f), 0.0f);
	m_LeftLeg->worldTranslate(m_InitialPosition.x, m_InitialPosition.y, m_InitialPosition.z);

	
	m_RightLeg = new CubeTexturedModel(m_scale * (torsoLength / 5.0f),
										m_scale * (torsoLength * 0.9f),
										m_scale * (torsoLength / 2.5f),
										placeholderFileNames);
	m_RightLeg->orientTranslate(m_scale * (torsoLength / 8.0f), -m_scale * (torsoLength - torsoLength * 0.05f), 0.0f);
	m_RightLeg->worldTranslate(m_InitialPosition.x, m_InitialPosition.y, m_InitialPosition.z);

}

void EnemyModel::WalkAnimation()
{
	if (leftRotationAngle >= -XM_PIDIV4) step = RIGHT;
	if (leftRotationAngle <= -XM_PIDIV2-XM_PIDIV4) step = LEFT;

	float rotationRadianAngle;
	if (step == LEFT) rotationRadianAngle = -XM_PIDIV4/20;
	else if (step == RIGHT) rotationRadianAngle = XM_PIDIV4/20;
	
	m_LeftArm->orientTranslate(0.0f, 0.0f, -cos(leftRotationAngle) * (m_scale * ((torsoLength * 0.9f) / 2.0f)));
	m_RightArm->orientTranslate(0.0f, 0.0f, -cos(rightRotationAngle) * (m_scale * ((torsoLength * 0.9f) / 2.0f)));
	m_LeftLeg->orientTranslate(0.0f, 0.0f, -cos(rightRotationAngle) * (m_scale * ((torsoLength * 0.9f) / 2.0f)));
	m_RightLeg->orientTranslate(0.0f, 0.0f, -cos(leftRotationAngle) * (m_scale * ((torsoLength * 0.9f) / 2.0f)));

	m_LeftArm->orientRotateX(rotationRadianAngle);
	m_RightArm->orientRotateX(-rotationRadianAngle);
	m_LeftLeg->orientRotateX(-rotationRadianAngle);
	m_RightLeg->orientRotateX(rotationRadianAngle);
	leftRotationAngle -= rotationRadianAngle;
	rightRotationAngle += rotationRadianAngle;
	
	m_LeftArm->orientTranslate(0.0f, 0.0f, cos(leftRotationAngle) * (m_scale * ((torsoLength * 0.9f) / 2.0f)));
	m_RightArm->orientTranslate(0.0f, 0.0f, cos(rightRotationAngle) * (m_scale * ((torsoLength * 0.9f) / 2.0f)));
	m_LeftLeg->orientTranslate(0.0f, 0.0f, cos(rightRotationAngle) * (m_scale * ((torsoLength * 0.9f) / 2.0f)));
	m_RightLeg->orientTranslate(0.0f, 0.0f, cos(leftRotationAngle) * (m_scale * ((torsoLength * 0.9f) / 2.0f)));
}

void EnemyModel::MoveForward()
{
	WalkAnimation();
	XMFLOAT3 effectiveDirectionVector;
	XMFLOAT4X4 torsoDirectionMatrix = m_Torso->GetWorldRotateMatrix();
    XMStoreFloat3( &effectiveDirectionVector,  XMVector3Transform( XMLoadFloat3(&m_directionVector), XMLoadFloat4x4(&torsoDirectionMatrix) ));

	float deltaX = effectiveDirectionVector.x*ADVANCE_SPEED;
	float deltaY = effectiveDirectionVector.y*ADVANCE_SPEED;
	float deltaZ = effectiveDirectionVector.z*ADVANCE_SPEED;
	
	m_Head->worldTranslate(deltaX, deltaY, deltaZ);
	m_Torso->worldTranslate(deltaX, deltaY, deltaZ);
	m_LeftArm->worldTranslate(deltaX, deltaY, deltaZ);
	m_RightArm->worldTranslate(deltaX, deltaY, deltaZ);
	m_LeftLeg->worldTranslate(deltaX, deltaY, deltaZ);
	m_RightLeg->worldTranslate(deltaX, deltaY, deltaZ);
	
}


void EnemyModel::TurnLeft()
{
	Turn(-XM_PIDIV4/40);
}

void EnemyModel::TurnRight()
{
	Turn(XM_PIDIV4/40);
}

void EnemyModel::TurnLeft90()
{
	Turn(-XM_PIDIV2);
}

void EnemyModel::TurnRight90()
{
	Turn(XM_PIDIV2);
}

void EnemyModel::Turn(float rotationRadianAngle)
{
	m_Head->worldRotateY(rotationRadianAngle);
	m_Torso->worldRotateY(rotationRadianAngle);
	m_LeftArm->worldRotateY(rotationRadianAngle);
	m_RightArm->worldRotateY(rotationRadianAngle);
	m_LeftLeg->worldRotateY(rotationRadianAngle);
	m_RightLeg->worldRotateY(rotationRadianAngle);
}

void EnemyModel::Shutdown()
{

	if (m_Head)
	{
		delete m_Head;
		m_Head = 0;
	}
	
	if (m_Torso)
	{
		delete m_Torso;
		m_Torso = 0;
	}
	
	if (m_LeftArm)
	{
		delete m_LeftArm;
		m_LeftArm = 0;
	}
	
	if (m_RightArm)
	{
		delete m_RightArm;
		m_RightArm = 0;
	}
	
	if (m_LeftLeg)
	{
		delete m_LeftLeg;
		m_LeftLeg = 0;
	}
	
	if (m_RightLeg)
	{
		delete m_RightLeg;
		m_RightLeg = 0;
	}

}
