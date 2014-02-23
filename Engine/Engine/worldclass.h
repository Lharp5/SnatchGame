/* worldClass ::: Luke Harper */

#ifndef WORLDCLASS_H
#define WORLDCLASS_H

#include "levelclass.h"

class worldClass
{
public:
	void runGame();
	void getModels(ArrayList<GameModel>*); //models to be sent back to the system for rendering.
private:
	//objects
	LevelClass levels;
	ArrayList<GameModel>* renderModels; //Lists of models that can be stored so they can be rendered.

	//functions
	void Menu();
	void playGame();
	void advanceLevel();
	void endGame();
};

#endif
