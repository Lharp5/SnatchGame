/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	LevelClass
*	Date:		feb. 19/14
**************************/
#include "levelclass.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//creating a base level THE TEMP LEVEL
LevelClass::LevelClass(SoundClass* s) : sound(s)
{
	initialize();
	wchar_t* outstring = L"...Levels Loaded\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

//probably needed more later
LevelClass::~LevelClass()
{
	Shutdown();
	wchar_t* outstring = L"Levels Closed";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

/* Function:	initalize 
 * Purpose:		to initalize the map.
*/
void LevelClass::initialize()
{
	sizeX = 5;
	sizeY = 5;

	for(int i=0; i<sizeX; i++){
		for(int j=0; j<sizeY; j++){
			map[i][j] = C_DEFAULT;
		}
	}
}


/* Function:	loadLevel 
 * Purpose:		to change the level
 * in:			the level wishing to be assigned as an int.
*/
void LevelClass::loadLevel(int level)
{	
	switch(level){
	case 1:		break;
	case 2:		break;
	case 3:		break;
	case 4:		break;
	default:	level0(); break;
	}
	
}

/* Function:	loadLevel 
 * Purpose:		To assign level 1 to the map
*/
void LevelClass::level0()
{
	sizeX = 12;
	sizeY = 12;

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			map[i][j] = C_FLOOR;
		}
	}
	for (int i = 0; i < sizeX; i++)
	{
		map[i][0] = C_WALL;
		map[i][sizeY - 1] = C_WALL;
	}
	for (int i = 0; i < sizeY; i++)
	{
		map[0][i] = C_WALL;
		map[sizeX - 1][i] = C_WALL;
	}
	
	map[6][0] = C_LOCK_1;
	map[9][0] = C_LOCK_1;
	map[3][1] = C_WALL;
	map[5][1] = C_WALL;
	map[7][1] = C_WALL;
	map[8][1] = C_WALL;
	map[10][1] = C_WALL;
	map[3][2] = C_WALL;
	map[7][2] = C_WALL;
	map[5][3] = C_WALL;
	map[7][3] = C_WALL;
	map[8][3] = C_WALL;
	map[10][3] = C_WALL;
	map[7][4] = C_DOOR_2;
	map[11][4] = C_LIGHT_4;
	for (int i = 2; i < 11; i++) map[i][5] = C_WALL;
	map[8][5] = C_DOOR_1;
	map[2][6] = C_LIGHT_4;
	map[3][6] = C_WALL;
	map[7][6] = C_WALL;
	map[1][7] = C_WALL;
	map[2][7] = C_WALL;
	map[3][7] = C_WALL;
	map[5][7] = C_WALL;
	map[7][7] = C_WALL;
	map[9][7] = C_WALL;
	map[10][7] = C_WALL;
	map[5][8] = C_WALL;
	map[7][8] = C_WALL;
	map[11][8] = C_LIGHT_4;
	map[2][9] = C_WALL;
	map[3][9] = C_WALL;
	map[5][9] = C_WALL;
	map[7][9] = C_WALL;
	map[9][9] = C_WALL;
	map[10][9] = C_WALL;
	map[0][10] = C_LOCK_2;
	map[5][10] = C_WALL;
	map[9][10] = C_DOOR_2;
	map[11][10] = C_FLOOR;
	
	playerStartX = 1;
	playerStartZ = 1;

	loadObjects();

	for (int i = 1; i < 7; i++)
	{
		for (int j = 1; j < 6; j++)
		{
			if (map[i][j] == C_FLOOR)
			{
				dynamic_cast<FloorObject*>(getLocation(i, j))->createSource(2, 6);
			}
		}
	}
	dynamic_cast<FloorObject*>(getLocation(1, 6))->createSource(2, 6);
	
	for (int i = 8; i < 11; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if (map[i][j] == C_FLOOR)
			{
				dynamic_cast<FloorObject*>(getLocation(i, j))->createSource(11, 4);
			}
		}
	}
	
	for (int i = 1; i < 10; i++)
	{
		for (int j = 7; j < 11; j++)
		{
			if (map[i][j] == C_FLOOR)
			{
				dynamic_cast<FloorObject*>(getLocation(i, j))->createSource(11, 8);
			}
		}
	}
	for (int i = 4; i < 11; i++)
	{
		if (map[i][6] == C_FLOOR)
		{
			dynamic_cast<FloorObject*>(getLocation(i, 6))->createSource(11, 8);
		}
	}
	dynamic_cast<FloorObject*>(getLocation(10, 8))->createSource(11, 8);
	
	dynamic_cast<DoorObject*>(getLocation(7, 4))->createLock(dynamic_cast<LockObject*>(getLocation(6, 0)));
	dynamic_cast<DoorObject*>(getLocation(8, 5))->createLock(dynamic_cast<LockObject*>(getLocation(9, 0)));
	dynamic_cast<DoorObject*>(getLocation(9, 10))->createLock(dynamic_cast<LockObject*>(getLocation(0, 10)));

	int path1[] = {2, 2, 1, 3, 2, 1, 2, 2, 1, 3, 2, 1};
	enemyList.add(new EnemyObject(path1, sound, 10.0f, -1.85f, 80.0f, 5.0f));
	int path2[] = {2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1};
	enemyList.add(new EnemyObject(path2, sound, 40.0f, -1.85f, 40.0f, 5.0f));
	enemyList.elementAt(1)->TurnRight90();
	enemyList.elementAt(1)->setPatrolLight(dynamic_cast<LightObject*>(getLocation(2, 6)));
	int path3[] = {2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2};
	enemyList.add(new EnemyObject(path3, sound, 80.0f, -1.85f, 20.0f, 5.0f));
	enemyList.elementAt(2)->TurnRight90();
	enemyList.elementAt(2)->setPatrolLight(dynamic_cast<LightObject*>(getLocation(11, 4)));
	int path4[] = {2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2};
	enemyList.add(new EnemyObject(path4, sound, 60.0f, -1.85f, 90.0f, 5.0f));
	enemyList.elementAt(3)->TurnRight90();
	enemyList.elementAt(3)->TurnRight90();
	enemyList.elementAt(3)->setPatrolLight(dynamic_cast<LightObject*>(getLocation(11, 8)));

	wchar_t* outstring = L"Level 0: Loaded\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

