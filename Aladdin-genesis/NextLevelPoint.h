#ifndef __NEXTLEVELPOINT__
#define __NEXTLEVELPOINT__
#include  "GameObject.h"

class NextLevelPoint : public GameObject
{
public:
	NextLevelPoint(int id, float x, float y);
	~NextLevelPoint();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
#endif __HEART__