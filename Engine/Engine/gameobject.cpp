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

GameObject::~GameObject()
{
	Shutdown();
}

GameModel* GameObject::getModel()
{
	return myModel;
}