void LevelClass::level1()
{

}

void LevelClass::loadObjects()
{
	for(int i=0; i<sizeX; i++){
		for(int j=0; j<sizeY; j++){
			switch(map[i][j]){
			case C_DOOR_1: case C_DOOR_2:									
										buildDoor(i,j); buildFloor(i,j); buildCeiling(i,j);		break;
			case C_LOCK_1: case C_LOCK_2: case C_LOCK_3: case C_LOCK_4:		buildLock(i,j);		break;
			case C_LIGHT_1: case C_LIGHT_2: case C_LIGHT_3: case C_LIGHT_4:	buildLight(i,j);	break;
			case C_WALL:													buildWall(i,j);		break;
			case C_FLOOR:								buildFloor(i,j); buildCeiling(i, j);	break;
			}
		}
	}
}

void LevelClass::buildWall(int x, int y)
{
	WCHAR* wallTextures[] = { L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
							};

	WallObject* newWall = new WallObject(x+0.0f,y+0.0f, wallTextures);
	gamePieces.add(newWall);
}

void LevelClass::buildDoor(int x, int y)
{
	WCHAR* doorTextures[] = { L"../Engine/textures/doortexture.dds",
								L"../Engine/textures/doortexture.dds",
								L"../Engine/textures/doortexture.dds",
								L"../Engine/textures/doortexture.dds",
								L"../Engine/textures/doortexture.dds",
								L"../Engine/textures/doortexture.dds",
							};

	DoorObject* newDoor = new DoorObject(-1,-1,x+0.0f,y+0.0f,doorTextures);
	newDoor->giveSoundObject(sound);
	if (map[x][y] == C_DOOR_2) newDoor->getModel()->worldRotateY(XM_PIDIV2);
	gamePieces.add(newDoor);
}

