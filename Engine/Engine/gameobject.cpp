/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	GameObject
*	Date:		feb. 19/14
**************************/


//super class for all game Models.
#include "gameobject.h"

GameObject::GameObject()
{
	initialize();
}

GameObject::GameObject(GameModel* m, float x, float y, float z)
{
	xLocation = x;
	yLocation =y;
	zLocation =z;
	myModel = m;

	myModel->worldTranslate(xLocation, yLocation, zLocation);
}

GameObject::~GameObject()
{
	shutdown();
}


void GameObject::initialize()
{
}

void GameObject:: shutdown()
{
}

GameModel* GameObject::getModel()
{
	return myModel;
}