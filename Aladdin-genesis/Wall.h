#ifndef __WALL__
#define __WALL__

#include "GameObject.h"

class Wall : public GameObject
{
public:
	Wall();
	Wall(int id,  float x, float y, int width, int height, oType type);
	~Wall();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	//void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	void Render() { RenderBoundingBox(); };
	//void SetState(int state) { this->state = state; };
};

#endif __BRICK__