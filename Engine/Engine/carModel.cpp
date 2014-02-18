#include "gamemodel.h"
#include "modelclass.h"
#include "carModel.h"
#include "arraylist.h"

/*
This class represents a simple airplane model built out of cube and prism game model components
It can be moved forward in the direction it is facing and turned left or right.

Exercise: it would be cool if it actually banked while turning.
How would you do this?
*/
CarModel::CarModel()
{
	
	m_Body = 0;
	m_Cab = 0;
	m_tire1 = 0;
	m_tire2 = 0;
	m_tire3 = 0;
	m_tire4 = 0;

	//direction plane is facing as constructed in the model co-ordinates
    m_directionVector = XMFLOAT3(1.0f,0.0f,0.0f); //face in positive X direction

	InitializeModel();
}

CarModel::~CarModel(void)
{ 
	Shutdown();
}

ArrayList<GameModel> CarModel::GetGameModels(){

	//Provide an arraylist of simple GameModel components that make up this airplane
	//These will be given to the GraphicsClass object to render using the graphics pipeline

	ArrayList<GameModel> list;

	list.add(m_Body);
	list.add(m_Cab);
	list.add(m_tire1);
	list.add(m_tire2);
	list.add(m_tire3);
	list.add(m_tire4);


	return list;
}


void CarModel::InitializeModel()
{

	/*
	Create the airplane out of simple CubeModel and PrismModel parts
	*/

	//Define dimensions of parts of the plane so they can easily be changed in one place

	float bodyLength = 4.0f;
	float bodyWidth =2.0f;
	float bodyThickness = 0.75f;
	
	float cabLength = bodyLength* .75f;
	float cabWidth = bodyWidth - 0.02f;
	float cabThickness = bodyThickness*.75f;

	float tireRadius = bodyLength/10.0f;
	float tireWidth = bodyWidth/8.0f;
	int tireFace = 24;

	//fuselage colours
	XMFLOAT4 prismColors[] = {
	    XMFLOAT4(230.0f/255, 0.0f, 0.0f, 1.0f), //prism faces red1
	    XMFLOAT4(204.0f/255, 0.0f, 0.0f, 1.0f), //prism ends red2
	};

    WCHAR * CabTextureFiles[] = {
		 L"../Engine/textures/wood_texture.dds", 
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/end_grain.dds",
		 L"../Engine/textures/end_grain.dds",
	};


	m_Cab = new CubeTexturedModel( cabWidth,  //width
							     cabLength,  //radius
								 cabThickness,      //number of faces
							     CabTextureFiles //prism texture files
							    ); 

    m_Cab->orientRotateZ(XM_PIDIV2); //orient fuselage along X axis
	m_Cab->orientRotateX(XM_PIDIV2);
	m_Cab->orientTranslate(0.0f, 0.5f, 0.0f);
    m_directionVector = XMFLOAT3(1.0f,0.0f,0.0f); //plane is facing in positive X direction


    WCHAR * bodyTextureFiles[] = {
		 L"../Engine/textures/wood_texture.dds", 
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/end_grain.dds",
		 L"../Engine/textures/end_grain.dds",
	};


	m_Body = new CubeTexturedModel( bodyThickness,  //height
							     bodyLength,  //radius
							     bodyWidth,      //number of faces
								 bodyTextureFiles //prism texture files
							    ); 

	m_Body->orientTranslate(0.0f, 0.0f, 0.0);
    m_Body->orientRotateZ(XM_PIDIV2); //orient fuselage along X axis

	
	 WCHAR * tireTextureFiles[] = {
		 L"../Engine/textures/tireTread.dds",
		 L"../Engine/textures/carWheel.dds",
		 L"../Engine/textures/CarWheel.dds",
	};
	
	m_tire1 = new PrismTexturedModel( tireWidth,  //height
							     tireRadius,  //radius
							     tireFace,      //number of faces
							     tireTextureFiles //prism texture files
							    ); 
	m_tire2 = new PrismTexturedModel( tireWidth,  //height
							     tireRadius,  //radius
							     tireFace,      //number of faces
							     tireTextureFiles //prism texture files
							    ); 
	m_tire3 = new PrismTexturedModel( tireWidth,  //height
							     tireRadius,  //radius
							     tireFace,      //number of faces
							     tireTextureFiles //prism texture files
							    ); 
	m_tire4 = new PrismTexturedModel( tireWidth,  //height
							     tireRadius,  //radius
							     tireFace,      //number of faces
							     tireTextureFiles //prism texture files
							    ); 

    m_tire1->orientRotateX(XM_PIDIV2); //orient fuselage along X axis
	m_tire1->orientTranslate(bodyLength*.3f, -bodyThickness*.75f, 1.0f);

	m_tire2->orientRotateX(XM_PIDIV2); //orient fuselage along X axis
	m_tire2->orientTranslate(-bodyLength*.3f, -bodyThickness*.75f, -1.0f);

	m_tire3->orientRotateX(XM_PIDIV2); //orient fuselage along X axis
	m_tire3->orientTranslate(-bodyLength*.3f, -bodyThickness*.75f, 1.0f);

	m_tire4->orientRotateX(XM_PIDIV2); //orient fuselage along X axis
	m_tire4->orientTranslate(bodyLength*.3f, -bodyThickness*.75f, -1.0f);

}

