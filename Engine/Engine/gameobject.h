/* GameObject.h ::: Luke Harper */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "gamemodel.h"

class GameObject
{
	public:
		GameObject();
		GameObject(GameModel*);
		~GameObject();

		virtual GameModel* getModel();
	protected:
		virtual void initialize();
		virtual void shutdown();

		GameModel* myModel;
		int xLocation;
		int yLocation;
		int zLocation;
};



#endif