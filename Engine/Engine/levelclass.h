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
#include "enemyobject.h"
#include "arraylist.h"
#include "soundclass.h"

#include <windows.h> //needed to create and destroy windows and call Win32 functions

class LevelClass
{
	public:
		LevelClass(SoundClass* s);
		~LevelClass();
		
		ArrayList<GameModel> getGameModels();

		void loadLevel(int);
		int getSizeX();
		int getSizeY();

		GameObject* getLocation(int, int);

		ArrayList<EnemyObject> getEnemies();

		/**********
		*	Function:	checkMap
		*	In:			co-ordinates of desired location
		*	Out:		Object type at location
		*	Purpose:	To get the object type on the map
		***********/
		WALL_TYPE checkMap(int, int);

		int getPlayerStartX();
		int getPlayerStartZ();


		void toggleFloor();

	private:
		//level sound
		SoundClass* sound;
		//the map of the objects
		WALL_TYPE map[100][100];
		ArrayList <GameObject> gamePieces; 
		//GameObject* player;
		ArrayList<EnemyObject> enemyList;

		int sizeX;
		int sizeY;

		//player starting positions as set in levelLoader.
		int playerStartX;
		int playerStartZ;
		
		//functions

		void Shutdown();
		void initialize();
		void level0();
		void level1();

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