void LevelClass::buildFloor(int x, int y)
{
	WCHAR * floorTexture = L"../Engine/textures/tilefloortexture.dds";

	FloorObject * newFloor = new FloorObject(x+0.0f,y+0.0f,floorTexture);
	gamePieces.add(newFloor);
}

void LevelClass::buildCeiling(int x, int y)
{
	WCHAR * ceilingTexture = L"../Engine/textures/concretetexture.dds";

	FloorObject * newCeiling = new FloorObject(x+0.0f, y+0.0f, ceilingTexture);
	newCeiling->getModel()->worldRotateX(XM_PI);
	newCeiling->getModel()->worldTranslate(0.0f, 14.5f, 0.0f);
	gamePieces.add(newCeiling);
}

void LevelClass::buildLight(int x, int y)
{
	WCHAR* lightTextures[] = { L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
							};

	LightObject* newLight = new LightObject(x+0.0f,y+0.0f, lightTextures);
	newLight->giveSoundObject(sound);
	if (map[x][y] == C_LIGHT_2) newLight->rotate(XM_PIDIV2);
	if (map[x][y] == C_LIGHT_3) newLight->rotate(XM_PI);
	if (map[x][y] == C_LIGHT_4) newLight->rotate(XM_PI + XM_PIDIV2);
	gamePieces.add(newLight);
}

void LevelClass::buildLock(int x, int y)
{
	WCHAR* lockTextures[] = { L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
								L"../Engine/textures/brickwalltexture2.dds",
							};

	LockObject* newLock = new LockObject(x+0.0f,y+0.0f, lockTextures);
	newLock->giveSoundObject(sound);
	if (map[x][y] == C_LOCK_2) newLock->rotate(XM_PIDIV2);
	if (map[x][y] == C_LOCK_3) newLock->rotate(XM_PI);
	if (map[x][y] == C_LOCK_4) newLock->rotate(XM_PI + XM_PIDIV2);
	gamePieces.add(newLock);
}

/* Function:	Shutdown
 * Purpose:		To free up any pointers, close any files.
*/
void LevelClass::Shutdown()
{
	for(int i=0; i<gamePieces.size(); i++){
		delete gamePieces.elementAt(i);
	}
	wchar_t* outstring = L"Levels Shutdown..";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}


int LevelClass::getSizeX()
{
	return sizeX;
}

int LevelClass::getSizeY()
{
	return sizeY;
}

ArrayList<GameModel> LevelClass::getGameModels()
{
	ArrayList<GameModel> gameModels;
	
	for(int i=0; i<gamePieces.size(); i++)
		gameModels.addAll(gamePieces.elementAt(i)->GetGameModels());

	return gameModels;
}

ArrayList<EnemyObject> LevelClass::getEnemies()
{
	return enemyList;
}

int LevelClass::getPlayerStartX()
{
	return playerStartX;
}

int LevelClass::getPlayerStartZ()
{
	return playerStartZ;
}

GameObject* LevelClass::getLocation(int x, int z)
{
	if(x<sizeX && z<sizeY && x>=0 && z>=0){
	for(int i=0; i<gamePieces.size(); i++)
		if(gamePieces.elementAt(i)->getLocation(x,z)== true)
		{
			return gamePieces.elementAt(i);
		}
	}
	return NULL;
}

WALL_TYPE LevelClass::checkMap(int x, int z)
{
	//wchar_t s[32];
	//wsprintf(s, L"Checking Location: %d, %d\n", x, z);
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), s, wcslen(s), NULL, NULL);
	//if(map[x][z] == C_DEFAULT){
	//
	//}
	return map[x][z];
}

/*void LevelClass::toggleFloor()
{
	for(int i=0; i<sizeX; i++){
		for(int j=0; j<sizeY; j++){
			map[i][j] = new FloorObject(10.0f*i,10.0f*j);
		}
	}
}*/

