/* LevelClass.H ::: Luke Harper */


#ifndef LEVELCLASS_H
#define LEVELCLASS_H

#include "worldDefs.h"
#include "gameobject.h"
#include "floorobject.h"
#include "wallobject.h"
#include "gamemodel.h"
#include "LightObject.h"
#include "LockObject.h"
#include "DoorObject.h"
#include "arraylist.h"

#include <windows.h> //needed to create and destroy windows and call Win32 functions

class LevelClass
{
	public:
		LevelClass();
		~LevelClass();
		
		ArrayList<GameModel> getGameModels();

		void loadLevel(int);
		int getSizeX();
		int getSizeY();

		void toggleFloor();

	private:
		//the map of the objects
		WALL_TYPE map[100][100];
		ArrayList <GameObject> gamePieces; 
		//GameObject* player;

		int sizeX;
		int sizeY;
		
		//functions

		void Shutdown();
		void initialize();
		void level0();

		void loadObjects();

		///factory methods for building game Objects

		void buildWall(int, int);
		void buildFloor(int, int);
		void buildCeiling(int, int);
		void buildLight(int, int);
		void buildDoor(int, int);
		void buildLock(int, int);
};


#endif