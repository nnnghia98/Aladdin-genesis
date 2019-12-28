#include "Heart.h"

bool Heart::isLoadedResource = false;

void Heart::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);

	sprites->Add(41849, 16, 3510, 32, 3531, texture);
	sprites->Add(41850, 42, 3510, 59, 3531, texture);
	sprites->Add(41851, 69, 3508, 88, 3531, texture);
	Animation * ani = new Animation(120);
	ani->Add(41849);
	ani->Add(41850);
	ani->Add(41851);
	anim->Add(41849, ani);
	this->animations[HEART_STATE_1] = ani;
	sprites->Add(41870, 476, 1512, 483, 1522, texture);
	ani = new Animation(90);
	ani->Add(41870);
	anim->Add(41870, ani);
	this->animations[HEART_STATE_2] = ani;
}

Heart::Heart(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = oType::HEART;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[HEART_STATE_1] = Animations::GetInstance()->Get(41849);
	this->animations[HEART_STATE_2] = Animations::GetInstance()->Get(41870);
	SetCurrentState(HEART_STATE_1);
}


Heart::~Heart()
{
}

void Heart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == HEART_STATE_1) {
		left = (float)x;
		top = (float)y;
		right = left + (float)width;
		bottom = top + (float)height;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Heart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Heart::Render(int flip)
{
	if (currentState == HEART_STATE_2 && animations[currentState]->GetCurrentFrame() == animations[currentState]->GetCountFrame() - 1)
		return;
	animations[currentState]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	//RenderBoundingBox();
}
