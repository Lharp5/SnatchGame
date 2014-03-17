////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"
# include <iostream>
SystemClass::SystemClass()
{
	//set pointers to our objects to null so if initialization of them
	//fails they will not mistakenly be used to clean up memory
	m_Input = 0;  
	m_Graphics = 0;
	m_Camera = 0;
	m_GameModels = new ArrayList<GameModel>();
	keyPressedE = false;
	prevEPressedState = false;
}


SystemClass::SystemClass(const SystemClass& other)
{
	//always implmement your own copy constructor even if it does nothing
}


SystemClass::~SystemClass()
{
	//Always implement your own destructor even if it does nothing.
	//If your class will ever have subclasses (through inheritance) then make the 
	//destructor virtual as in
	// virtual SystemClass::~SystemClass(){...}
	// otherwise you will likely have memory leaks
}


bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;
	spacePressed = false;

	// Initialize the width and height of the screen to zero before sending the variables into 
	// InitializeWindows() function which will cause them to get set.
	// They are passed in by reference so can be set from within the InitializeWindows() function

	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	// Create the actual window. This screenWidth and screenHeight variables will get set
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new DirectInputClass;
	if(!m_Input)
	{
		return false;
	}
		// Initialize the input object.
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initalize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Camera object.
	m_Camera = new CineCameraClass(screenWidth,screenHeight);
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -20.0f); //10 units along Z in front of origin
	m_Camera->SetDirection(0.0f, 0.0f, 1.0f); //look in positive Z direction
	m_Camera->SetUpDirection(0.0f, 1.0f, 0.0f); //up points in positive Y direction
	/*IMPORTANT:  note camera direction and up must be orthogonal */

	//Create the game objects for our game

	//Set up some colors that are variations of each other
	//e.g. various shades of brown

	XMFLOAT4 quadColor = XMFLOAT4(0.0f, 76.0f/255, 153.0f/255, 1.0f);  //for use with QuadModel
	//make a background textured quad

	WCHAR * backdropTextureFileName = L"../Engine/textures/cloudy_backdrop.dds";

	float backdropWidthX = 100.0f;
	float backdropHeightY = 80.0f;

	//make a background textured quad
	m_backDrop = new QuadTexturedModel(
		                     backdropWidthX,  //length in X direction
							 backdropHeightY,  //length in Y direction
							 backdropTextureFileName  //path name of .dds texture file
							 );

    float distanceBackZ = 100;
	m_backDrop->worldTranslate(0.0f, 0.0f, distanceBackZ); //move to location in the world

	WCHAR * groundCoverTextureFileName = L"../Engine/textures/graph_paper.dds";

	float groundCoverWidthX = 100.0f;
	float groundCoverHeightY = 100.0f;

	//make a ground cover textured quad
	m_groundCover = new QuadTexturedModel(
		                     groundCoverWidthX,  //length in X direction
							 groundCoverHeightY,  //length in Y direction
							 groundCoverTextureFileName  //path name of texture .dds texture file
							 );

	m_groundCover->orientRotateX(XM_PIDIV2); //rotate 90 degrees around X so it is parallel to XZ ground plane
	m_groundCover->worldTranslate(0.0f, -backdropHeightY/2, groundCoverHeightY/2); //move to location in the world
	
	m_enemy = new EnemyObject(15.0f, -1.85f, 60.0f, 5.0f);

	m_World = new WorldClass();

	m_lightMask = new LightMask(m_Camera->GetPosition());
	
	//Add the  gameModel objects to the GameModels collection
	//that will be rendered by the graphics system

	m_GameModels->add(m_backDrop);
	m_GameModels->add(m_groundCover);
	m_GameModels->addAll(m_enemy->GetGameModels());

	m_GameModels->addAll(m_World->getModels());

	m_GameModels->addAll(m_lightMask->GetModels());

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object. 	Engine.exe!WinMain(HINSTANCE__ * hInstance, HINSTANCE__ * hPrevInstance, char * pScmdline, int iCmdshow) Line 21	C++
	// The Graphics::Initialize will also call back into our game objects an initialize their ModelClass objects once the GraphicsClass has had
	// a chance to initialize

	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd, m_Camera, m_GameModels);
	
	wchar_t* outstring = L"Rendered";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
	if(!result)
	{
		return false;
	}

	m_Camera->SetPosition(m_World->getPlayerStartX(), m_World->getPlayerStartY(), m_World->getPlayerStartZ());
	prevCamPos = m_Camera->GetPosition();
	return true;
}


