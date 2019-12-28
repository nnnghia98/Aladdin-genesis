#ifndef __SKELETON__
#define __SKELETON__
#include "GameObject.h"
class Skeleton: public GameObject
{
private:
public:
	bool isDeath;
	void Render(int flip = 1);
	void SetCurrentState(int currentState);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Skeleton(float nx,float x, float y, float vx, float vy);
	~Skeleton();
};

#endif // !__SKELETON__


