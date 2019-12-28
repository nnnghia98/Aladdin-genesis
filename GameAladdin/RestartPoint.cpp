#include "RestartPoint.h"

bool RestartPoint::isLoadedResource = false;

void RestartPoint::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ITEM);

	sprites->Add(41853, 19, 424, 39, 457, texture);
	Animation * ani = new Animation(120);
	ani->Add(41853);
	anim->Add(41853, ani);
	this->animations[RESTARTPOINT_STATE_1] = ani;

	sprites->Add(41855, 49, 428, 73, 457, texture);
	sprites->Add(41856, 78, 437, 112, 457, texture);
	sprites->Add(41857, 119, 425, 139, 459, texture);
	sprites->Add(41858, 145, 425, 168, 459, texture);
	sprites->Add(41859, 174, 426, 200, 459, texture);
	sprites->Add(41860, 207, 426, 231, 460, texture);
	sprites->Add(41861, 239, 427, 259, 461, texture);
	sprites->Add(41862, 270, 428, 294, 461, texture);
	sprites->Add(41863, 302, 429, 325, 462, texture);
	ani = new Animation(90);
	ani->Add(41855);
	ani->Add(41856);
	ani->Add(41857);
	ani->Add(41858);
	ani->Add(41859);
	ani->Add(41860);
	ani->Add(41861);
	ani->Add(41862);
	ani->Add(41863);
	anim->Add(41855, ani);
	this->animations[RESTARTPOINT_STATE_2] = ani;
}

RestartPoint::RestartPoint()
{
	GameObject::GameObject();
	type = RESTARTPOINT;
}

RestartPoint::RestartPoint(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = RESTARTPOINT;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[RESTARTPOINT_STATE_1] = Animations::GetInstance()->Get(41853);
	this->animations[RESTARTPOINT_STATE_2] = Animations::GetInstance()->Get(41855);
	SetCurrentState(RESTARTPOINT_STATE_1);
}


RestartPoint::~RestartPoint()
{
}

void RestartPoint::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == RESTARTPOINT_STATE_1) {
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

void RestartPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void RestartPoint::Render(int flip)
{
	animations[currentState]->Render(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
}
