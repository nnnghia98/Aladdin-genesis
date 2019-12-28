#ifndef _ENEMY_BAT_
#define _ENEMY_BAT_
#include "GameObject.h"

#include <cstdlib>
#include <ctime>

#define BAT_STAY 1
#define BAT_FLY 2
#define BAT_DEATH 4

class EnemyBat :public GameObject
{
private:
	float d; // khoang cach can di sau 1 dt
	int count; // dem quang duong da di
	int n; // chieu dich chuyen: n = 1 -> bay ve aladdin; n = -1 -> bay ve diem xuat phat
	static bool isLoadedSprite;

	Point stayPoint;

	void LoadSprite();
public:
	Point aladdinPosition;
	void SetN(int n) { this->n = n; };
	EnemyBat(int id, float x, float y, int width, int height, oType type);
	~EnemyBat();
	void LoadResource();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
	void SetCurrentState(int currentState);
};

#endif //!_ENEMY_FAT