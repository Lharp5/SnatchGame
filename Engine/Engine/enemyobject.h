
/* EnemyObject.h ::: Luke Harper */

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "gameobject.h"
#include "enemymodel.h"
#include "worldDefs.h"
#include "arraylist.h"

enum EnemyState { STANDING, WALKING, ATTACKING };

class EnemyObject: public GameObject
{
public:
	EnemyObject(float x=0.0f, float y=0.0f, float z=0.0f, float s=1.0f);
	virtual ~EnemyObject(void);
	virtual void shutdown();
	virtual ArrayList<GameModel> GetGameModels();
	
	virtual bool getRenderValue();
	virtual void setRenderValue(bool);
	
	void TurnLeft();
	void TurnRight();
	void TurnLeft90();
	void TurnRight90();
	void Turn(float rotationRadianAngle);
	void MoveForward();
	void Rest();

private:
	EnemyModel* m_model;
	bool renderVal;

};

#endif