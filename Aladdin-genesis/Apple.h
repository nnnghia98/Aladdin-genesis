#ifndef __APPLE__
#define __APPLE__
#include  "GameObject.h"

#define APPLE_STATE_1 1 // Trạng thái bình thường
#define APPLE_STATE_2 2 // Trạng thái va chạm 

class Apple : public GameObject
{
private:
	static bool isLoadedResource;
	void LoadResources();
public:
	Apple();
	Apple(int id, float x, float y, int width, int height, oType type);
	~Apple();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
};

#endif __APPLE__