#include "NextLevelPoint.h"

NextLevelPoint::NextLevelPoint(int id, float x, float y)
{
	this->x = x;
	this->y = y;
	width = 5;
	height = 5;
	type = oType::NEXTLEVELPOINT;
	this->id = id;
}

NextLevelPoint::~NextLevelPoint()
{
}

void NextLevelPoint::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = (float)x;
	top = (float)y;
	right = left + (float)width;
	bottom = top + (float)height;
}