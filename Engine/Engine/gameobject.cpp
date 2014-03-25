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
	sound = 0;
	if (myModel)
	{
		myModel->worldTranslate(xLocation*10.0f, yLocation, zLocation*10.0f);
	}
}

GameObject::~GameObject()
{
	shutdown();
}

void GameObject::giveSoundObject(SoundClass* s)
{
	sound = s;
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

float GameObject::getLocationX()
{
	return xLocation;
}

float GameObject::getLocationY()
{
	return yLocation;
}

float GameObject::getLocationZ()
{
	return zLocation;
}

bool GameObject::getStatus()
{
	return false;
}

void GameObject::toggleLight(bool Light)
{
}

void GameObject::translate(float x, float y, float z)
{
	xLocation += x;
	yLocation += y;
	zLocation += z;
	ArrayList<GameModel> list = GetGameModels();
	for (int i = 0; i < list.size(); i++)
	{
		list.elementAt(i)->worldTranslate(0.0f,0.3f,0.0f);
	}
}

