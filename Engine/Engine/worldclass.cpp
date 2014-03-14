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

ArrayList<GameModel> WorldClass::getModels()
{
	wchar_t* outstring = L"Adding models Uh OH!!!";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
	return renderModels;
}

// returning the player start position functions
float WorldClass::getPlayerStartX()
{
	return 50.0f;
}

float WorldClass::getPlayerStartY()
{
	return 0.0f;
}

float WorldClass::getPlayerStartZ()
{
	return 50.0f;
}

void WorldClass::runGame()
{
}
void WorldClass::toggleFloor()
{
	//level->toggleFloor();
}