
/* EnemyObject.h ::: Luke Harper */

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "gameobject.h"
#include "enemymodel.h"
#include "worldDefs.h"
#include "arraylist.h"
#include "lightobject.h"

enum EnemyState { PATROLLING, FIXING, CHASING };
enum Direction { NORTH, EAST, SOUTH, WEST };

class EnemyObject: public GameObject
{
public:
	EnemyObject(int*, SoundClass*, float x=0.0f, float y=0.0f, float z=0.0f, float s=1.0f);
	virtual ~EnemyObject(void);
	virtual void shutdown();
	virtual ArrayList<GameModel> GetGameModels();
	virtual void setPatrolLight(LightObject*);
	virtual LightObject* getPatrolLight();
	
	virtual bool getRenderValue();
	virtual void setRenderValue(bool);

	int* getPath();
	int currentPathAction;
	bool actionComplete;
	
	void TurnLeft();
	void TurnRight();
	void TurnLeft90();
	void TurnRight90();
	void Turn(float rotationRadianAngle);
	void MoveForward(int);
	void Rest(int);

	XMINT2 getPrevDestination();
	void setPrevDestination(int, int);
	bool isOnPath();
	void toggleOnPath();

	void Frame();

	EnemyState enemyState;

private:
	EnemyModel* m_model;
	bool renderVal;
	XMINT2 destination;
	XMINT2 prevDestination;
	Direction direction;
	time_t timeN;
	int path[12];
	LightObject* patrolLight;
	bool onPath;
};

#endif