/* worldClass ::: Luke Harper */

#ifndef WORLDCLASS_H
#define WORLDCLASS_H

#include "levelclass.h"
#include "PlayerClass.h"
#include "enemyobject.h"
#include <math.h>

class WorldClass
{
public:
	WorldClass();
	~WorldClass();
	void runGame();
	void toggleFloor();
	void doAction();
	
	/*********
	*	Function:	checkLight
	*	out:		boolean whether light is on or off
	*	Purpose:	to check location of the player and determine if that floor is lit up.
	**********/
	bool checkLight();
	bool updatePlayer(float, float);

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


	//functions

	//setting up the default world.
	void initalizeWorld();
	void initalizeRoof();
	void initalizeFloor();

	/************	
	*	Function:	ConvertToInt
	*	in:			number as a float
	*	out:		number as an int
	*	Purpose:	To convert a number from float to int
	************/
	int convertToInt(float);

	//removing the world
	void Shutdown();

	void Menu();
	void playGame();
	void advanceLevel();
	void endGame();
	void updateLight(int,int);
	void scan(int, int);
};

#endif
