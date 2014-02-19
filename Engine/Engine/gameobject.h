/* GameObject.h ::: Luke Harper */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
	public:
		GameObject();
		~GameObject();

		GameModel* getModel();
	protected:
		void initialize();
		void Shutdown();

		GameModel* myModel;
};

#include "gamemodel.h"

#endif