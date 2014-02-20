#include "gamemodel.h"
#include "modelclass.h"
#include "enemymodel.h"
#include "arraylist.h"

EnemyModel::EnemyModel(void)
{
	m_Head = 0;
	m_Torso = 0;
	m_LeftArm = 0;
	m_RightArm = 0;
	m_LeftLeg = 0;
	m_RightLeg = 0;

    m_directionVector = XMFLOAT3(0.0f,1.0f,0.0f); //face in positive X direction
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

    m_directionVector = XMFLOAT3(0.0f,1.0f,0.0f); //face in positive X direction
	m_InitialPosition = XMFLOAT3(x, y, z);
	m_scale = s;

	InitializeModel();
}


EnemyModel::~EnemyModel(void)
{
	Shutdown();
}

ArrayList<GameModel> EnemyModel::GetGameModels(){

	//Provide an arraylist of simple GameModel components that make up this airplane
	//These will be given to the GraphicsClass object to render using the graphics pipeline

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

	float torsoLength = 0.5f;

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
										m_scale * (torsoLength / 2.0f),
										placeholderFileNames);
	m_LeftLeg->orientTranslate(-m_scale * (torsoLength / 8.0f), -m_scale * (torsoLength - torsoLength * 0.05f), 0.0f);
	m_LeftLeg->worldTranslate(m_InitialPosition.x, m_InitialPosition.y, m_InitialPosition.z);

	
	m_RightLeg = new CubeTexturedModel(m_scale * (torsoLength / 5.0f),
										m_scale * (torsoLength * 0.9f),
										m_scale * (torsoLength / 2.0f),
										placeholderFileNames);
	m_RightLeg->orientTranslate(m_scale * (torsoLength / 8.0f), -m_scale * (torsoLength - torsoLength * 0.05f), 0.0f);
	m_RightLeg->worldTranslate(m_InitialPosition.x, m_InitialPosition.y, m_InitialPosition.z);

}

void EnemyModel::WalkAnimation()
{
	/*
	float propellerRadianAngularIncrement = -XM_PIDIV4/5;
	m_Propeller->orientRotateX(propellerRadianAngularIncrement);
	*/
}

void EnemyModel::MoveForward()
{
	/*
	XMFLOAT3 effectiveDirectionVector;
	XMFLOAT4X4 fuselageDirectionMatrix = m_Fuselage->GetWorldRotateMatrix();
    XMStoreFloat3( &effectiveDirectionVector,  XMVector3Transform( XMLoadFloat3(&m_directionVector), XMLoadFloat4x4(&fuselageDirectionMatrix) ));

	float deltaX = effectiveDirectionVector.x*AIRPLANE_FORWARD_SPEED_FACTOR;
	float deltaY = effectiveDirectionVector.y*AIRPLANE_FORWARD_SPEED_FACTOR;
	float deltaZ = effectiveDirectionVector.z*AIRPLANE_FORWARD_SPEED_FACTOR;

	m_Fuselage->worldTranslate(deltaX, deltaY, deltaZ);
	m_Wing->worldTranslate(deltaX, deltaY, deltaZ);
	m_Propeller->worldTranslate(deltaX, deltaY, deltaZ);
    m_PontoonLeft->worldTranslate(deltaX, deltaY, deltaZ);
    m_PontoonRight->worldTranslate(deltaX, deltaY, deltaZ);
    
	m_StrutFrontLeft->worldTranslate(deltaX, deltaY, deltaZ);
    m_StrutFrontRight->worldTranslate(deltaX, deltaY, deltaZ);
    m_StrutBackLeft->worldTranslate(deltaX, deltaY, deltaZ);
    m_StrutBackRight->worldTranslate(deltaX, deltaY, deltaZ);
	*/
}


void EnemyModel::TurnLeft()
{
	/*
	float rotationRadianAngle = -XM_PIDIV4/40;
	m_Fuselage->worldRotateY(rotationRadianAngle);
	m_Wing->worldRotateY(rotationRadianAngle);
	m_Propeller->worldRotateY(rotationRadianAngle);
	m_PontoonLeft->worldRotateY(rotationRadianAngle);
	m_PontoonRight->worldRotateY(rotationRadianAngle);

	m_StrutFrontLeft->worldRotateY(rotationRadianAngle);
    m_StrutFrontRight->worldRotateY(rotationRadianAngle);
    m_StrutBackLeft->worldRotateY(rotationRadianAngle);
    m_StrutBackRight->worldRotateY(rotationRadianAngle);
	*/
}
void EnemyModel::TurnRight()
{
	/*
	float rotationRadianAngle = XM_PIDIV4/40;
	m_Fuselage->worldRotateY(rotationRadianAngle);
	m_Wing->worldRotateY(rotationRadianAngle);
	m_Propeller->worldRotateY(rotationRadianAngle);
	m_PontoonLeft->worldRotateY(rotationRadianAngle);
	m_PontoonRight->worldRotateY(rotationRadianAngle);

	m_StrutFrontLeft->worldRotateY(rotationRadianAngle);
    m_StrutFrontRight->worldRotateY(rotationRadianAngle);
    m_StrutBackLeft->worldRotateY(rotationRadianAngle);
    m_StrutBackRight->worldRotateY(rotationRadianAngle);
	*/
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
