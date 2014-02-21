
/* EnemyObject.h ::: Luke Harper */

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "gameobject.h"
#include "enemymodel.h"
#include "worldDefs.h"

enum EnemyState { STANDING, WALKING, ATTACKING };
class EnemyObject: public GameObject
{
public:


private:
	EnemyModel m_model;

};

#endif