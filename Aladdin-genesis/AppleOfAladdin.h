#ifndef __APPLE_OF_ALADDIN__
#define __APPLE_OF_ALADDIN__
#include  "GameObject.h"

#define APPLE_STATE_1 1 // Trạng thái: Trạng thái bay
#define APPLE_STATE_2 2 // Trạng thái: khi va chạm -> phát nổ
#define APPLE_SPEED_X 0.25f//chỉnh tốc độ quả táo 
#define APPLE_SPEED_Y 0.1f
#define APPLE_GRAVITY 0.00030f

#include "EnemySkeleton.h"
class AppleOfAladdin: public GameObject
{
private:
	static bool isLoadedResource;
	void LoadResources();
public:
	AppleOfAladdin(float x, float y, float nx = 1.0f);
	~AppleOfAladdin();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
	void CollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects);
	void CollisionWithObjectMap(vector<LPGAMEOBJECT>* coObjects);
};
#endif