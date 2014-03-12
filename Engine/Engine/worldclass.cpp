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


void WorldClass::Shutdown()
{
	/*for(int i=0; i<100; i++){
		for(int j=1; j<100; j++){
			if(floor[i][j] != NULL)
				delete floor[i][j];
			if(roof[i][j] !=NULL)
				delete roof[i][j];
		}
	}*/

	delete [] floor;
	delete [] roof;
	wchar_t* outstring = L"World Shutdown..";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}


void WorldClass::initalizeRoof()
{
	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++){
			roof[i][j] =  new QuadTexturedModel(10.0f, 10.0f, L"../Engine/textures/die1.dds");
			roof[i][j]->worldTranslate(10.0f*i, 15.0f,10.0f*j);
			roof[i][j]->worldRotateX(-XM_PIDIV2);
		}
	}
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