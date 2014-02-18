#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "modelclass.h"
#include "gamemodel.h"
#include "cubemodel.h"
#include "cubeTexturedModel.h"
#include "prismTexturedModel.h"
#include "prismmodel.h"
#include "arraylist.h"


#include <string>

using namespace DirectX;

const float CAR_FORWARD_SPEED_FACTOR = 0.1f; //adjust this to make forward motion look good

class CarModel
{
public:
	CarModel();
	virtual ~CarModel(void);
	virtual void Shutdown(); //release airplane component memory
	ArrayList<GameModel> GetGameModels(); //provide a list of simple components of the airplane

	//Motion control of plane
	//To be called on a per frame basis to alter motion of plane

	void TurnLeft();
	void TurnRight();
	void MoveForward();
	void Advance(int);
	void MoveBackward();

protected:
	virtual void InitializeModel(); //construct the airplane from component parts

private:


	PrismTexturedModel* m_tire1; //body of airplane
	PrismTexturedModel* m_tire2; //bomb underneath plane
	PrismTexturedModel* m_tire3; //bomb underneath plane
	PrismTexturedModel* m_tire4; //bomb underneath plane
	
	/*PrismTexturedModel* m_Fuselage; //body of airplane
	PrismTexturedModel* m_PontoonLeft; //left pontoon of float plane
	PrismTexturedModel* m_PontoonRight; //right pontoon of float plane

	PrismTexturedModel* m_StrutFrontLeft; 
	PrismTexturedModel* m_StrutBackLeft; 
	PrismTexturedModel* m_StrutFrontRight; 
	PrismTexturedModel* m_StrutBackRight; 

	CubeTexturedModel* m_Wing; //wings of airplane
	CubeTexturedModel* m_Propeller; //propeller of airplane*/

	CubeTexturedModel* m_Cab;
	CubeTexturedModel* m_Body;

	XMFLOAT3 m_directionVector; //direction plane is facing when constructed
};

