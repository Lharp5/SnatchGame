#ifndef WORLDDEFS_H
#define WORLDDEFS_H

const float STRAFE_SPEED = 0.2f;
const float ADVANCE_SPEED = 0.25f;

enum GameState { MENU, PLAYING, WIN, GAMEOVER };

enum Direction { NORTH, EAST, SOUTH, WEST };

enum score {FAIL = 0, OK, GOOD,GREAT, EXCELL};

//Explanation for the numbers attached to WALL_TYPEs:
////representation of which direction the object is facing
////1 means facing positive z
////2 means facing positive x
////3 means facing negative z
////4 means facing negative x
enum WALL_TYPE {C_DOOR_1, C_DOOR_2,
				C_LOCK_1, C_LOCK_2, C_LOCK_3, C_LOCK_4,
				C_LIGHT_1, C_LIGHT_2, C_LIGHT_3, C_LIGHT_4,
				C_WALL,
				C_FLOOR,
				C_DEFAULT};

#endif