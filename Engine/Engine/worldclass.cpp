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
	gameState = MENU;
	winGame = false;
	
	// Initialize the sound object.
	bool result = initializeSound(hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
	}

	initalizeWorld();
	playerWalking = false;
	
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

	enemies.addAll(level->getEnemies());

	player = new PlayerClass();
	player->setPosition((int)getPlayerStartX(), (int)getPlayerStartZ());
	
	playerSeen = false;

	startTime = time(nullptr);
	currTime = time(nullptr);
	suspicionTime = time(nullptr);

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

int WorldClass::getCurrLevel()
{
	return currLevel;
}
void WorldClass::resetLevel(int levelNum)
{
	currLevel = levelNum;
	gameState = PLAYING;
	level->resetLevel(levelNum);
	player->setPosition(level->getPlayerStartX(), level->getPlayerStartZ());
	suspicionTime = time(nullptr);
	playerSeen = false;
	for(int i=0; i<enemies.size(); i++)
		enemies.elementAt(i)->playerSpotted = false;
	
	

	/* TODO */
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
	if (gameState == MENU)
	{
		if (sound->GetCurrentSong() != 9)
		{
			sound->StopDesiredFile(sound->GetCurrentSong());
			sound->PlayDesiredFile(9, false);
		}
	}
	else if (gameState == PLAYING)
	{
		currTime = time(nullptr);
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
			if (playerSeen && !e->playerSpotted)
			{
				continue;
			}
			int enemyX = (int)e->getLocationX() / 10;
			int enemyY = (int)e->getLocationZ() / 10;
			int sight;
			if ((e->getPatrolLight() != 0 && e->getPatrolLight()->getStatus()) || e->getPatrolLight() == 0)
			{
				if (e->getDirection() == NORTH)
				{
					sight = 0;
					for (int i = enemyY + 1; i < level->getSizeY(); ++i)
					{
						if (isWall(enemyX, i) || level->checkMap(enemyX, i) == C_DOOR_1 || level->checkMap(enemyX, i) == C_DOOR_2)
						{
							break;
						}
						sight += 1;
					}
					if (player->getXLocation() == enemyX && (player->getYLocation() > enemyY && player->getYLocation() <= enemyY + sight))
					{
						if (!playerSeen)
						{
							suspicionTime = time(nullptr);
						}
						playerSeen = true;
						e->playerSpotted = true;
						continue;
					}
					else
					{
						playerSeen = false;
						e->playerSpotted = false;
					}
				}
				else if (e->getDirection() == EAST)
				{
					sight = 0;
					for (int i = enemyX + 1; i < level->getSizeX(); ++i)
					{
						if (isWall(i, enemyY) || level->checkMap(i, enemyY) == C_DOOR_1 || level->checkMap(i, enemyY) == C_DOOR_2)
						{
							break;
						}
						sight += 1;
					}
					if (player->getYLocation() == enemyY && (player->getXLocation() > enemyX && player->getXLocation() <= enemyX + sight))
					{
						if (!playerSeen)
						{
							suspicionTime = time(nullptr);
						}
						playerSeen = true;
						e->playerSpotted = true;
						continue;
					}
					else
					{
						playerSeen = false;
						e->playerSpotted = false;
					}
				}
				else if (e->getDirection() == SOUTH)
				{
					sight = 0;
					for (int i = enemyY - 1; i >= 0; --i)
					{
						if (isWall(enemyX, i) || level->checkMap(enemyX, i) == C_DOOR_1 || level->checkMap(enemyX, i) == C_DOOR_2)
						{
							break;
						}
						sight += 1;
					}
					if (player->getXLocation() == enemyX && (player->getYLocation() < enemyY && player->getYLocation() >= enemyY - sight))
					{
						if (!playerSeen)
						{
							suspicionTime = time(nullptr);
						}
						playerSeen = true;
						e->playerSpotted = true;
						continue;
					}
					else
					{
						playerSeen = false;
						e->playerSpotted = false;
					}
				}
				else if (e->getDirection() == WEST)
				{
					sight = 0;
					for (int i = enemyY - 1; i >= 0; --i)
					{
						if (isWall(i, enemyY) || level->checkMap(i, enemyY) == C_DOOR_1 || level->checkMap(i, enemyY) == C_DOOR_2)
						{
							break;
						}
						sight += 1;
					}
					if (player->getYLocation() == enemyY && (player->getXLocation() < enemyX && player->getXLocation() >= enemyX - sight))
					{
						if (!playerSeen)
						{
							suspicionTime = time(nullptr);
						}
						playerSeen = true;
						e->playerSpotted = true;
						continue;
					}
					else
					{
						playerSeen = false;
						e->playerSpotted = false;
					}
				}
			}
			else if (e->getPatrolLight() != 0 && !e->getPatrolLight()->getStatus())
			{
				if (e->getDirection() == NORTH)
				{
					if (player->getXLocation() == enemyX && player->getYLocation() == enemyY + 1)
					{
						if (!playerSeen)
						{
							suspicionTime = time(nullptr);
						}
						playerSeen = true;
						e->playerSpotted = true;
						continue;
					}
					else
					{
						playerSeen = false;
						e->playerSpotted = false;
					}
				}
				else if (e->getDirection() == EAST)
				{
					if (player->getYLocation() == enemyY && player->getXLocation() == enemyX + 1)
					{
						if (!playerSeen)
						{
							suspicionTime = time(nullptr);
						}
						playerSeen = true;
						e->playerSpotted = true;
						continue;
					}
					else
					{
						playerSeen = false;
						e->playerSpotted = false;
					}
				}
				else if (e->getDirection() == SOUTH)
				{
					if (player->getXLocation() == enemyX && player->getYLocation() == enemyY - 1)
					{
						if (!playerSeen)
						{
							suspicionTime = time(nullptr);
						}
						playerSeen = true;
						e->playerSpotted = true;
						continue;
					}
					else
					{
						playerSeen = false;
						e->playerSpotted = false;
					}
				}
				else if (e->getDirection() == WEST)
				{
					if (player->getYLocation() == enemyY && player->getXLocation() == enemyX - 1)
					{
						if (!playerSeen)
						{
							suspicionTime = time(nullptr);
						}
						playerSeen = true;
						e->playerSpotted = true;
						continue;
					}
					else
					{
						playerSeen = false;
						e->playerSpotted = false;
					}
				}
				e->enemyState = FIXING;
			}
			if (e->enemyState == PATROLLING)
			{
				FollowPath(e, e->getCurrentPath());
			}
			else if (e->enemyState == FIXING)
			{
				if (!e->getPatrolLight()->getStatus())
				{
					if (e->actionComplete && e->getFixPath().size() == 0)
					{
						e->prevPathAction = e->currentPathAction;
						e->setPrevDestination(e->getDestination().x, e->getDestination().y);
						e->setPrevDirection(e->getDirection());
						vector<int> tempPath;
						FindPath((int)e->getLocationX() / 10, (int)e->getLocationZ() / 10, (int)e->getPatrolLight()->getLocationX(), 
							(int)e->getPatrolLight()->getLocationZ(), tempPath, e);

						e->setFixPath(tempPath);
						e->currentPathAction = 0;
						e->actionComplete = true;
					}
					int diffX = abs((int)e->getLocationX() / 10 - (int)e->getPatrolLight()->getLocationX());
					int diffY = abs((int)e->getLocationZ() / 10 - (int)e->getPatrolLight()->getLocationZ());
					if ((diffX == 1 && diffY == 0) || (diffX == 0 && diffY == 1))
					{
						e->fixPosition();
						e->getPatrolLight()->doAction();
						e->resetPath(e->getCurrentPath());
					}
				}
				else if (e->getPatrolLight()->getStatus())
				{
					if (e->getCurrentPath().size() == 0)
					{
						vector<int> tempPath;
						FindPath((int)e->getLocationX() / 10, (int)e->getLocationZ() / 10, e->getPrevDestination().x / 10,
							e->getPrevDestination().y / 10, tempPath, e);

						e->setFixPath(tempPath);
						e->currentPathAction = 0;
						e->actionComplete = true;
					}
					int diffX = abs((int)e->getLocationX() / 10 - e->getPrevDestination().x / 10);
					int diffY = abs((int)e->getLocationZ() / 10 - e->getPrevDestination().y / 10);
					if (diffX == 0 && diffY == 0)
					{
						e->resetPath(e->getFixPath());
						e->setCurrentPath(e->getPath());
						e->currentPathAction = e->prevPathAction;
						int d = (int)e->getPrevDirection() - (int)e->getDirection();
						if (d < 0)
						{
							for (int j = 0; j < abs(d); ++j)
								e->TurnLeft90();
						}
						else
						{
							for (int j = 0; j < d; ++j)
								e->TurnRight90();
						}
						e->fixPosition();
						e->enemyState = PATROLLING;
					}
				}
				int s = e->getCurrentPath().size();
				if (s > e->currentPathAction)
				{
					FollowPath(e, e->getCurrentPath());
				}
			}
			if (player->getXLocation() == enemyX && player->getYLocation() == enemyY)
			{
				playerSeen = true;
				gameState = GAMEOVER;
			}
			enemies.elementAt(i)->Frame();
		}
		if (playerSeen)
		{
			if (sound->GetCurrentSong() != 2)
			{
				sound->StopDesiredFile(sound->GetCurrentSong());
				sound->PlayDesiredFile(2, true);
			}
		}
		else
		{
			if (sound->GetCurrentSong() != 1)
			{
				sound->StopDesiredFile(sound->GetCurrentSong());
				sound->PlayDesiredFile(1, true);
			}
			suspicionTime = time(nullptr);
		}
		if (playerSeen && time(nullptr) - suspicionTime >= 3)
		{
			gameState = GAMEOVER;
		}
	}
}

