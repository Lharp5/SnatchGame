/* worldClass ::: Luke Harper */

#ifndef WORLDCLASS_H
#define WORLDCLASS_H

#include "levelclass.h"
#include "PlayerClass.h"
#include "enemyobject.h"

class WorldClass
{
public:
	WorldClass();
	~WorldClass();
	void runGame();
	void toggleFloor();

	ArrayList<GameModel> getModels(); //models to be sent back to the system for rendering.

	/************
	*	Function:	Get Player
	*	Purpose:	Returns the Player as a pointer.
	************/
	PlayerClass* getPlayer();

	/************
	*	Function:	GetPlayerStartX
	*	Purpose:	Returns the world co-ordinates of the start position for the player.
	************/
	float getPlayerStartX();
	/************
	*	Function:	GetPlayerStartX
	*	Purpose:	Returns the world co-ordinates of the start position for the player.
	************/
	float getPlayerStartY();
	/************
	*	Function:	GetPlayerStartX
	*	Purpose:	Returns the world co-ordinates of the start position for the player.
	************/
	float getPlayerStartZ();

private:
	//objects
	LevelClass* level;
	ArrayList<GameModel> renderModels; //Lists of models that can be stored so they can be rendered.
	GameModel* floor[100][100];
	GameModel* roof[100][100];

	PlayerClass* player;

	//int worldSize;

	//functions

	//setting up the default world.
	void initalizeWorld();
	void initalizeRoof();
	void initalizeFloor();

	//removing the world
	void Shutdown();

	void Menu();
	void playGame();
	void advanceLevel();
	void endGame();
};

#endif
