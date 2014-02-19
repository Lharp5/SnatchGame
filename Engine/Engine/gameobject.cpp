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

GameObject::GameObject(GameModel* m)
{
	myModel = m;
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