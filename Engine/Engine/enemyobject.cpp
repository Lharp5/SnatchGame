#include "enemyobject.h"

EnemyObject::EnemyObject(float x, float y, float z, float s) : GameObject(x, y, z)
{
	m_model = new EnemyModel(x, y, z, s);
	renderVal = true;
}

EnemyObject::~EnemyObject(void)
{
	shutdown();
}

void EnemyObject::shutdown()
{
	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}
}

ArrayList<GameModel> EnemyObject::GetGameModels()
{
	return m_model->GetGameModels();
}

void EnemyObject::TurnLeft()
{
	m_model->TurnLeft();
}

void EnemyObject::TurnRight()
{
	m_model->TurnRight();
}

void EnemyObject::TurnLeft90()
{
	m_model->TurnLeft90();
}

void EnemyObject::TurnRight90()
{
	m_model->TurnRight90();
}

void EnemyObject::Turn(float rotationRadianAngle)
{
	m_model->Turn(rotationRadianAngle);
}

void EnemyObject::MoveForward()
{
	m_model->MoveForward();
}

bool EnemyObject::getRenderValue()
{
	return renderVal;
}

void EnemyObject::setRenderValue(bool b)
{
	ArrayList<GameModel> list = GetGameModels();
	for (int i = 0; i < list.size(); i++)
	{
		list.elementAt(i)->setRenderVal(b);
	}
	renderVal = b;
}