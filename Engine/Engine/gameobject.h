/* GameObject.h ::: Luke Harper */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "gamemodel.h"
#include "arraylist.h"

class GameObject
{
	public:
		GameObject();
		GameObject(float, float, float, GameModel* m=0);
		~GameObject();
		virtual bool getRenderValue();
		virtual void setRenderValue(bool);
		
		GameModel* getModel();
		virtual ArrayList<GameModel> GetGameModels();

	protected:
		void initialize();
		void shutdown();

		GameModel* myModel;
		float xLocation;
		float yLocation;
		float zLocation;
};



#endif