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
		
		//virtual void toggleRender();
		GameModel* getModel();
	protected:
		void initialize();
		void shutdown();

		GameModel* myModel;
		float xLocation;
		float yLocation;
		float zLocation;

	//	bool renderObj;
};



#endif