void SystemClass::Shutdown()
{
	//Shut down our game character objects and release their memory

	if(m_World)
	{
		delete m_World;
		m_World = 0;
	}

	if(m_backDrop)
	{
		m_backDrop->Shutdown();
		delete m_backDrop;
		m_backDrop = 0;
	}

	if(m_groundCover)
	{
		m_groundCover->Shutdown();
		delete m_groundCover;
		m_groundCover = 0;
	}

	if(m_enemy)
	{
		m_enemy->shutdown();
		delete m_enemy;
		m_enemy = 0;
	}

	// Release the Light Mask object's memory.
	if(m_lightMask)
	{
		m_lightMask->Shutdown();
		delete m_lightMask;
		m_lightMask = 0;
	}

	//release the memory for the m_GameModels collection
	//all objects in it should have been released my the code immediately above
	if(m_GameModels)
	{
		delete m_GameModels;
		m_GameModels = 0;
	}

	//Shut down the graphics pipeline object and release its memory
	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object's memory.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

    // Release the camera object's memory.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Shutdown the actual Window's window.
	ShutdownWindows();
	
	return;
}


void SystemClass::Run()
{
	/*
	The Run function is where our application will loop and do all the application processing until we decide to quit. 
	The application processing is done in the Frame() function which is called each loop. 
	This is an important concept to understand as now the rest of our application must be written with this in mind. 
	The pseudo code looks like the following: 

	while not done {
        check for windows system messages
        process system messages
        process application loop
        check if user wanted to quit during the frame processing
		}


	*/
	MSG msg;
	bool done, result;

	//std::cout<< "Running through code " << std::endl;
	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}

		//check if the user pressed escape and wants to quit
		
		if(m_Input->IsEscapePressed() == true)
			done = true;

	}

	return;
}


bool SystemClass::Frame()
{
	/*
	The following Frame function is where all the processing for our application is done. 
	So far it is fairly simple, we check the input object to see if the user has pressed escape and wants to quit. 
	If they don't want to quit then we call the graphics object to do its frame processing 
	which will render the graphics for that frame. 
	As the application grows we'll place more code here. 
	*/
	
	/*
	Apply transformations to the game objects
	*/

	//Rotate the object a bit around some axis
	
	m_World->runGame();

	if(m_World->checkLight())
		LightMask::lightState = LightState::ON;
	else
		LightMask::lightState = LightState::OFF;

	//Handle user inputs
	bool result;

	result = m_Input->Frame();
	if(!result)
		return false;

	
	// Check if the user pressed escape and wants to exit the application.
	if(!checkControls())
		return false;
	
	//Move camera or models based on input
	
	m_lightMask->frame(m_Camera->GetPosition());

	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame();
	if(!result)
	{
		return false;
	}
	
	SetCursorPos(GetSystemMetrics(SM_CXSCREEN)  / 2, GetSystemMetrics(SM_CYSCREEN)  / 2);

	return true;
}


