#include "Drill.h"

void Drill::ChangeAnim(Keyboard* key)
{
	drillAnim->SetFrame(position, flipFlag, 20, 0, 10, true);
}

void Drill::Update(float dt, Keyboard* key)
{
	ChangeAnim(key);
	Object::Update(dt, key);
	drillAnim->Update(dt, key);
}

void Drill::Render(Viewport* viewport)
{
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(drillAnim->GetRect(),
			drillAnim->GetCenter(),
			drillAnim->GetPosition(),
			drillAnim->GetScale(),
			drillAnim->GetTransform(),
			drillAnim->GetAngle());
		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		drillAnim->SetIndex(0);
	}
}

Drill::Drill()
{
}

Drill::Drill(Sprite* sprite, SpriteSheet* info, D3DXVECTOR2 pos)
{
	this->sprite = sprite;
	drillAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	this->allowDraw = true;
	flipFlag = false;
	this->position = pos;

}


Drill::~Drill()
{
}
