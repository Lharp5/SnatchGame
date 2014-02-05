#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "textureclass.h"
#include "modelclass.h"
#include "gamemodel.h"


#include <string>

using namespace DirectX;

class QuadTexturedModel : public GameModel
	//This model represents a quad made up of two trianges.
	//One of lengthX, lengthY, or lengthZ must be 0;
{
public:
	QuadTexturedModel(float lengthX, float lengthY, WCHAR* aTextureFileName);
	virtual ~QuadTexturedModel(void);
	virtual void Shutdown();
    virtual bool initializeTextures(ID3D11Device* device);
	virtual ID3D11ShaderResourceView* GetTexture();

protected:
	virtual void InitializeModel(float lengthX, float lengthY, WCHAR* aTextureFileName);

private:
	WCHAR * m_textureFileName; 
	TextureClass * m_quadTexture;
};
