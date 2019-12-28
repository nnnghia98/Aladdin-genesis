#ifndef __REDJEWEL__
#define __REDJEWEL__
#include  "GameObject.h"

#define REDJEWEL_STATE_1 1 // Trạng thái bình thường
#define REDJEWEL_STATE_2 2 // Trạng thái khi va chạm

class RedJewel : public GameObject
{
private:
	static bool isLoadedResource;
	void LoadResources();
public:
	RedJewel();
	RedJewel(int id, float x, float y, int width, int height, oType type);
	~RedJewel();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
};

#endif __REDJEWEL__