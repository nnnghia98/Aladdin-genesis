#include "Skeleton.h"



void Skeleton::Render(int flip)
{
	//DebugOut((wchar_t*)L"t=x = %f, y = %f", x, y);
	animations[1]->Render(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
}

void Skeleton::SetCurrentState(int currentState)
{
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += 0.012;
	GameObject::Update(dt);
	x += dx;
	y += dy;
}

void Skeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = (float)x;
	top = (float)y;
	right = left + 5;
	bottom = top + 5;
	if (isDeath)
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
}

Skeleton::Skeleton(float nx,float x, float y, float vx, float vy)
{
	Animation *ani = new Animation(60);
	ani->Add(41936);
	ani->Add(41937);
	ani->Add(41938);
	ani->Add(41939);
	this->animations[1] = ani;
	this->nx = nx;
	this->vx = vx;
	this->vy = vy;
	this->type = SKELETON;
	this->x = x;
	this->y = y;
	isDeath = false;
}


Skeleton::~Skeleton()
{
}
