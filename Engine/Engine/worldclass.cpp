/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	worldClass
*	Date:		feb. 21/14
**************************/

#include "worldclass.h"

WorldClass::WorldClass()
{
	renderModels =0;

	initalizeWorld();
}

void WorldClass::initalizeWorld()
{
	initalizeRoof();
	initalizeFloor();
}

void WorldClass::initalizeRoof()
{
}

void WorldClass::initalizeFloor()
{
	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++){
			floor[i][j] =  new QuadTexturedModel(10.0f, 10.0f, L"../Engine/textures/die1.dds");
			floor[i][j]->worldTranslate(10.0f*i, -5.0f,10.0f*j);
			floor[i][j]->worldRotateX(XM_PIDIV2);
		}
	}
	
}