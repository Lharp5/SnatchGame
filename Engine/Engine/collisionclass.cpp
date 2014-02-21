#include "collisionclass.h"


CollisionClass::CollisionClass(void)
{
}


CollisionClass::~CollisionClass(void)
{
}

bool CollisionClass::CheckCollision(int x, int y)
{
	return (LevelClass::CheckLocation(x, y) != NULL);
}