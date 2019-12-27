#ifndef _APPLEITEM_H
#define _APPLEITEM_H

#include "Entity.h"
#include "Audio.h"

class AppleItem: public Entity
{
private:
	bool isSound;
public:
	AppleItem(float x, float y);
	~AppleItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
};

#endif