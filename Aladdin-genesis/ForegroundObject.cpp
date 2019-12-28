#include "ForegroundObject.h"



void ForegroundObject::Render()
{
	Sprites::GetInstance()->Get(idSprite)->Draw(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
}

void ForegroundObject::RenderWithEffect(float a, float b, float speed)
{
	Sprites::GetInstance()->Get(idSprite)->Draw(a - Camera::GetInstance()->GetXCam()*speed, b - Camera::GetInstance()->GetYCam()*speed);
}

void ForegroundObject::RenderWithEffect(float speed)
{
	Sprites::GetInstance()->Get(idSprite)->Draw(x - Camera::GetInstance()->GetXCam()*speed, y - Camera::GetInstance()->GetYCam()*speed);
}

ForegroundObject::ForegroundObject(int idSprite, float x, float y, int width, int height)
{
	this->idSprite = idSprite;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


ForegroundObject::~ForegroundObject()
{
}
