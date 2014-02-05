////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"

SystemClass::SystemClass()
{
	//set pointers to our objects to null so if initialization of them
	//fails they will not mistakenly be used to clean up memory
	m_Input = 0;  
	m_Graphics = 0;
	m_Camera = 0;
	m_GameModels = new ArrayList<GameModel>();
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


	// Initialize the width and height of the screen to zero before sending the variables into 
	// InitializeWindows() function which will cause them to get set.
	// They are passed in by reference so can be set from within the InitializeWindows() function

	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	// Create the actual window. This screenWidth and screenHeight variables will get set
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}
		// Initialize the input object.
	m_Input->Initialize();


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
	float quadLengthX = 4.0f;
	float quadLengthY = 4.0f;
	m_blueQuad = new QuadModel(
		                     quadLengthX,  //length in X direction
							 quadLengthY,  //length in Y direction
							 &quadColor  //pointer to color
							 );
	m_blueQuad->worldTranslate(-5.0f, -quadLengthY, -3.0f); //move to location in the world

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

	//for the Coke SIGN copying the background quad info
	WCHAR * signTexture = L"../Engine/textures/coca_cola.dds";

	float signWidthX = 6.0f;
	float signHeightY = 3.5f;
	m_cokeSignFront = new QuadTexturedModel(signWidthX, signHeightY, signTexture);
	m_cokeSignFront->worldTranslate(5.0f, -5.0f, 0.0f);

	WCHAR * signBackTexture = L"../Engine/textures/slogan.dds";
	m_cokeSignBack = new QuadTexturedModel(signWidthX, signHeightY, signBackTexture);
	m_cokeSignBack->worldTranslate(5.0f, -5.0f, 0.0f);
	m_cokeSignBack->orientRotateY(XM_PI);



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
		
	XMFLOAT4 cubeColors[] = {
	    XMFLOAT4(153.0f/255, 76.0f/255, 0.0f, 1.0f), //front face brown1
	    XMFLOAT4(153.0f/255, 76.0f/255, 0.0f, 1.0f), //back face brown1
	    XMFLOAT4(204.0f/255, 102.0f/255, 0.0f, 1.0f), //right side brown2
	    XMFLOAT4(204.0f/255, 102.0f/255, 0.0f, 1.0f), //left side brown2
	    XMFLOAT4(255.0f/255, 128.0f/255, 0.0f, 1.0f), //top face brown3
	    XMFLOAT4(255.0f/255, 128.0f/255, 0.0f, 1.0f), //bottom face brown3
	};

	m_Player = new CubeModel(1.0f,  //length in X direction
							 1.0f,  //length in Y direction
							 1.0f, //length in Z direction
							 cubeColors //XMFLOAT4[6] with face colours
							 );

	m_Player->orientRotateY(XM_PIDIV4); //orient relative to model origin
	m_Player->worldTranslate(2.5f, -2.0f, 0.0f); //move to location in the world
	

	m_AirPlane = new AirPlaneModel();


	XMFLOAT4 prismColors[] = {
	    XMFLOAT4(230.0f/255, 230.0f/255, 0.0f, 1.0f), //prism faces yellow1
	    XMFLOAT4(204.0f/255, 204.0f/255, 0.0f, 1.0f), //prism ends yellow2
	};

	m_Enemy = new PrismModel(2.0f,  //height (Y direction)
							 1.0f,  //radius (X direction)
							 12,      //number of faces
							 prismColors //side and end colours 
							 ); 

    m_Enemy->orientRotateZ(XM_PIDIV4); //orient relative to model origin
	m_Enemy->worldTranslate(-2.5f, -2.5f, 0.0f); //move to location in the world

	
	
	//Add the  gameModel objects to the GameModels collection
	//that will be rendered by the graphics system

	m_GameModels->add(m_blueQuad);
	m_GameModels->add(m_backDrop);
	m_GameModels->add(m_cokeSignFront);
	m_GameModels->add(m_cokeSignBack);
	m_GameModels->add(m_groundCover);
	m_GameModels->add(m_Player);
	m_GameModels->add(m_Enemy);
	m_GameModels->addAll(m_AirPlane->GetGameModels());



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
	if(!result)
	{
		return false;
	}
	
	return true;
}


