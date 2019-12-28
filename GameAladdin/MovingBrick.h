#ifndef __MOVINGBRICK__
#define __MOVINGBRICK__

#include "GameObject.h"

#define STATE1 1

class MovingBrick : public GameObject
{
private:
	static bool isLoadedResource;
	static int oddFrame; // frame hình của Moving Brick lẻ
	void LoadResource();
public:
	MovingBrick();
	MovingBrick(int id, float x, float y, int width, int height, oType type);
	~MovingBrick();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(int flip = 1);
};

#endif __MOVINGBRICK__