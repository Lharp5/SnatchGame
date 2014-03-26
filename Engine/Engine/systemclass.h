////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

#define WIN32_LEAN_AND_MEAN 
// defining "lean and mean" will leave of some windows API's and keep the system stripped down

//////////////
// INCLUDES //
//////////////
#include <windows.h> //needed to create and destroy windows and call Win32 functions


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "directinputclass.h"
#include "graphicsclass.h"
#include "gamemodel.h"
#include "arraylist.h"
#include "cinecameraclass.h"
#include "enemyobject.h"
#include "DoorObject.h"
#include "enemymodel.h"
#include "levelclass.h"
#include "lightmask.h"
#include "soundclass.h"
#include "worldclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: SystemClass
// The System class is our encapsulation of our application.
// This is really the entry from the windows framework into our own code
////////////////////////////////////////////////////////////////////////////////
class SystemClass
{
public:
	SystemClass(); //default constructor
	SystemClass(const SystemClass&); //copy constructor
	~SystemClass(); //destructor

	bool Initialize();
	void Shutdown();
	void Run();

	//This method is used to intercept the windows messages
	//This is how windows messages or events get into out application
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	bool checkControls();

private:


	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;  //handle to the Windows window (client window for the application)

	DirectInputClass* m_Input; //out input class object from which to obtain user inputs
	GraphicsClass* m_Graphics; //our graphics class object that encapsulates the graphics pipeline
	CineCameraClass * m_Camera; //our encapsulation of where the camera is looking at our world

	//Game World Items

	ArrayList<GameModel>* m_GameModels; //container to hold all our game world models
	WorldClass* m_World;
	LightMask* m_lightMask;

	bool spacePressed;
	bool prevSpacePressed;

	XMFLOAT3 prevCamPos;

	bool keyPressedE;
	bool prevEPressedState;

	XMFLOAT3 velocityVector;

	//move movement?




};





/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////

//This is where windows will direct messages to.
//This will get set to our SystemClass object when 
//System intialize is called.
static SystemClass* ApplicationHandle = 0;


#endif