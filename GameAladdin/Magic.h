#ifndef __MAGIC__
#define __MAGIC__

#include "GameObject.h"

#define DRAG_NON_COLLISION 1
#define DRAG_COLLISION 2

class Magic: public GameObject
{
private:
	float v;
	DWORD dtime;
public:
	bool isDeath;
	Point Goal;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
	void SetCurrentState(int currentState);
	Magic(float x, float y, int width, int height);
	~Magic();
};

#endif