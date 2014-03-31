/* UI.H*/
#ifndef UI_H
#define UI_H

#include "quadTexturedModel.h"
#include "worldDefs.h"

class UI
{
public:
	UI();
	UI(XMFLOAT3);
	~UI();
	void frame(XMFLOAT3);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
	void setPosition(XMFLOAT3);
	QuadTexturedModel* getUI();
	void changeScore();
private:
	XMFLOAT3 cameraPosition;
	Score goldStar;
	WCHAR * star4;
	WCHAR * star3;
	WCHAR * star2;
	WCHAR * star1;
	WCHAR * star0;
	QuadTexturedModel* starUi;

	XMFLOAT3 position;

	void setStar4();
	void setStar3();
	void setStar2();
	void setStar1();
	void setStar0();
	
};

#endif