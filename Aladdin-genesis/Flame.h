#ifndef __FLAME__
#define __FLAME__

#include "GameObject.h"

#define FLAME_1 1

class Flame : public GameObject
{
private:
	DWORD dtime;
public:
	bool isDeath;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
	void SetCurrentState(int currentState);
	Flame(float x, float y, int width, int height, float nx);
	~Flame();
};
#endif