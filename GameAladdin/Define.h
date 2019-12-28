#ifndef _DEFINE_H__
#define _DEFINE_H__

#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

#include <fstream> 
#include <string>
#include <stdio.h>
#include <Windows.h>  
#include <iostream>
#include <map>
#include <algorithm>
#include <d3dx9.h>
#include <stdlib.h>
#include <iomanip>
#include <d3d9.h>
#include <vector>
#include <iostream>

#define SCREEN_WIDTH 315
#define SCREEN_HEIGHT 254
#define CAM_WIDTH 310
#define CAM_HEIGHT 234
#define MAX_FRAME_RATE 60

#define ALADDIN_POS_DEFAULT_WIDTH 130
#define ALADDIN_POS_DEFAULT_HEIGHT 52

#define WINDOW_CLASS_NAME L"Aladdin"
#define MAIN_WINDOW_TITLE L"Aladdin"

#define D3DCOLOR_BACKGROUND D3DCOLOR_XRGB(0, 0, 0)

#define MAP1 101
#define MAP2 102
#define MAP1_SIZE_OF_WIDTH 2264
#define MAP1_SIZE_OF_HEIGHT 1136
#define MAP2_SIZE_OF_WIDTH 500
#define MAP2_SIZE_OF_HEIGT 500

#define ID_TEX_BBOX -100

#define GRID_CELL_WIDTH 568
#define GRID_CELL_HEIGHT 280
#define ID_TEX_ALADDIN 1021
#define ID_TEX_ENEMY 1022
#define ID_TEX_RESOURCE_MAP1 1023
#define ID_TEX_ITEM 1024
#define ID_TEX_STATEDISAPPEAR 1025
#define ID_TEX_BAT 1026
#define ID_TEX_SKELETON 1027
#define ID_TEX_BOSS 1028
#define ID_TEX_RESOURCE_MAP1A 1029
#define ID_TEX_BOSSBACKGROUND 1030

#define ENEMYTHIN_WALK_SPEED 0.12f
#define ENEMY_DEFIANT 1
#define ENEMY_WALK 2
#define ENEMY_ATTACKING 3
#define ENEMY_DEATH 4



//object type
enum oType
{
	ALADDIN = 0,
	BOB = 1,
	BAT = 2,
	APPLE = 3,
	WALL = 4,
	BRICK = 5,
	ROPE = 6, // dây thừng
	MOVINGBRICK = 7,
	ARROW = 8,
	REDJEWEL = 9,
	GENIE = 10,
	HEART = 11,
	RESTARTPOINT = 12,
	ENEMYFAT = 13,
	ENEMYTHIN = 14,
	ENEMYSKELETON = 15,
	ENEMYBAT = 16,
	SKELETON = 17,
	JAFAR = 18,
	FLAME = 19,
	MAGIC = 20,
	NEXTLEVELPOINT = 21
};

struct Point 
{
	int x;
	int y;
	float distance(Point a) 
	{
		return sqrt(abs((x - a.x)*(x - a.x) + (y - a.y)*(y - a.y)));
	}
	float distance(float x, float y)
	{
		return sqrt(abs((this->x - x)*(this->x - x) + (y - this->y)*(y - this->y)));
	}

};

struct BoundingBox
{
	float top, left, right, bottom;
	float vx, vy;

	BoundingBox(){}
	~BoundingBox(){}
};

#endif