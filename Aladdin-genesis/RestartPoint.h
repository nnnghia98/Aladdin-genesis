#ifndef __RESTARTPOINT__
#define __RESTARTPOINT__
#include  "GameObject.h"

#define RESTARTPOINT_STATE_1 1 // Trạng thái: không có va chạm với aladdin
#define RESTARTPOINT_STATE_2 2 // Trạng thái: khi va chạm với aladdin -> phát nổ

class RestartPoint : public GameObject
{
private:
	static bool isLoadedResource;
	void LoadResources();
public:
	RestartPoint();
	RestartPoint(int id, float x, float y, int width, int height, oType type);
	~RestartPoint();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
};

#endif __RESTARTPOINT__