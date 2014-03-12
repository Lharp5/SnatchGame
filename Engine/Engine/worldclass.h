/* worldClass ::: Luke Harper */

#ifndef WORLDCLASS_H
#define WORLDCLASS_H

#include "levelclass.h"

class WorldClass
{
public:
	WorldClass();
	~WorldClass();
	void runGame();
	void getModels(ArrayList<GameModel>*); //models to be sent back to the system for rendering.
private:
	//objects
	LevelClass levels;
	ArrayList<GameModel>* renderModels; //Lists of models that can be stored so they can be rendered.
	GameModel* floor[100][100];
	GameModel* roof[100][100];

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
