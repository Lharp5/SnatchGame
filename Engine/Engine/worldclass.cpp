/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	worldClass
*	Date:		feb. 21/14
**************************/

#include "worldclass.h"

WorldClass::WorldClass()
{
	//renderModels =0;
	initalizeWorld();
	
}

WorldClass::~WorldClass()
{
	Shutdown();
}

void WorldClass::initalizeWorld()
{
	level = new LevelClass();

	level->loadLevel(0);

	player = new PlayerClass();
	player->setPosition(getPlayerStartX(), getPlayerStartZ());
	
	//NEEDS TO FINISH THIS CLASS

	renderModels.addAll(level->getGameModels());
	
	
	wchar_t* outstring = L"Models added..";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}


void WorldClass::Shutdown()
{
	/*if(level)
		delete level;
	if(player)
		delete player;

	level = 0;
	player = 0;*/

	wchar_t* outstring = L"World Shutdown..";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}


bool WorldClass::updatePlayer(float x, float z)
{
	int mapX = convertToInt(x/10);
	int mapZ = convertToInt(z/10);

	wchar_t s[32];
	wsprintf(s, L"New Position: %d, %d\n", mapX, mapZ);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), s, wcslen(s), NULL, NULL);

	switch(level->checkMap(mapX, mapZ)){
		case C_WALL:
		case C_DOOR:
		case C_LIGHT:
		case C_LOCK:	return false; break;
	}
	player->setPosition(mapX, mapZ);
	return true;

}
ArrayList<GameModel> WorldClass::getModels()
{
	wchar_t* outstring = L"Adding models\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
	return renderModels;
}

// returning the player start position functions
float WorldClass::getPlayerStartX()
{
	return level->getPlayerStartX()*10.0f;
}

float WorldClass::getPlayerStartY()
{
	return 0.0f;
}

float WorldClass::getPlayerStartZ()
{
	return level->getPlayerStartZ()*10.0f;
}

void WorldClass::runGame()
{

}

void WorldClass::doAction()
{
	int playerX = player->getXLocation();
	int playerY = player->getYLocation();

	/*switch(level->checkMap(playerX, playerY)){
		case C_WALL:
		case C_FLOOR:	break;
		case C_LIGHT:	
		case C_DOOR:	
		case C_LOCK:	scan(playerX, playerY);	break;
	}*/

	scan(playerX, playerY);
	
}

void WorldClass::scan(int x, int y)
{
	if(level->getLocation(x+1, y+1))
		if(level->getLocation(x+1, y+1)->doAction())
			return;
	if(level->getLocation(x, y+1))
		if(level->getLocation(x, y+1)->doAction())
			return;
	if(level->getLocation(x+1, y))
		if(level->getLocation(x+1, y)->doAction())
			return;
	if(level->getLocation(x-1, y-1))
		if(level->getLocation(x-1, y-1)->doAction())
			return;
	if(level->getLocation(x-1, y))	
		if(level->getLocation(x-1, y)->doAction())
			return;
	if(level->getLocation(x, y-1))
		if(level->getLocation(x, y-1)->doAction())
			return;
	if(level->getLocation(x+1, y-1))
		if(level->getLocation(x+1, y-1)->doAction())
			return;
	if(level->getLocation(x-1, y+1))
		if(level->getLocation(x-1, y+1)->doAction())
			return;
	if(level->getLocation(x, y))
		if(level->getLocation(x, y)->doAction())
			return;
}
bool WorldClass::checkLight()
{
	int playerX = player->getXLocation();
	int playerY = player->getYLocation();
	
	if(level->checkMap(playerX, playerY) == C_FLOOR){
		updateLight(playerX, playerY);
		return level->getLocation(playerX, playerY)->isLit();
	}


	return true;
}

void WorldClass::toggleFloor()
{
	//level->toggleFloor();
}

int WorldClass::convertToInt(float num)
{
	num+=0.5f;
	num = floorf(num);

	int newNum = num;

	return newNum;

}

void WorldClass::updateLight(int x, int z)
{
	int sourceX = level->getLocation(x, z)->getSourceX();
	int sourceY = level->getLocation(x, z)->getSourceY();

	level->getLocation(x, z)->toggleLight(level->getLocation(sourceX, sourceY)->getStatus());
}