
/* EnemyObject.h ::: Luke Harper */

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "gameobject.h"
#include "enemymodel.h"
#include "worldDefs.h"
#include "arraylist.h"
#include "lightobject.h"
#include <vector>

enum EnemyState { PATROLLING, FIXING, CHASING };

class EnemyObject: public GameObject
{
public:
	EnemyObject(vector<int>, SoundClass*, float x=0.0f, float y=0.0f, float z=0.0f, float s=1.0f);
	virtual ~EnemyObject(void);
	virtual void shutdown();
	virtual ArrayList<GameModel> GetGameModels();
	virtual void setPatrolLight(LightObject*);
	virtual LightObject* getPatrolLight();
	
	virtual bool getRenderValue();
	virtual void setRenderValue(bool);

	vector<int>& getPath();
	vector<int>& getFixPath();
	void setFixPath(vector<int>&);
	vector<int>& getCurrentPath();
	void setCurrentPath(vector<int>& p);
	void resetPath(vector<int>&);
	int currentPathAction;
	int prevPathAction;
	bool actionComplete;
	
	void TurnLeft();
	void TurnRight();
	void TurnLeft90();
	void TurnRight90();
	void Turn(float rotationRadianAngle);
	void MoveForward(int);
	void Rest(int);

	Direction getDirection();
	Direction getPrevDirection();
	void setPrevDirection(Direction);

	XMINT2 getDestination();
	XMINT2 getPrevDestination();
	void setPrevDestination(int, int);
	bool isOnPath();
	void toggleOnPath();

	void Frame();

	bool playerSpotted;

	EnemyState enemyState;

private:
	EnemyModel* m_model;
	bool renderVal;
	XMINT2 destination;
	XMINT2 prevDestination;
	Direction direction;
	Direction prevDirection;
	time_t timeN;
	vector<int> path;
	vector<int> fixPath;
	vector<int> currentPath;
	LightObject* patrolLight;
};

#endif