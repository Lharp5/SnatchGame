#include "enemyobject.h"
#include <ctime>

EnemyObject::EnemyObject(vector<int> p, SoundClass* snd, float x, float y, float z, float s) : GameObject(x, y, z)
{
	m_model = new EnemyModel(x, y, z, s);
	renderVal = true;
	destination = XMINT2((int)x, (int)z);
	direction = NORTH;
	actionComplete = true;
	currentPathAction = 12;
	for (unsigned int i = 0; i < p.size(); i++)
	{
		path.push_back(p[i]);
	}
	currentPath = path;
	giveSoundObject(snd);
	enemyState = PATROLLING;
	patrolLight = 0;
	playerSpotted = false;
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

void EnemyObject::setPatrolLight(LightObject* light)
{
	patrolLight = light;
}

LightObject* EnemyObject::getPatrolLight()
{
	return patrolLight;
}

void EnemyObject::TurnLeft()
{
	m_model->TurnLeft();
}

void EnemyObject::TurnRight()
{
	m_model->TurnRight();
}

void EnemyObject::Frame()
{
	if (currentPathAction % 3 == 1)
	{
		if ((int)xLocation != destination.x || (int)zLocation != destination.y)
		{
			if (direction == NORTH)
			{
				zLocation += ADVANCE_SPEED;
			}
			else if (direction == EAST)
			{
				xLocation += ADVANCE_SPEED;
			}
			else if (direction == SOUTH)
			{
				zLocation -= ADVANCE_SPEED;
			}
			else if (direction == WEST)
			{
				xLocation -= ADVANCE_SPEED;
			}
			m_model->MoveForward();
		}
		else
		{
			actionComplete = true;
		}
	}
	else if (currentPathAction % 3 == 2)
	{
		if (xLocation != (float)destination.x || zLocation != (float)destination.y)
		{
			m_model->Transform(-xLocation, 0.0f, -zLocation);
			xLocation = (float)destination.x;
			zLocation = (float)destination.y;
			m_model->Transform(xLocation, 0.0f, zLocation);
		}
		if (time(0) < timeN)
		{
			m_model->ResetPose();
		}
		else
		{
			actionComplete = true;
		}
	}
}

void EnemyObject::fixPosition()
{
	m_model->Transform(-xLocation, 0.0f, -zLocation);
	xLocation = (float)destination.x;
	zLocation = (float)destination.y;
	m_model->Transform(xLocation, 0.0f, zLocation);
}

void EnemyObject::TurnLeft90()
{
	if (direction == NORTH)
	{
		direction = WEST;
	}
	else
	{
		direction = (Direction)((int)direction - 1);
	}
	m_model->TurnLeft90();
}

void EnemyObject::TurnRight90()
{
	if (direction == WEST)
	{
		direction = NORTH;
	}
	else
	{
		direction = (Direction)((int)direction + 1);
	}
	m_model->TurnRight90();
}

void EnemyObject::Turn(float rotationRadianAngle)
{
	m_model->Turn(rotationRadianAngle);
}

void EnemyObject::MoveForward(int spaces)
{
	if (direction == NORTH)
	{
		destination = XMINT2((int)xLocation, (int)zLocation + spaces * 10);
	}
	else if (direction == EAST)
	{
		destination = XMINT2((int)xLocation + spaces * 10, (int)zLocation);
	}
	else if (direction == SOUTH)
	{
		destination = XMINT2((int)xLocation, (int)zLocation - spaces * 10);
	}
	else if (direction == WEST)
	{
		destination = XMINT2((int)xLocation - spaces * 10, (int)zLocation);
	}
	actionComplete = false;
}

void EnemyObject::Rest(int t)
{
	timeN = time(0) + t;
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

vector<int>& EnemyObject::getPath()
{
	return path;
}

vector<int>& EnemyObject::getFixPath()
{
	return fixPath;
}

void EnemyObject::setFixPath(vector<int>& p)
{
	resetPath(fixPath);
	for (unsigned int i = 0; i < p.size(); i++)
	{
		fixPath.push_back(p[i]);
	}
	setCurrentPath(fixPath);
}

vector<int>& EnemyObject::getCurrentPath()
{
	return currentPath;
}

void EnemyObject::setCurrentPath(vector<int>& p)
{
	currentPath = p;
}

void EnemyObject::resetPath(vector<int>& p)
{
	while (p.size() > 0)
	{
		p.pop_back();
	}
}

Direction EnemyObject::getDirection()
{
	return direction;
}

Direction EnemyObject::getPrevDirection()
{
	return prevDirection;
}

void EnemyObject::setPrevDirection(Direction d)
{
	prevDirection = d;
}

XMINT2 EnemyObject::getDestination()
{
	return destination;
}

XMINT2 EnemyObject::getPrevDestination()
{
	return prevDestination;
}

void EnemyObject::setPrevDestination(int x, int y)
{
	prevDestination = XMINT2(x, y);
}