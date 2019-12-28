#ifndef __HEART__
#define __HEART__
#include  "GameObject.h"

#define HEART_STATE_1 1 // Trạng thái: không có va chạm với aladdin
#define HEART_STATE_2 2 // Trạng thái: khi va chạm với aladdin -> phát nổ

class Heart : public GameObject
{
private:
	static bool isLoadedResource;
	void LoadResources();
public:
	Heart(int id, float x, float y, int width, int height, oType type);
	~Heart();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
};
#endif __HEART__