#include "Apple.h"

bool Apple::isLoadedResource = false;

void Apple::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	LPDIRECT3DTEXTURE9 texture1 = Textures::GetInstance()->Get(ID_TEX_STATEDISAPPEAR);

	sprites->Add(41802, 422, 1501, 429, 1508, texture);
	Animation * ani = new Animation(300);
	ani->Add(41802);
	anim->Add(41802, ani);
	this->animations[APPLE_STATE_1] = ani;

	sprites->Add(41880, 80, 31, 118, 52, texture1);
	sprites->Add(41881, 128, 39, 145, 52, texture1);
	sprites->Add(41882, 152, 28, 191, 52, texture1);
	sprites->Add(41883, 200, 36, 230, 52, texture1);
	sprites->Add(41884, 240, 41, 284, 52, texture1);
	sprites->Add(41885, 296, 46, 302, 52, texture1);
	sprites->Add(41886, 312, 32, 331, 52, texture1);
	sprites->Add(41887, 344, 25, 370, 52, texture1);
	ani = new Animation(30);
	ani->Add(41880);
	ani->Add(41881);
	ani->Add(41882);
	ani->Add(41883);
	ani->Add(41884);
	ani->Add(41885);
	ani->Add(41886);
	ani->Add(41887);
	anim->Add(41880, ani);
	this->animations[APPLE_STATE_2] = ani;
}

Apple::Apple()
{
	GameObject::GameObject();
	type = APPLE;
}

Apple::Apple(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = APPLE;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[APPLE_STATE_1] = Animations::GetInstance()->Get(41802);
	this->animations[APPLE_STATE_2] = Animations::GetInstance()->Get(41880);
	SetCurrentState(APPLE_STATE_1);
}


Apple::~Apple()
{
}

void Apple::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == APPLE_STATE_1) {
		left = (float)x;
		top = (float)y;
		right = left + (float)width;
		bottom = top + (float)height;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Apple::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Apple::Render(int flip)
{
	if (currentState == APPLE_STATE_2 && animations[currentState]->GetCurrentFrame() == animations[currentState]->GetCountFrame() - 1)
		return;
	animations[currentState]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
}
