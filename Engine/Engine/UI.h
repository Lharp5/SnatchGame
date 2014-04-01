/* UI.H*/
#ifndef UI_H
#define UI_H

#include "quadTexturedModel.h"
#include "worldDefs.h"

class UI
{
public:
	UI();
	UI(XMFLOAT3, XMFLOAT2);
	~UI();
	void frame(XMFLOAT3, XMFLOAT2);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
	void setPosition(XMFLOAT3);
	void setRotation(XMFLOAT2);
	QuadTexturedModel* getUI();
	bool changeNeeded();
	void setStar(float, float, float);

	Score getStars();

private:
	XMFLOAT3 cameraPosition;
	XMFLOAT2 cameraRotation;
	Score goldStar;
	WCHAR * star4;
	WCHAR * star3;
	WCHAR * star2;
	WCHAR * star1;
	WCHAR * star0;
	QuadTexturedModel* starUi;

	XMFLOAT3 position;
	XMFLOAT2 rotation;
	bool firstTimeP;
	bool firstTimeR;

	float width;
	float height;
		
};

#endif