#pragma once
#include "Object.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Keyboard.h"
#include "Viewport.h"
class Drill :public Object
{
protected:
	Animation * drillAnim;
public:
	void ChangeAnim(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	Drill();
	Drill(Sprite *sprite, SpriteSheet *info, D3DXVECTOR2 pos);
	~Drill();
};


