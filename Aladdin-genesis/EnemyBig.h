#ifndef _ENEMY_FAT_
#define _ENEMY_FAT_
#include "GameObject.h"

#include <cstdlib>
#include <ctime>
class EnemyBig :public GameObject
{
private:
	int ny;
	static bool isLoadedSprite;
	void LoadSprite();


public:
	EnemyBig(int id, float x, float y, int width, int height, oType type, int leftMargin = -1, int rightMargin=-1);
	~EnemyBig();
	bool isOnlyStay;
	int LeftMargin;
	int RightMargin;
	void LoadResource();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
	void SetCurrentState(int currentState);
};

#endif //!_ENEMY_FAT
