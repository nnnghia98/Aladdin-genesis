#ifndef __ROPE__
#define __ROPE__

#include "GameObject.h"

class Rope : public GameObject
{
public:
	Rope();
	Rope(int id, float x, float y, int width, int height, oType type);
	~Rope();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	//void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	void Render() { RenderBoundingBox(); };
	//void SetState(int state) { this->state = state; };
};

#endif __ROPE__