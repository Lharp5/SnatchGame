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

		GameModel* getModel();
	protected:
		void initialize();
		void shutdown();

		GameModel* myModel;
};



#endif