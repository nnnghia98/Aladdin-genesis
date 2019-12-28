#ifndef __JAFAR__
#define __JAFAR__

#include "GameObject.h"
#include "Magic.h"
#include "Flame.h"

#define JAFAR_ATTACK 1
#define JAFAR_THROW_SNAKE 2
#define SNAKE_APPEAR 3
#define SNAKE_ATTACK 4
#define FIRER 5
#define FIRER_OF_SNAKE 8

class Jafar :public GameObject
{
private: 
	static bool isLoadedSprite;
	void LoadSprite();
public:
	bool isSnake;
	bool isDeath;
	vector<LPGAMEOBJECT> weapon;
	DWORD dtime = 0;
	Point aladdinPoint;
	void LoadResource();
	Jafar();
	~Jafar();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
	void SetCurrentState(int currentState);
	int GetHealth() { return health; }
};
#endif // !__JAFAR__