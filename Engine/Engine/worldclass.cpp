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
	winGame = false;
	initalizeWorld();
	
}

bool WorldClass::initializeSound(HWND hwnd)
{
	sound = new SoundClass;
	if(!sound)
	{
		return false;
	}
 
	// Initialize the sound object.
	bool result = sound->Initialize(hwnd);
	if(!result)
	{
		return false;
	}

	sound->PlayWaveFile();

	return true;
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
	player->setPosition((int)getPlayerStartX(), (int)getPlayerStartZ());
	
	//NEEDS TO FINISH THIS CLASS

	
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

bool WorldClass::isWall(int x, int y)
{
	switch(level->checkMap(x, y)){
		case C_WALL:
		case C_DOOR_1: case C_DOOR_2: return !(level->getLocation(x,y)->getStatus()); break;
		case C_LIGHT_1: case C_LIGHT_2: case C_LIGHT_3: case C_LIGHT_4: 
		case C_LOCK_1: case C_LOCK_2: case C_LOCK_3: case C_LOCK_4:
			return true;
	}
	return false;
}

void WorldClass::updatePlayer(float x, float z)
{
	int mapX = convertToInt(x/10);
	int mapZ = convertToInt(z/10);

	//wchar_t s[32];
	//wsprintf(s, L"New Position: %d, %d\n", mapX, mapZ);
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), s, wcslen(s), NULL, NULL);

	player->setPosition(mapX, mapZ);

}
ArrayList<GameModel> WorldClass::getModels()
{
	//wchar_t* outstring = L"Adding models\n";
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
	
	return level->getGameModels();
	//return renderModels;
}

PlayerClass* WorldClass::getPlayer()
{
	return player;
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
	for(int i=0; i<level->getSizeX(); i++){
		for(int j=0; j<level->getSizeY(); j++){
			if(level->checkMap(i,j) == C_DOOR_1 || level->checkMap(i,j) == C_DOOR_2){
				if(level->getLocation(i,j)->getStatus())
				{
					level->getLocation(i,j)->translate(0.0f, 0.3f, 0.0f);
					float height = level->getLocation(i,j)->getLocationY();
					if (height > 20.0f)
						level->getLocation(i,j)->setRenderValue(false);
				}

				//wchar_t* outstring = L"Found Door\n";
				//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
			}
		}
	}
}

void WorldClass::doAction()
{
	int playerX = player->getXLocation();
	int playerY = player->getYLocation();

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

	int newNum = (int)num;

	return newNum;

}

void WorldClass::updateLight(int x, int z)
{
	int sourceX = level->getLocation(x, z)->getSourceX();
	int sourceY = level->getLocation(x, z)->getSourceY();

	level->getLocation(x, z)->toggleLight(level->getLocation(sourceX, sourceY)->getStatus());
}