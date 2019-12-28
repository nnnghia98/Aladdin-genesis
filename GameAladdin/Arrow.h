#ifndef __ARROW__
#define __ARROW__

#include "GameObject.h"
#define STATE1 1 // trang thai chuyen ra vao
class Arrow: public GameObject
{
private:
	static bool isLoadedResource;
	void LoadResources();
public:
	Arrow(int id, float x, float y, int width, int height, oType type);
	~Arrow();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(int flip = 1);
};

#endif // !__ARROW__


