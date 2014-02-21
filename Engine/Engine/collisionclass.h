#pragma once
#include <DirectXCollision.h>
#include "levelclass.h"

using namespace DirectX;

class CollisionClass
{
public:
	CollisionClass(void);
	~CollisionClass(void);
	static bool CheckCollision(int x, int y);
};

