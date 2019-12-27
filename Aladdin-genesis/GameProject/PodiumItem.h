#ifndef _PODIUMITEM_H
#define _PODIUMITEM_H

#include "Entity.h"
#include "Audio.h"

class PodiumItem : public Entity
{
private:
	bool isSound;
public:
	PodiumItem(float x, float y);
	~PodiumItem();

	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif