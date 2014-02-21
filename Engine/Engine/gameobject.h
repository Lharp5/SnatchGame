/* GameObject.h ::: Luke Harper */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "gamemodel.h"

class GameObject
{
	public:
		GameObject();
		GameObject(GameModel*, float, float, float);
		~GameObject();

		virtual GameModel* getModel();
	protected:
		virtual void initialize();
		virtual void shutdown();

		GameModel* myModel;
		float xLocation;
		float yLocation;
		float zLocation;
};



#endif