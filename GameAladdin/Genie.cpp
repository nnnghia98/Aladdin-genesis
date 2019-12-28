#include "Genie.h"

bool Genie::isLoadedResource = false;

void Genie::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	LPDIRECT3DTEXTURE9 texture1 = Textures::GetInstance()->Get(ID_TEX_STATEDISAPPEAR);

	sprites->Add(41840, 328, 3440, 366, 3490, texture);
	sprites->Add(41841, 376, 3438, 419, 3490, texture);
	sprites->Add(41842, 429, 3446, 472, 3490, texture);
	sprites->Add(41843, 482, 3446, 527, 3490, texture);
	Animation * ani = new Animation(300);
	ani->Add(41840);
	ani->Add(41841);
	ani->Add(41842);
	ani->Add(41843);
	anim->Add(41840, ani);
	this->animations[GENIE_STATE_1] = ani;

	sprites->Add(41865, 480, 15, 517, 52, texture1);
	sprites->Add(41866, 528, 9, 570, 52, texture1);
	sprites->Add(41867, 584, 9, 625, 52, texture1);
	sprites->Add(41868, 8, 67, 51, 108, texture1);
	sprites->Add(41869, 64, 67, 106, 108, texture1);
	sprites->Add(41870, 120, 69, 163, 108, texture1);
	sprites->Add(41871, 176, 71, 219, 108, texture1);
	sprites->Add(41872, 232, 71, 274, 108, texture1);
	sprites->Add(41873, 288, 64, 331, 108, texture1);
	sprites->Add(41874, 344, 73, 385, 108, texture1);
	sprites->Add(41875, 392, 84, 433, 108, texture1);
	sprites->Add(41876, 440, 84, 479, 108, texture1);
	sprites->Add(41877, 488, 88, 514, 108, texture1);
	sprites->Add(41878, 528, 84, 576, 108, texture1);
	ani = new Animation(90);
	ani->Add(41865);
	ani->Add(41866);
	ani->Add(41867);
	ani->Add(41868);
	ani->Add(41869);
	ani->Add(41870);
	ani->Add(41871);
	ani->Add(41872);
	ani->Add(41873);
	ani->Add(41874);
	ani->Add(41875);
	ani->Add(41876);
	ani->Add(41877);
	ani->Add(41878);
	anim->Add(41865, ani);
	this->animations[GENIE_STATE_2] = ani;
}

Genie::Genie(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = oType::GENIE;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[GENIE_STATE_1] = Animations::GetInstance()->Get(41840);
	this->animations[GENIE_STATE_2] = Animations::GetInstance()->Get(41865);
	SetCurrentState(GENIE_STATE_1);
}


Genie::~Genie()
{
}

void Genie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == GENIE_STATE_1) {
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

void Genie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Genie::Render(int flip)
{
	if (currentState == GENIE_STATE_2 && animations[currentState]->GetCurrentFrame() == animations[currentState]->GetCountFrame() - 1)
		return;
	animations[currentState]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	//RenderBoundingBox();
}
