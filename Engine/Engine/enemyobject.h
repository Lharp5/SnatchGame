
/* EnemyObject.h ::: Luke Harper */

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "gameobject.h"
#include "enemymodel.h"
#include "worldDefs.h"

enum EnemyState { STANDING, WALKING, ATTACKING };
<<<<<<< HEAD
=======

>>>>>>> ccfb6a73796238df84156047a14d614ce8ad8f47
class EnemyObject: public GameObject
{
public:


private:
	EnemyModel m_model;

};

#endif