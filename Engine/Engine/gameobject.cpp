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
		myModel->worldTranslate(xLocation*10.0f, yLocation, zLocation*10.0f);
	}
}

GameObject::~GameObject()
{
	shutdown();
}


void GameObject::initialize()
{
}

bool GameObject::isLit()
{
	return false;
}

void GameObject::shutdown()
{
	/*if(myModel){
		delete myModel;
		myModel = 0;
	}*/
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

ArrayList<GameModel> GameObject::GetGameModels()
{
	ArrayList<GameModel> list;
	list.add(myModel);
	return list;
}

bool GameObject::getLocation(int x, int z)
{
	return((x == xLocation)&&(z==zLocation));
}

bool GameObject::doAction()
{
	return false;
}

int GameObject::getSourceX()
{
	return 0;
}

int GameObject::getSourceY()
{
	return 0;
}

bool GameObject::getStatus()
{
	return false;
}

void GameObject::toggleLight(bool Light)
{
}