void WorldClass::FollowPath(EnemyObject* e, vector<int> path)
{
	unsigned int cpa = e->currentPathAction;
	if (cpa > path.size() - 1)
	{
		e->currentPathAction = 0;
	}
	if (e->currentPathAction % 3 == 0)
	{
		if (e->actionComplete)
		{
			e->actionComplete = false;
			e->MoveForward(path[e->currentPathAction]);
			e->currentPathAction++;
		}
	}
	else if (e->currentPathAction % 3 == 1)
	{
		if (e->actionComplete)
		{
			e->actionComplete = false;
			e->Rest(path[e->currentPathAction]);
			e->currentPathAction++;
		}
	}
	else if (e->currentPathAction % 3 == 2)
	{
		if (e->actionComplete)
		{
			for (int j = 0; j < path[e->currentPathAction]; j++)
			{
				e->TurnRight90();
			}
			e->currentPathAction++;
			e->actionComplete = true;
		}
	}
}

void WorldClass::FindPath(int x, int y, int destX, int destY, vector<int>& p, EnemyObject* e)
{
	int i, j, k, l;
	int d[100][100];
	int visited[100][100];
	int sizeX = level->getSizeX();
	int sizeY = level->getSizeY();
	for (i = 0; i < sizeX; ++i)
	{
		for (j = 0; j < sizeY; ++j)
		{
			d[i][j] = INFINITE;
			if (isWall(i,j))
			{
				visited[i][j] = 1;
			}
			else
			{
				visited[i][j] = 0;
			}
		}
	}
	visited[destX][destY] = 0;

	d[x][y] = 0;
	k = x;
	l = y;
	vector<int> lastMove;
	vector<int> horOrVert;
	horOrVert.push_back(-1);

	while (!visited[destX][destY])
	{
		visited[k][l] = 1;

		if (d[k][l] + 1 < d[k+1][l] || d[k+1][l] == -1)
		{
			d[k+1][l] = d[k][l] + 1;
		}
		if (d[k][l] + 1 < d[k-1][l] || d[k-1][l] == -1)
		{
			d[k-1][l] = d[k][l] + 1;
		}
		if (d[k][l] + 1 < d[k][l+1] || d[k][l+1] == -1)
		{
			d[k][l+1] = d[k][l] + 1;
		}
		if (d[k][l] + 1 < d[k][l-1] || d[k][l-1] == -1)
		{
			d[k][l-1] = d[k][l] + 1;
		}
		if (!visited[k+1][l])
		{
			k += 1;
			horOrVert.push_back(1);
			lastMove.push_back(1);
			continue;
		}
		if (!visited[k-1][l])
		{
			k -= 1;
			horOrVert.push_back(1);
			lastMove.push_back(-1);
			continue;
		}
		if (!visited[k][l+1])
		{
			l += 1;
			horOrVert.push_back(0);
			lastMove.push_back(1);
			continue;
		}
		if (!visited[k][l-1])
		{
			l -= 1;
			horOrVert.push_back(0);
			lastMove.push_back(-1);
			continue;
		}
		if (visited[k+1][l] && visited[k-1][l] && visited[k][l+1] && visited[k][l-1])
		{
			if (horOrVert.back() == 1)
			{
				k -= lastMove.back();
				lastMove.pop_back();
				horOrVert.pop_back();
			}
			else if (horOrVert.back() == 0)
			{
				l -= lastMove.back();
				lastMove.pop_back();
				horOrVert.pop_back();
			}
			else if (horOrVert.back() == -1)
			{
				break;
			}
		}
	}

	vector<XMINT2> rpath;
	vector<XMINT2> path;
	k = destX;
	l = destY;
	rpath.push_back(XMINT2(k, l));
	for (i = 0; i < d[destX][destY]; ++i)
	{
		if (d[k+1][l] == d[k][l] - 1 && !isWall(k+1, l))
		{
			k += 1;
		}
		else if (d[k-1][l] == d[k][l] - 1 && !isWall(k-1, l))
		{
			k -= 1;
		}
		else if (d[k][l+1] == d[k][l] - 1 && !isWall(k, l+1))
		{
			l += 1;
		}
		else if (d[k][l-1] == d[k][l] - 1 && !isWall(k, l-1))
		{
			l -= 1;
		}
		else
		{
			break;
		}
		rpath.push_back(XMINT2(k,l));
	}
	rpath.pop_back();
	vector<XMINT2> temp = rpath;
	for (unsigned int n = 0; n < rpath.size(); ++n)
	{
		path.push_back(rpath[rpath.size()-1-n]);
	}
	if (isWall(destX, destY))
	{
		path.pop_back();
	}
	p = convertPath(x, y, path, e);
}

