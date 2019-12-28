#ifndef __BOB__
#define __BOB__

#include "GameObject.h"
#define STATE1 1

class Bob:public GameObject
{
private:
	static bool isLoadedResource;
	void LoadResources();
public:
	Bob(int id, float x, float y, int width, int height, oType type);
	~Bob();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(int flip = 1);
};
#endif