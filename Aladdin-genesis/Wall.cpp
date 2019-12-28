#include "Wall.h"



Wall::Wall()
{
	GameObject::GameObject();
	type = WALL;
}

Wall::Wall(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	this->id = id;
	type = WALL;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
}


Wall::~Wall()
{
}

void Wall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = (float)x;
	top = (float)y;
	right = left + (float)width;
	bottom = top + (float)height;
}