/**************************
*	Project:	Snatch
*	Name:		Luke Harper
*	Program:	LevelClass
*	Date:		feb. 19/14
**************************/
#include "levelclass.h"


//creating a base level THE TEMP LEVEL
LevelClass::LevelClass()
{
	initialize();
	loadLevel(0);
	wchar_t* outstring = L"...Levels Loaded\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

//probably needed more later
LevelClass::~LevelClass()
{
	Shutdown();
	wchar_t* outstring = L"Levels Closed";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

/* Function:	initalize 
 * Purpose:		to initalize the map.
*/
void LevelClass::initialize()
{
	sizeX = 100;
	sizeY = 100;

	for(int i=0; i<sizeX; i++){
		for(int j=0; j<sizeY; j++){
			map[i][j] = NULL;
		}
	}
}


/* Function:	loadLevel 
 * Purpose:		to change the level
 * in:			the level wishing to be assigned as an int.
*/
void LevelClass::loadLevel(int level)
{
	switch(level){
	case 1:		break;
	case 2:		break;
	case 3:		break;
	case 4:		break;
	default:	level0(); break;
	}
}

/* Function:	loadLevel 
 * Purpose:		To assign level 1 to the map
*/
void LevelClass::level0()
{
	sizeX = 10;
	sizeY = 10;

	for(int i=0; i<sizeX; i++){
		for(int j=0; j<sizeY; j++){
			map[i][j] = new FloorObject(10.0f*i,10.0f*j);
		}
	}
	wchar_t* outstring = L"Level 0: Loaded\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}
/* Function:	Shutdown
 * Purpose:		To free up any pointers, close any files.
*/
void LevelClass::Shutdown()
{
	for(int i=0; i<sizeX; i++){
		for(int j=1; j<sizeY; j++){
			if(map[i][j] != NULL)
				delete map[i][j];
		}
	}
	wchar_t* outstring = L"Levels Shutdown..";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

/* Function:	getPlayerLocation
 * Purpose:		to find the player on the map.
 * in/out:		X and Y position of the player.
*/
void LevelClass::getPlayerLocation(int* x, int* y)
{
/*	for(int i=0; i<sizeX; i++)
		for(int j=0; j<sizeY; j++)
			if(map[i][j] == player){
				*x = i;
				*y = j;
			}
*/}

int LevelClass::getSizeX()
{
	return sizeX;
}

int LevelClass::getSizeY()
{
	return sizeY;
}

GameObject* LevelClass::CheckLocation(int x, int y)
{
	return map[x][y];
}

/* Function:	CheckLocation
 * Purpose:		To see if there exists an object at a location.
 * in:			X and Y coordinates to check.
 * out:			Pointer to object that exists there - null otherwise.
 */