bool SystemClass::checkControls()
{	
	//Move camera or models based on input
	//We will combinations for a key + arrow keys to control the camera
	if(m_Input->keyPressed(DIK_SPACE)){
		if(!spacePressed)
			m_World->doAction();
		spacePressed = true;
	}
	else{
		spacePressed = false;
	}
	if ( m_Input->keyPressed(DIK_LSHIFT)){   
		if ( m_Input->keyPressed(DIK_LEFT))
		   m_enemy->TurnLeft();
	   if ( m_Input->keyPressed(DIK_RIGHT))
		   m_enemy->TurnRight();
	   if ( m_Input->keyPressed(DIK_UP))
		   m_enemy->MoveForward();
	}
	 else if ( m_Input->keyPressed(DIK_C)){
	   if ( m_Input->keyPressed(DIK_UP) ) //Crane Up
		  m_Camera->CraneUp();
	   if ( m_Input->keyPressed(DIK_DOWN) ) //Crane Down
		  m_Camera->CraneDown();	
	}
	else if ( m_Input->keyPressed(DIK_R)){

	   if ( m_Input->keyPressed(DIK_LEFT) ) //Roll Left
		  m_Camera->RollLeft();
	   if ( m_Input->keyPressed(DIK_RIGHT) ) //Roll Right
		  m_Camera->RollRight();	
	}
	else if ( m_Input->keyPressed(DIK_Z)){

	   if ( m_Input->keyPressed(DIK_UP) ) //Zoom In
		  m_Camera->ZoomIn();
	   if ( m_Input->keyPressed(DIK_DOWN) ) //Zoom Out
		  m_Camera->ZoomOut();	
	}
	else{
	   if ( m_Input->keyPressed(DIK_A) ){ //Move Camera Left			
			m_Camera->StrafeLeft();
			if(!(m_World->updatePlayer(m_Camera->GetPosition().x, m_Camera->GetPosition().z)))
				m_Camera->SetPosition(prevCamPos.x, prevCamPos.y, prevCamPos.z);
			else
				prevCamPos = m_Camera->GetPosition();
	   }

	   if ( m_Input->keyPressed(DIK_D) ){ //Move Camera Right
			m_Camera->StrafeRight();
			if(!(m_World->updatePlayer(m_Camera->GetPosition().x, m_Camera->GetPosition().z)))
				m_Camera->SetPosition(prevCamPos.x, prevCamPos.y, prevCamPos.z);
			else
				prevCamPos = m_Camera->GetPosition();
	   }

	   if ( m_Input->keyPressed(DIK_W) ){ //Camera Move Forward
		  m_Camera->MoveForward();
		  if(!(m_World->updatePlayer(m_Camera->GetPosition().x, m_Camera->GetPosition().z)))
				m_Camera->SetPosition(prevCamPos.x, prevCamPos.y, prevCamPos.z);
			else
				prevCamPos = m_Camera->GetPosition();
	   }
	   if ( m_Input->keyPressed(DIK_S) ){ //Camera Pull Back
		  m_Camera->MoveBackward();
		  if(!(m_World->updatePlayer(m_Camera->GetPosition().x, m_Camera->GetPosition().z)))
				m_Camera->SetPosition(prevCamPos.x, prevCamPos.y, prevCamPos.z);
			else
				prevCamPos = m_Camera->GetPosition();
	   }
	   if ( m_Input->keyPressed(DIK_E) )
	   {
		   if (!keyPressedE)
		       LightMask::lightState = LightMask::lightState == LightState::OFF ? LightState::ON : LightState::OFF;
		   keyPressedE = true;
	   }
	   else
	   {
			keyPressedE = false;
	   }
	   
	   if ( m_Input->keyPressed(DIK_LEFT) ) //Pan Camera Left
	      m_Camera->PanLeft();

	   if ( m_Input->keyPressed(DIK_RIGHT) ) //Pan Camera Right
	      m_Camera->PanRight();
	   
	   if ( m_Input->keyPressed(DIK_UP) ) //Tilt Camera Downward
		  m_Camera->TiltUp();

	   if ( m_Input->keyPressed(DIK_DOWN) ) //Tilt Camera Upward
		  m_Camera->TiltDown();	
	   
	   
	}
	int x, y;
	m_Input->GetMouseDisplacement(x, y);
	if (abs(x) > 0 || abs(y) > 0)
	{
		wchar_t s[32];
		wsprintf(s, L"Mouse Displacement: %d, %d\n", x, y);
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), s, wcslen(s), NULL, NULL);
		m_Camera->CameraAim(x, y);
	}

	//user is still playing
	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	//removed all the jargan quote "Direct Input handles all of this for now"
		return DefWindowProc(hwnd, umsg, wparam, lparam);
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	/*
	The InitializeWindows will build the actual Windows window we will render to. 
	It sets (returns)  screenWidth and screenHeight back to the calling function
	so these values can be used throughout the application. 
	
	We create the window using some default settings to initialize a plain black window with no borders. 
	The function will make either a small window or make a full screen window depending on 
	the true or false setting of the global variable called FULL_SCREEN. 
	If this is set to true then we make the screen cover the entire users desktop window. 
	If it is set to false we just make a 800x600 window in the middle of the screen. 
	The FULL_SCREEN global variable at the top of the graphicsclass.h file in case you want to modify it. 
	
	It will make sense later why it is placed in that file instead of the header for this file.
	*/
	WNDCLASSEX wc; //struct which describes the window class (properties of the window)

	DEVMODE dmScreenSettings;
	int posX, posY;


	// Set an external static pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Engine"; //Long-character, or wchar, string

	// Setup the windows class with default settings.
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //http://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
	wc.lpfnWndProc   = WndProc; //our procedure to call back on window events
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hinstance; //set window's application to this application
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW); //use standard arrow cursor for window (when shown)
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //brush for painting background colour
	wc.lpszMenuName  = NULL; //we have no menus with our window
	wc.lpszClassName = m_applicationName; //name of our application
	wc.cbSize        = sizeof(WNDCLASSEX);  //size of this structure in bytes
	
	// Register the window class.
	// The window class must be registered with Window's OS before the window
	// can actually be created.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = 1200;
		screenHeight = 700;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	//http://msdn.microsoft.com/en-us/library/windows/desktop/ms632679(v=vs.85).aspx

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, 
		                    m_applicationName, 
							m_applicationName, 
						    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_CAPTION, //WS_CAPTION for border with title
						    posX,  //screen X of window's top left corner
							posY, //creen Y of windowns's top left corner
							screenWidth,  //width of screen
							screenHeight, //height of screen
							NULL, 
							NULL, 
							m_hinstance, //the application instance
							NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW); //show  the window
	SetForegroundWindow(m_hwnd); //make window the foreground window
	SetFocus(m_hwnd);            //give window input focus

	// Hide the mouse cursor if you don't want it over your game window.
	ShowCursor(false);
	SetCursorPos(GetSystemMetrics(SM_CXSCREEN)  / 2, GetSystemMetrics(SM_CYSCREEN)  / 2);

	return;
}


void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor again.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}

}
