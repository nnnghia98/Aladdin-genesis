#include "Rope.h"



Rope::Rope()
{
	GameObject::GameObject();
	type = WALL;
}

Rope::Rope(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	this->id = id;
	type = type;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
}


Rope::~Rope()
{
}

void Rope::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = (float)x;
	top = (float)y;
	right = left + (float)width;
	bottom = top + (float)height;
}