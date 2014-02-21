/* LevelClass.H ::: Luke Harper */


#ifndef LEVELCLASS_H
#define LEVELCLASS_H

#include "worldDefs.h"
#include "gameobject.h"
#include "floorobject.h"
#include "wallobject.h"
#include "playerobject.h"
#include "enemyobject.h"

#include <windows.h> //needed to create and destroy windows and call Win32 functions

class LevelClass
{
	public:
		LevelClass();
		~LevelClass();

		void getPlayerLocation(int*, int*);

		GameObject* CheckLocation(int, int);

		void loadLevel(int);
		int getSizeX();
		int getSizeY();

	private:
		GameObject* map[100][100];
		//GameObject* player;

		int sizeX;
		int sizeY;
		
		//functions

		void Shutdown();
		void initialize();
		void level0();
};


#endif