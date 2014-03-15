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
LevelClass::LevelClass()
{
	initialize();
	loadLevel(0);
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
	/*
	string level1[] = {"W W W W W",
						"W 0 0 0 W",
						"W 0 0 0 W",
						"W 0 0 0 W",
						"W W W W W", };
	WCHAR* wallTextures[] = { L"../Engine/textures/wood_texture.dds",
								L"../Engine/textures/wood_texture.dds",
								L"../Engine/textures/wood_texture.dds",
								L"../Engine/textures/wood_texture.dds",
								L"../Engine/textures/wood_texture.dds",
								L"../Engine/textures/wood_texture.dds", };
	for (int i = 0; i < 5; i++)
	{
		int j = 0;
		stringstream ss(level1[i]);
		string s;
		while (getline(ss, s, ' '))
		{
			if (s == "W")
			{
				map[i][j] = new WallObject(wall, 10.0f*i, 10.0f*j, wallTextures);
				//map[0][a]->getModel()->worldRotateY(-XM_PIDIV2);
			}
			else if (s == "0")
			{
				map[i][j] = new FloorObject(10.0f*i,10.0f*j);
			}
			map[i][j]->getModel()->worldTranslate(-50.0f,0.0f,0.0f);
			j++;
		}
	}
	*/
	
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
	sizeX = 10;
	sizeY = 10;
	
	for(int i=0; i<sizeX; i++){
		for(int j=0; j<sizeY; j++){
			map[i][j] = C_FLOOR;
		}
	}

	//creates the wall images. adjusting their location side walls
	for(int a=0; a<sizeY; a++){
		map[0][a] = C_WALL;
		map[sizeX-1][a] = C_WALL;
	}
	//back/front walls walls
	for(int b=0; b<sizeX; b++){
		map[b][0] = C_WALL;
		map[b][sizeY-1] = C_WALL;
	}

	map[sizeX-1][sizeY/2] = C_LIGHT;
	map[0][sizeY/2] = C_LOCK;
	map[sizeX/2][0] = C_DOOR;
	loadObjects();

	wchar_t* outstring = L"Level 0: Loaded\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

void LevelClass::loadObjects()
{
	for(int i=0; i<sizeX; i++)
		for(int j=0; j<sizeY; j++){
			switch(map[i][j]){
			case C_WALL:	buildWall(i,j);			break;
			case C_DOOR:	buildDoor(i,j);			break;
			case C_LIGHT:	buildLight(i,j);		break;
			case C_LOCK:	buildLock(i,j);			break;
			}
			buildFloor(i,j);
		}
}

void LevelClass::buildWall(int x, int y)
{
	WCHAR* wallTextures[] = { L"../Engine/textures/walltexture.dds",
								L"../Engine/textures/walltexture.dds",
								L"../Engine/textures/walltexture.dds",
								L"../Engine/textures/walltexture.dds",
								L"../Engine/textures/walltexture.dds",
								L"../Engine/textures/walltexture.dds",
							};

	WallObject* newWall = new WallObject(x+0.0f,y+0.0f, wallTextures);
	gamePieces.add(newWall);
}

void LevelClass::buildDoor(int x, int y)
{
	WCHAR* doorTextures[] = { L"../Engine/textures/doortexture.dds",
								L"../Engine/textures/doortexture.dds",
								L"../Engine/textures/toblerone.dds",
								L"../Engine/textures/toblerone.dds",
								L"../Engine/textures/toblerone.dds",
								L"../Engine/textures/toblerone.dds",
							};

	DoorObject* newDoor = new DoorObject(-1,-1,x+0.0f,y+0.0f,doorTextures);
	gamePieces.add(newDoor);
}

void LevelClass::buildFloor(int x, int y)
{
	WCHAR * floorTexture = L"../Engine/textures/carpettexture.dds";

	FloorObject * newFloor = new FloorObject(x+0.0f,y+0.0f,floorTexture);
	gamePieces.add(newFloor);
}

void LevelClass::buildLight(int x, int y)
{
	WCHAR* lightTextures[] = { L"../Engine/textures/coca_cola.dds",
								L"../Engine/textures/coca_cola.dds",
								L"../Engine/textures/coca_cola.dds",
								L"../Engine/textures/coca_cola.dds",
								L"../Engine/textures/coca_cola.dds",
								L"../Engine/textures/coca_cola.dds",
							};

	LightObject* newLight = new LightObject(x+0.0f,y+0.0f, lightTextures);
	gamePieces.add(newLight);
}

void LevelClass::buildLock(int x, int y)
{
	WCHAR* lockTextures[] = { L"../Engine/textures/penciltexture.dds",
								L"../Engine/textures/penciltexture.dds",
								L"../Engine/textures/penciltexture.dds",
								L"../Engine/textures/penciltexture.dds",
								L"../Engine/textures/penciltexture.dds",
								L"../Engine/textures/penciltexture.dds",
							};

	LockObject* newLock = new LockObject(x+0.0f,y+0.0f, lockTextures);
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

/* Function:	getPlayerLocation
 * Purpose:		to find the player on the map.
 * in/out:		X and Y position of the player.
*/


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
		gameModels.add(gamePieces.elementAt(i)->getModel());

	return gameModels;
}

/*void LevelClass::toggleFloor()
{
	for(int i=0; i<sizeX; i++){
		for(int j=0; j<sizeY; j++){
			map[i][j] = new FloorObject(10.0f*i,10.0f*j);
		}
	}
}*/

