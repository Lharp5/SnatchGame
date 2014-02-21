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
	sizeX =10;
	sizeY=10;
	wchar_t* outstring = L"Level Loaded";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

//probably needed more later
LevelClass::~LevelClass()
{
	Shutdown();
	wchar_t* outstring = L"Level Closed";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}


/* Function:	Shutdown
 * Purpose:		To free up any pointers, close any files.
*/
void LevelClass::Shutdown()
{
	wchar_t* outstring = L"Shutting Level Down....";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}

/* Function:	getPlayerLocation
 * Purpose:		to find the player on the map.
 * in/out:		X and Y position of the player.
*/
void LevelClass::getPlayerLocation(int* x, int* y)
{
	for(int i=0; i<sizeX; i++)
		for(int j=0; j<sizeY; j++)
			if(map[i][j] == player){
				*x = i;
				*y = j;
			}
}


/* Function:	CheckLocation
 * Purpose:		To see if there exists an object at a location.
 * in:			X and Y coordinates to check.
 * out:			Pointer to object that exists there - null otherwise.
 */
GameObject* LevelClass::CheckLocation(int x, int y)
{
	return NULL;
}