vector<int> WorldClass::convertPath(int x, int y, vector<XMINT2>& path, EnemyObject* e)
{
	vector<int> p;
	p.push_back(0);
	p.push_back(3);
	Direction d = NORTH;
	Direction prevd;
	if (path[0].x - x > 0) d = EAST;
	if (path[0].y - y < 0) d = SOUTH;
	if (path[0].x - x < 0) d = WEST;
	if (d == NORTH)
	{
		if ((int)d - (int)e->getDirection() < 0)
			p.push_back((int)d - (int)e->getDirection() + 4);
		else
			p.push_back((int)d - (int)e->getDirection());
	}
	else if (d == EAST)
	{
		if ((int)d - (int)e->getDirection() < 0)
			p.push_back((int)d - (int)e->getDirection() + 4);
		else
			p.push_back((int)d - (int)e->getDirection());
	}
	else if (d == SOUTH)
	{
		if ((int)d - (int)e->getDirection() < 0)
			p.push_back((int)d - (int)e->getDirection() + 4);
		else
			p.push_back((int)d - (int)e->getDirection());
	}
	else if (d == WEST)
	{
		p.push_back((int)d - (int)e->getDirection());
	}
	prevd = d;
	for (unsigned int i = 0; i < path.size(); ++i)
	{
		p.push_back(1);
		p.push_back(0);
		XMINT2 point;
		if (i < path.size() - 1)
		{
			point = path[i+1];
		}
		else  if (i == path.size() - 1)
		{
			p.push_back(2);
			break;
		}
		d = NORTH;
		if (path[i].x - point.x < 0) d = EAST;
		if (path[i].y - point.y > 0) d = SOUTH;
		if (path[i].x - point.x > 0) d = WEST;
		if (d == NORTH)
		{
			if ((int)d - (int)prevd < 0)
				p.push_back((int)d - (int)prevd + 4);
			else
				p.push_back((int)d - (int)prevd);
		}
		else if (d == EAST)
		{
			if ((int)d - (int)prevd < 0)
				p.push_back((int)d - (int)prevd + 4);
			else
				p.push_back((int)d - (int)prevd);
		}
		else if (d == SOUTH)
		{
			if ((int)d - (int)prevd < 0)
				p.push_back((int)d - (int)prevd + 4);
			else
				p.push_back((int)d - (int)prevd);
		}
		else if (d == WEST)
		{
			p.push_back((int)d - (int)prevd);
		}
		prevd = d;
	}
	return p;
}

