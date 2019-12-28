#include "Arrow.h"

bool Arrow::isLoadedResource = false;

void Arrow::LoadResources()
{
	isLoadedResource = true;
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_RESOURCE_MAP1);
	sprites->Add(41822, 32, 668, 55, 688, texture);
	sprites->Add(41823, 60, 668, 83, 691, texture);
	sprites->Add(41824, 88, 668, 114, 696, texture);
	sprites->Add(41825, 119, 668, 152, 699, texture);
	sprites->Add(41826, 157, 668, 199, 700, texture);
	sprites->Add(41827, 204, 668, 253, 703, texture);

	Animation * ani = new Animation(50);
	ani->Add(41822,700);
	ani->Add(41823,10);
	ani->Add(41824,10);
	ani->Add(41825,10);
	ani->Add(41826,10);
	ani->Add(41827,700);
	anim->Add(41822, ani);
	this->animations[STATE1] = ani;
}

Arrow::Arrow(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = ARROW;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[STATE1] = Animations::GetInstance()->Get(41822);
	currentState = STATE1;
}


Arrow::~Arrow()
{
}

void Arrow::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (animations[STATE1]->GetCurrentFrame() > 3)
	{
		left = (float)x+30;
		top = (float)y+5;
		right = left + (float)width-30;
		bottom = top + ((float)height-20);
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Arrow::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Arrow::Render(int flip)
{
	animations[STATE1]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());

}
