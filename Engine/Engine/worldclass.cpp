/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	worldClass
*	Date:		feb. 21/14
**************************/

#include "worldclass.h"

WorldClass::WorldClass():worldSize(50), floorImage(L"../Engine/textures/tireTread.dds"), roofImage(L"../Engine/textures/tireTread.dds")
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
	levels = new LevelClass();
	//initalizeRoof();
	//initalizeFloor();
	
	/*for(int i=0; i<worldSize; i++){
		for(int j=0; j<worldSize; j++){
			renderModels.add(roof[i][j]); 
			renderModels.add(floor[i][j]);
		}
		//renderModels.add(roof[0][0]);
	}*/

	levels->loadLevel(0);
	
	//NEEDS TO FINISH THIS CLASS

	renderModels.addAll(levels->getGameModels());
	
	
	wchar_t* outstring = L"Models added..";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}


void WorldClass::Shutdown()
{
	wchar_t* outstring = L"World Shutdown..";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

ArrayList<GameModel> WorldClass::getModels()
{
	wchar_t* outstring = L"Adding models Uh OH!!!";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
	return renderModels;
}

void WorldClass::initalizeRoof()
{
	for(int i=0; i<worldSize; i++){
		for(int j=0; j<worldSize; j++){
			roof[i][j] =  new QuadTexturedModel(10.0f, 10.0f, roofImage);
			roof[i][j]->worldTranslate(10.0f*i, 15.0f,10.0f*j);
			roof[i][j]->worldRotateX(-XM_PIDIV2);
		}
	}
}

void WorldClass::initalizeFloor()
{
	for(int i=0; i<worldSize; i++){
		for(int j=0; j<worldSize; j++){
			floor[i][j] =  new QuadTexturedModel(10.0f, 10.0f, floorImage);
			floor[i][j]->worldTranslate(10.0f*i, -5.0f,10.0f*j);
			floor[i][j]->worldRotateX(XM_PIDIV2);
		}
	}
	
}

void WorldClass::toggleFloor()
{
	//levels->toggleFloor();
}