void SystemClass::Shutdown()
{
	//Shut down our game character objects and release their memory

	if(m_blueQuad)
	{
		m_blueQuad->Shutdown();
		delete m_blueQuad;
		m_blueQuad = 0;
	}

	if(m_backDrop)
	{
		m_backDrop->Shutdown();
		delete m_backDrop;
		m_backDrop = 0;
	}
	if(m_cokeSignFront)
	{
		m_cokeSignFront->Shutdown();
		delete m_cokeSignFront;
		m_cokeSignFront = 0;
	}
	if(m_cokeSignBack)
	{
		m_cokeSignBack->Shutdown();
		delete m_cokeSignBack;
		m_cokeSignBack = 0;
	}

	if(m_groundCover)
	{
		m_groundCover->Shutdown();
		delete m_groundCover;
		m_groundCover = 0;
	}


	if(m_Player)
	{
		m_Player->Shutdown();
		delete m_Player;
		m_Player = 0;
	}

	if(m_Enemy)
	{
		m_Enemy->Shutdown();
		delete m_Enemy;
		m_Enemy = 0;
	}

	if(m_AirPlane)
	{
		m_AirPlane->Shutdown();
		delete m_AirPlane;
		m_AirPlane = 0;
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
	m_Enemy->orientRotateZ(XM_PIDIV4/100);
	m_Enemy->orientRotateX(XM_PIDIV4/70);


	m_cokeSignBack->orientRotateY(XM_PIDIV4/70);
	m_cokeSignFront->orientRotateY(XM_PIDIV4/70);
	m_AirPlane->Advance();

	//Handle user inputs
	bool result;

	//checking to see if the user is doing something
	if(!checkControls())
		return false;
     


	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame();
	if(!result)
	{
		return false;
	}

	return true;
}


bool SystemClass::checkControls()
{
	const int ascii_A = 65;
	const int ascii_B = 66;
	const int ascii_C = 67;
	const int ascii_D = 68;
	const int ascii_E = 69;
	const int ascii_P = 80;
	const int ascii_R = 82;
	const int ascii_S = 83;
	const int ascii_W = 87;
	const int ascii_X = 88;
	const int ascii_Y = 89;
	const int ascii_Z = 90;


	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	
	//Move camera or models based on input
	

	/*
	We will combinations for a key + arrow keys to control the camera
	*/

	if ( m_Input->IsKeyDown(VK_SHIFT)){
	   
		if ( m_Input->IsKeyDown(VK_LEFT))
		   m_AirPlane->TurnLeft();
	   if ( m_Input->IsKeyDown(VK_RIGHT))
		   m_AirPlane->TurnRight();
	   if ( m_Input->IsKeyDown(VK_UP))
		   m_AirPlane->MoveForward();
	   if ( m_Input->IsKeyDown(VK_DOWN))
		   m_Player->MoveDown();	
		}
	else if ( m_Input->IsKeyDown(ascii_C)){

	   if ( m_Input->IsKeyDown(VK_UP) ) //Crane Up
		  m_Camera->CraneUp();
	   if ( m_Input->IsKeyDown(VK_DOWN) ) //Crane Down
		  m_Camera->CraneDown();	
	}
	else if ( m_Input->IsKeyDown(ascii_R)){

	   if ( m_Input->IsKeyDown(VK_LEFT) ) //Roll Left
		  m_Camera->RollLeft();
	   if ( m_Input->IsKeyDown(VK_RIGHT) ) //Roll Right
		  m_Camera->RollRight();	
	}
	else if ( m_Input->IsKeyDown(ascii_Z)){

	   if ( m_Input->IsKeyDown(VK_UP) ) //Zoom In
		  m_Camera->ZoomIn();
	   if ( m_Input->IsKeyDown(VK_DOWN) ) //Zoom Out
		  m_Camera->ZoomOut();	
	}
	else{
	   if ( m_Input->IsKeyDown(ascii_A) ) //Move Camera Left
	      m_Camera->StrafeLeft();

	   if ( m_Input->IsKeyDown(ascii_D) ) //Move Camera Right
	      m_Camera->StrafeRight();

	   if ( m_Input->IsKeyDown(ascii_W) ) //Camera Move Forward
		  m_Camera->MoveForward();

	   if ( m_Input->IsKeyDown(ascii_S) ) //Camera Pull Back
		  m_Camera->MoveBackward();

	   if ( m_Input->IsKeyDown(VK_LEFT) ) //Pan Camera Left
	      m_Camera->PanLeft();

	   if ( m_Input->IsKeyDown(VK_RIGHT) ) //Pan Camera Right
	      m_Camera->PanRight();
	   
	   if ( m_Input->IsKeyDown(VK_UP) ) //Tilt Camera Downward
		  m_Camera->TiltUp();

	   if ( m_Input->IsKeyDown(VK_DOWN) ) //Tilt Camera Upward
		  m_Camera->TiltDown();	
	}
	//user is still playing
	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	/*
	The MessageHandler function is where windows system messages are directed into our application
	Here we can listen for certain information that we are interested in. 
	Currently we will just read if a key is pressed or if a key is released and pass that information on to the input object. 
	All other information we will pass back to the windows default message handler. 
	*/
	switch(umsg)
	{
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			// The input object will be polled by our game logic

			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
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
		screenWidth  = 800;
		screenHeight = 600;

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
	//ShowCursor(false);

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