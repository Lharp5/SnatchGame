#include "UI.h"

UI::UI(): star4(L"../Engine/textures/Score/Score4.dds"), star3(L"../Engine/textures/Score/Score3.dds"), star2(L"../Engine/textures/Score/Score2.dds"), 
			star1(L"../Engine/textures/Score/Score1.dds"), star0 (L"../Engine/textures/Score/Score0.dds"), starUi(new QuadTexturedModel(1.0f, 0.25f,star4))
{
}

UI::UI(XMFLOAT3 camPos, XMFLOAT2 camRot): star4(L"../Engine/textures/Score/Score4.dds"), star3(L"../Engine/textures/Score/Score3.dds"), star2(L"../Engine/textures/Score/Score2.dds"), 
			star1(L"../Engine/textures/Score/Score1.dds"), star0 (L"../Engine/textures/Score/Score0.dds"), starUi(new QuadTexturedModel(0.5f, 0.125f,star4))
{
	width = 0.5f;
	height = 0.125f;
	goldStar = EXCELL;
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

void UI::setStar(XMFLOAT3 camPos, XMFLOAT2 camRot)
{
	firstTimeP = true;
	firstTimeR = true;
	delete starUi;
	switch(goldStar){
	case EXCELL:	starUi = new QuadTexturedModel(width, height, star4);	break;
	case GREAT:		starUi = new QuadTexturedModel(width, height, star3);	break;
	case GOOD:		starUi = new QuadTexturedModel(width, height, star2);	break;
	case OK:		starUi = new QuadTexturedModel(width, height, star1);	break;
	default:		starUi = new QuadTexturedModel(width, height, star0);	break;
	}
	setPosition(camPos);
	setRotation(camRot);
	wchar_t* outstring = L"Created New Texture \n";
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
}
bool UI::changeNeeded()
{
	
	switch(goldStar){
	case EXCELL:	goldStar = GREAT; 	break;
	case GREAT:		goldStar = GOOD; 	break;	
	case GOOD:		goldStar = OK;		break;
	case OK:		goldStar = FAIL; 	break; 
	default:		return false;
	}
	wchar_t* outstring = L"Changed the Star \n";
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
	return true;
}
Score UI::getStars()
{
	return goldStar;
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
		starUi->worldRotateX(cameraRotation.y);
		starUi->worldRotateY(cameraRotation.x);
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

	position = XMFLOAT3(position.x+dx, position.y+dy, position.z+dz);
	
	starUi->worldTranslate(dx, dy, dz);
	starUi->worldRotateY(ax);
	starUi->worldRotateY(-cameraRotation.x);
	starUi->worldRotateX(ay);
	starUi->worldRotateY(cameraRotation.x);
}