void CarModel::Advance(int i){
	//Advance moving parts of the plane
	//This method should be called on a per-frame basis
	
	//Spin the propeller
	float tireRadianAngularIncrement = (-XM_PIDIV4/5)*i; //sign changes direction of the propeller
	m_tire1->orientRotateZ(tireRadianAngularIncrement);
	m_tire2->orientRotateZ(tireRadianAngularIncrement);
	m_tire3->orientRotateZ(tireRadianAngularIncrement);
	m_tire4->orientRotateZ(tireRadianAngularIncrement);
}

void CarModel::MoveForward(){

	Advance(1);

	  //Move the airplane in the direction it is facing based on its
	  //direction vector and the speed factor which can be adjusted for smooth motion

	  XMFLOAT3 effectiveDirectionVector;
	  XMFLOAT4X4 fuselageDirectionMatrix = m_Body->GetWorldRotateMatrix();
      XMStoreFloat3( &effectiveDirectionVector,  XMVector3Transform( XMLoadFloat3(&m_directionVector), XMLoadFloat4x4(&fuselageDirectionMatrix) ));

	  float deltaX = effectiveDirectionVector.x*CAR_FORWARD_SPEED_FACTOR;
	  float deltaY = effectiveDirectionVector.y*CAR_FORWARD_SPEED_FACTOR;
	  float deltaZ = effectiveDirectionVector.z*CAR_FORWARD_SPEED_FACTOR;

	  //Move all the  component parts of the airplane relative to the world
	  //co-ordinate system

	  m_Cab->worldTranslate(deltaX, deltaY, deltaZ);
	  m_Body->worldTranslate(deltaX, deltaY, deltaZ);
	  m_tire1->worldTranslate(deltaX, deltaY, deltaZ);
	  m_tire2->worldTranslate(deltaX, deltaY, deltaZ);
	  m_tire3->worldTranslate(deltaX, deltaY, deltaZ);
	  m_tire4->worldTranslate(deltaX, deltaY, deltaZ);
}

void CarModel::MoveBackward(){

	  Advance(-1);
	  //Move the airplane in the direction it is facing based on its
	  //direction vector and the speed factor which can be adjusted for smooth motion

	  XMFLOAT3 effectiveDirectionVector;
	  XMFLOAT4X4 bodyDirectionMatrix = m_Body->GetWorldRotateMatrix();
      XMStoreFloat3( &effectiveDirectionVector,  XMVector3Transform( XMLoadFloat3(&m_directionVector), XMLoadFloat4x4(&bodyDirectionMatrix) ));

	  float deltaX = -effectiveDirectionVector.x*CAR_FORWARD_SPEED_FACTOR;
	  float deltaY = -effectiveDirectionVector.y*CAR_FORWARD_SPEED_FACTOR;
	  float deltaZ = -effectiveDirectionVector.z*CAR_FORWARD_SPEED_FACTOR;

	  //Move all the  component parts of the airplane relative to the world
	  //co-ordinate system

	  m_Cab->worldTranslate(deltaX, deltaY, deltaZ);
	  m_Body->worldTranslate(deltaX, deltaY, deltaZ);
	  m_tire1->worldTranslate(deltaX, deltaY, deltaZ);
	  m_tire2->worldTranslate(deltaX, deltaY, deltaZ);
	  m_tire3->worldTranslate(deltaX, deltaY, deltaZ);
	  m_tire4->worldTranslate(deltaX, deltaY, deltaZ);
}
void CarModel::TurnLeft(){
	
	//Rotate, or Yaw, the plane about the Y axis

	float rotationRadianAngle = -XM_PIDIV4/40;
	m_Cab->worldRotateY(rotationRadianAngle);
	m_Body->worldRotateY(rotationRadianAngle);
	m_tire1->worldRotateY(rotationRadianAngle);
	m_tire2->worldRotateY(rotationRadianAngle);
	m_tire3->worldRotateY(rotationRadianAngle);
	m_tire4->worldRotateY(rotationRadianAngle);

}
void CarModel::TurnRight(){

	//Rotate, or Yaw, the plane about the Y axis

	float rotationRadianAngle = XM_PIDIV4/40;
	m_Cab->worldRotateY(rotationRadianAngle);
	m_Body->worldRotateY(rotationRadianAngle);
	m_tire1->worldRotateY(rotationRadianAngle);
	m_tire2->worldRotateY(rotationRadianAngle);
	m_tire3->worldRotateY(rotationRadianAngle);
	m_tire4->worldRotateY(rotationRadianAngle);
}



void CarModel::Shutdown()
{
	//Release the memory of the component parts of the airplane

	if(m_Cab)
	{
		delete m_Cab;
		m_Cab = 0;
	}

	if(m_Body)
	{
		delete m_Body;
		m_Body = 0;
	}

	if(m_tire1)
	{
		delete m_tire1;
		m_tire1 = 0;
	}
	if(m_tire2)
	{
		delete m_tire1;
		m_tire1 = 0;
	}
	if(m_tire3)
	{
		delete m_tire1;
		m_tire1 = 0;
	}
	if(m_tire4)
	{
		delete m_tire1;
		m_tire1 = 0;
	}

}