bool WorldClass::GameMenu()
{
	return gameState == MENU;
}

bool WorldClass::GamePlaying()
{
	return gameState == PLAYING;
}

bool WorldClass::GameOver()
{
	return gameState == GAMEOVER;
}

void WorldClass::StartGame()
{
	gameState = PLAYING;
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
	{
		if (!checkLight() && (level->checkMap(x+1, y+1) == C_LIGHT_1 ||
			level->checkMap(x+1, y+1) == C_LIGHT_2 || 
			level->checkMap(x+1, y+1) == C_LIGHT_3 ||
			level->checkMap(x+1, y+1) == C_LIGHT_4))
		{
			return;
		}
		if(level->getLocation(x+1, y+1)->doAction())
			return;
	}
	if(level->getLocation(x, y+1))
	{
		if (!checkLight() && (level->checkMap(x, y+1) == C_LIGHT_1 ||
			level->checkMap(x, y+1) == C_LIGHT_2 || 
			level->checkMap(x, y+1) == C_LIGHT_3 ||
			level->checkMap(x, y+1) == C_LIGHT_4))
		{
			return;
		}
		if(level->getLocation(x, y+1)->doAction())
			return;
	}
	if(level->getLocation(x+1, y))
	{
		if (!checkLight() && (level->checkMap(x+1, y) == C_LIGHT_1 ||
			level->checkMap(x+1, y) == C_LIGHT_2 || 
			level->checkMap(x+1, y) == C_LIGHT_3 ||
			level->checkMap(x+1, y) == C_LIGHT_4))
		{
			return;
		}
		if(level->getLocation(x+1, y)->doAction())
			return;
	}
	if(level->getLocation(x-1, y-1))
	{
		if (!checkLight() && (level->checkMap(x-1, y-1) == C_LIGHT_1 ||
			level->checkMap(x-1, y-1) == C_LIGHT_2 || 
			level->checkMap(x-1, y-1) == C_LIGHT_3 ||
			level->checkMap(x-1, y-1) == C_LIGHT_4))
		{
			return;
		}
		if(level->getLocation(x-1, y-1)->doAction())
			return;
	}
	if(level->getLocation(x-1, y))	
	{
		if (!checkLight() && (level->checkMap(x-1, y) == C_LIGHT_1 ||
			level->checkMap(x-1, y) == C_LIGHT_2 || 
			level->checkMap(x-1, y) == C_LIGHT_3 ||
			level->checkMap(x-1, y) == C_LIGHT_4))
		{
			return;
		}
		if(level->getLocation(x-1, y)->doAction())
			return;
	}
	if(level->getLocation(x, y-1))
	{
		if (!checkLight() && (level->checkMap(x, y-1) == C_LIGHT_1 ||
			level->checkMap(x, y-1) == C_LIGHT_2 || 
			level->checkMap(x, y-1) == C_LIGHT_3 ||
			level->checkMap(x, y-1) == C_LIGHT_4))
		{
			return;
		}
		if(level->getLocation(x, y-1)->doAction())
			return;
	}
	if(level->getLocation(x+1, y-1))
	{
		if (!checkLight() && (level->checkMap(x+1, y-1) == C_LIGHT_1 ||
			level->checkMap(x+1, y-1) == C_LIGHT_2 || 
			level->checkMap(x+1, y-1) == C_LIGHT_3 ||
			level->checkMap(x+1, y-1) == C_LIGHT_4))
		{
			return;
		}
		if(level->getLocation(x+1, y-1)->doAction())
			return;
	}
	if(level->getLocation(x-1, y+1))
	{
		if (!checkLight() && (level->checkMap(x-1, y+1) == C_LIGHT_1 ||
			level->checkMap(x-1, y+1) == C_LIGHT_2 || 
			level->checkMap(x-1, y+1) == C_LIGHT_3 ||
			level->checkMap(x-1, y+1) == C_LIGHT_4))
		{
			return;
		}
		if(level->getLocation(x-1, y+1)->doAction())
			return;
	}
	if(level->getLocation(x, y))
	{
		if (!checkLight() && (level->checkMap(x, y) == C_LIGHT_1 ||
			level->checkMap(x, y) == C_LIGHT_2 || 
			level->checkMap(x, y) == C_LIGHT_3 ||
			level->checkMap(x, y) == C_LIGHT_4))
		{
			return;
		}
		if(level->getLocation(x, y)->doAction())
			return;
	}
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

void WorldClass::UpdatePlayerWalk(bool walking)
{
	if (walking && !playerWalking)
	{
		sound->PlayDesiredFile(5, true);
		playerWalking = true;
	}
	else if (!walking && playerWalking)
	{
		sound->StopDesiredFile(5);
		playerWalking = false;
	}
	else
	{
		return;
	}
}

void WorldClass::setStartTime()
{
	startTime = time(nullptr);
}

time_t WorldClass::getElapsedTime()
{
	time_t t = currTime - startTime;
	return t;
}