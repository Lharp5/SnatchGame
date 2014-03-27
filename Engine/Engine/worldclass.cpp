/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	worldClass
*	Date:		feb. 21/14
**************************/

#include "worldclass.h"

WorldClass::WorldClass(HWND hwnd)
{
	//renderModels =0;
	winGame = false;
	
	// Initialize the sound object.
	bool result = initializeSound(hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
	}

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

	sound->PlayDesiredFile(1, true);

	return true;
}

WorldClass::~WorldClass()
{
	Shutdown();
}

void WorldClass::initalizeWorld()
{
	level = new LevelClass(sound);

	level->loadLevel(0);

	int path1[] = {2, 2, 1, 3, 2, 1, 2, 2, 1, 3, 2, 1};
	enemies.add(new EnemyObject(path1, sound, 10.0f, -1.85f, 80.0f, 5.0f));
	int path2[] = {2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1};
	enemies.add(new EnemyObject(path2, sound, 40.0f, -1.85f, 40.0f, 5.0f));
	enemies.elementAt(1)->TurnRight90();
	int path3[] = {2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2};
	enemies.add(new EnemyObject(path3, sound, 80.0f, -1.85f, 20.0f, 5.0f));
	enemies.elementAt(2)->TurnRight90();
	int path4[] = {2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2};
	enemies.add(new EnemyObject(path4, sound, 60.0f, -1.85f, 90.0f, 5.0f));
	enemies.elementAt(3)->TurnRight90();
	enemies.elementAt(3)->TurnRight90();

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
	
	ArrayList<GameModel> list;
	list.addAll(level->getGameModels());
	for (int i = 0; i < enemies.size(); i++)
	{
		list.addAll(enemies.elementAt(i)->GetGameModels());
	}

	return list;
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
					float height = level->getLocation(i,j)->getLocationY();
					if (height < 15.0f)
					{
						level->getLocation(i,j)->translate(0.0f, 0.3f, 0.0f);
					}
					else
					{
						if (!dynamic_cast<DoorObject*>(level->getLocation(i,j))->finishedOpening)
						{
							sound->PlayDesiredFile(4, false);
							sound->StopDesiredFile(3);
							dynamic_cast<DoorObject*>(level->getLocation(i,j))->finishedOpening = true;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		EnemyObject* e = enemies.elementAt(i);
		if ((int)e->getLocationX() / 10 == player->getXLocation() && (int)e->getLocationZ() / 10 == player->getYLocation())
		{
			if (sound->GetCurrentSong() != 2)
			{
				sound->StopDesiredFile(sound->GetCurrentSong());
				sound->PlayDesiredFile(2, true);
			}
			e->enemyState = CHASING;
		}
		if (e->currentPathAction % 3 == 0)
		{
			if (e->currentPathAction == 12)
			{
				e->currentPathAction = 0;
			}
			if (e->actionComplete)
			{
				e->actionComplete = false;
				e->MoveForward(e->getPath()[e->currentPathAction]);
				e->currentPathAction++;
			}
		}
		else if (e->currentPathAction % 3 == 1)
		{
			if (e->actionComplete)
			{
				e->actionComplete = false;
				e->Rest(e->getPath()[e->currentPathAction]);
				e->currentPathAction++;
			}
		}
		else if (e->currentPathAction % 3 == 2)
		{
			if (e->actionComplete)
			{
				for (int j = 0; j < e->getPath()[e->currentPathAction]; j++)
				{
					e->TurnRight90();
				}
				e->currentPathAction++;
				e->actionComplete = true;
			}
		}
		enemies.elementAt(i)->Frame();
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