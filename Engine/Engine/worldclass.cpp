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


void WorldClass::updatePlayer(float x, float z)
{
	int mapX = convertToInt(x);
	int mapZ = convertToInt(z);

	player->setPosition(mapX, mapZ);

}
ArrayList<GameModel> WorldClass::getModels()
{
	wchar_t* outstring = L"Adding models Uh OH!!!";
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
void WorldClass::toggleFloor()
{
	//level->toggleFloor();
}

int WorldClass::convertToInt(float number)
{
	int intNum = number;
	float rem = fmodf(number, intNum);

	if(rem<=0.05f)
		return intNum+1;
	else
		return intNum;

}