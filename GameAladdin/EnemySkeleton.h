#ifndef __ENEMY_SKELETON__
#define __ENEMY_SKELETON__
#include <cstdlib>
#include <ctime>
#include "Skeleton.h"
#define SKELETON_STAY 1
#define SKELETON_DEATH 4 //


class EnemySkeleton:public GameObject
{
private:
	static bool isLoadedSprite;
	void LoadSprite();
public:
	bool isDeath;
	DWORD dTime = -1;
	vector<Skeleton*> skeletons;
	Point aladdinPoint;
	void LoadResource();
	void Render(int flip = 1);
	void SetCurrentState(int currentState);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	EnemySkeleton(int id, float x, float y, int width, int height, oType type);
	~EnemySkeleton();
};
#endif // !__ENEMY_SKELETON__

