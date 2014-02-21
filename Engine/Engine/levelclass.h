/* LevelClass.H ::: Luke Harper */


#ifndef LEVELCLASS_H
#define LEVELCLASS_H

#include "worldDefs.h"
#include "gameobject.h"

#include <windows.h> //needed to create and destroy windows and call Win32 functions

class LevelClass
{
	public:
		LevelClass();
		~LevelClass();

		void getPlayerLocation(int*, int*);

		static GameObject* CheckLocation(int, int);

	private:
		GameObject* map[100][100];
		GameObject* player;

		int sizeX;
		int sizeY;
		//functions
		void loadLevel();
		void Shutdown();
};


#endif