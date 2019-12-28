#include "Flame.h"

void Flame::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = (float)x;
	top = (float)y+ 50;
	right = left + (float)width - 15;
	bottom = top + (float)height;
}

void Flame::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	x += dx;
	dtime += dt;
	if (dtime > 3000)
		isDeath = true;
}

void Flame::Render(int flip)
{
	animations[currentState]->Render(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());

}

void Flame::SetCurrentState(int currentState)
{

}

Flame::Flame(float x, float y, int width, int height, float nx)
{
	Animation * ani;
	ani = new Animation(90, 0);
	ani->Add(141991);
	ani->Add(141992);
	ani->Add(141993);
	ani->Add(141994);
	ani->Add(141995);
	ani->Add(141996);
	ani->Add(141997);
	ani->Add(141998);
	this->animations[FLAME_1] = ani;
	this->vx = 0.25;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = oType::FLAME;
	dtime = 0;
	isDeath = false;
	currentState = FLAME_1;
	this->nx = nx;
}

Flame::~Flame()
{
}