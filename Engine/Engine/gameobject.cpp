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

GameObject::GameObject(float x, float y, float z, GameModel* m): xLocation(x), yLocation(y), zLocation(z), myModel(m)
{
	if (myModel)
	{
		myModel->worldTranslate(xLocation, yLocation, zLocation);
	}
}

GameObject::~GameObject()
{
	shutdown();
}


void GameObject::initialize()
{
}

void GameObject::shutdown()
{
	if(myModel){
		delete myModel;
		myModel = 0;
	}
}

GameModel* GameObject::getModel()
{
	return myModel;
}

bool GameObject::getRenderValue()
{
	if (myModel)
	{
		return myModel->getRenderVal();
	}
	return true;
}

void GameObject::setRenderValue(bool b)
{
	if (myModel)
	{
		myModel->setRenderVal(b);
	}
}