#include "UI.h"

UI::UI(): star4(L"../Engine/textures/Score/Score4.dds"), star3(L"../Engine/textures/Score/Score3.dds"), star2(L"../Engine/textures/Score/Score2.dds"), 
			star1(L"../Engine/textures/Score/Score1.dds"), star0 (L"../Engine/textures/Score/Score0.dds"), starUi(new QuadTexturedModel(1.0f, 0.25f,star4))
{
}

UI::UI(XMFLOAT3 camPos, XMFLOAT2 camRot): star4(L"../Engine/textures/Score/Score4.dds"), star3(L"../Engine/textures/Score/Score3.dds"), star2(L"../Engine/textures/Score/Score2.dds"), 
			star1(L"../Engine/textures/Score/Score1.dds"), star0 (L"../Engine/textures/Score/Score0.dds"), starUi(new QuadTexturedModel(0.5f, 0.125f,star4))
{
	cameraPosition = camPos;
	firstTimeP = true;
	cameraRotation = camRot;
	firstTimeR = true;
	//starUi->worldTranslate(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	//starUi->worldTranslate(12.0f, -2.0f, 15.0f);
}

UI::~UI()
{
	delete starUi;
	starUi = 0;
}

QuadTexturedModel* UI::getUI()
{
	return starUi;
}

void UI::setPosition(XMFLOAT3 camPos)
{
	if(firstTimeP){
		position = XMFLOAT3(camPos.x, camPos.y, camPos.z);
		starUi->worldTranslate(position.x, position.y, position.z);
		starUi->orientTranslate(0.75f, -0.5f, 1.5f);
		firstTimeP = false;
		cameraPosition = camPos;
	}
}

void UI::setRotation(XMFLOAT2 camRot)
{
	if(firstTimeR){
		rotation = XMFLOAT2(camRot.x, camRot.y);
		firstTimeR = false;
		cameraRotation = camRot;
	}
}

void UI::frame(XMFLOAT3 camPos, XMFLOAT2 camRot)
{
	float dx = camPos.x - cameraPosition.x;
	float dy = camPos.y - cameraPosition.y;
	float dz = camPos.z - cameraPosition.z;
	float ax = camRot.x - cameraRotation.x;
	float ay = camRot.y - cameraRotation.y;
	cameraPosition = camPos;
	cameraRotation = camRot;
	
	starUi->worldTranslate(dx, dy, dz);
	starUi->worldRotateY(ax);
	starUi->worldRotateY(-cameraRotation.x);
	starUi->worldRotateX(ay);
	starUi->worldRotateY(cameraRotation.x);
}


