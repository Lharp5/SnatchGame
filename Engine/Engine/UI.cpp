#include "UI.h"

UI::UI(): star4(L"../Engine/textures/Score/Score4.dds"), star3(L"../Engine/textures/Score/Score3.dds"), star2(L"../Engine/textures/Score/Score2.dds"), 
			star1(L"../Engine/textures/Score/Score1.dds"), star0 (L"../Engine/textures/Score/Score0.dds"), starUi(new QuadTexturedModel(1.0f, 0.25f,star4))
{
}

UI::UI(XMFLOAT3 camPos): star4(L"../Engine/textures/Score/Score4.dds"), star3(L"../Engine/textures/Score/Score3.dds"), star2(L"../Engine/textures/Score/Score2.dds"), 
			star1(L"../Engine/textures/Score/Score1.dds"), star0 (L"../Engine/textures/Score/Score0.dds"), starUi(new QuadTexturedModel(0.5f, 0.125f,star4))
{
	cameraPosition = camPos;
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
	position = XMFLOAT3(camPos.x+0.75f, camPos.y-0.5f, camPos.z+1.5f);
	starUi->worldTranslate(position.x, position.y, position.z);
}
void UI::frame(XMFLOAT3 camPos)
{
	float dx = (camPos.x - cameraPosition.x);
	float dy = (camPos.y - cameraPosition.y);
	float dz = (camPos.z - cameraPosition.z);
	cameraPosition = camPos;

	
	//starUi->worldTranslate(dx, dy, dz);
}


