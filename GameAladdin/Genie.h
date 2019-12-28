#ifndef __GENIE__
#define __GENIE__
#include  "GameObject.h"

#define GENIE_STATE_1 1 // Trạng thái: không có va chạm với aladdin
#define GENIE_STATE_2 2 // Trạng thái: khi va chạm với aladdin -> phát nổ

class Genie : public GameObject
{
private:
	static bool isLoadedResource;
	void LoadResources();
public:
	Genie(int id, float x, float y, int width, int height, oType type);
	~Genie();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
};

#endif __GENIE__