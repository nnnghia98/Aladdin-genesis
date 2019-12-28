#include "MovingBrick.h"

bool MovingBrick::isLoadedResource = false;

void MovingBrick::LoadResource()
{
	isLoadedResource = true;
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_RESOURCE_MAP1);
	sprites->Add(31101, 32, 639, 63, 654, texture);
	sprites->Add(31102, 68, 639, 99, 654, texture);
	sprites->Add(31103, 104, 639, 138, 656, texture);
	sprites->Add(31104, 143, 639, 181, 660, texture);
	sprites->Add(31105, 186, 639, 226, 663, texture);
	Animation * ani = new Animation(60, 3);
	ani->Add(31101, 700);//350
	ani->Add(31102, 100);//250
	ani->Add(31103, 100);//200
	ani->Add(31104, 100);//250
	ani->Add(31105, 700);//350
	anim->Add(31101, ani);
	this->animations[STATE1] = ani;
}

MovingBrick::MovingBrick()
{
	GameObject::GameObject();
	type = MOVINGBRICK;
	if (!isLoadedResource)
		LoadResource();
	Animations * anim = Animations::GetInstance();
	Animation * ani = anim->Get(31101);
	this->animations[STATE1] =ani;
}

MovingBrick::MovingBrick(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = MOVINGBRICK;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResource();
	this->animations[STATE1] = Animations::GetInstance()->Get(31101);

	if (id % 2 == 0)
	{
		int tmp = animations[STATE1]->GetCountFrame();
		animations[STATE1]->SetCurrentFrame(tmp -1);
	}
}


MovingBrick::~MovingBrick()
{
}

void MovingBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (id % 2)
	{
		if (animations[STATE1]->GetCurrentFrame() >= 2)
		{
			left = (float)x;
			top = (float)y;
			right = left + (float)width+10;
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
	else
	{
		if (animations[STATE1]->GetCountFrame()-animations[STATE1]->GetCurrentFrame() >= 2)
		{
			left = (float)x;
			top = (float)y;
			right = left + (float)width+10;
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
}

void MovingBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	if (animations[STATE1]->GetCurrentFrame() == -1)
	{
		int chk = id % 2;
		LPGAMEOBJECT e = NULL;
		LPGAMEOBJECT e2 = NULL;
		int i = 0;
		for (; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->GetType() == MOVINGBRICK && coObjects->at(i)->GetId() % 2)
			{
				e = coObjects->at(i);
				return;
			}
		}
		for (; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->GetType() == MOVINGBRICK && coObjects->at(i)->GetId() % 2 == 0)
			{
				e2 = coObjects->at(i);
				return;
			}
		}
		DWORD now = GetTickCount();
		if (e->GetId() % 2 == chk)
		{
			animations[STATE1]->SetCurrentFrame(e->GetAnimation(1)->GetCurrentFrame());
			animations[STATE1]->SetLastFrameTime(now);
			animations[STATE1]->SetFlagReverse(e->GetAnimation(1)->GetFlagReverse());
		}
		else if (e2->GetId() % 2 == chk)
		{
			animations[STATE1]->SetCurrentFrame(e2->GetAnimation(1)->GetCurrentFrame());
			animations[STATE1]->SetLastFrameTime(now);
			animations[STATE1]->SetFlagReverse(e2->GetAnimation(1)->GetFlagReverse());
		}
		else
		{
			animations[STATE1]->SetCurrentFrame(animations[STATE1]->GetCountFrame() - e->GetAnimation(1)->GetCurrentFrame() - 1);
			animations[STATE1]->SetLastFrameTime(now);
			animations[STATE1]->SetFlagReverse(e->GetAnimation(1)->GetFlagReverse()*(-1));
		}
	}
		
}

void MovingBrick::Render(int flip)
{
	if (id % 2)
		animations[STATE1]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	else
		animations[STATE1]->CustomRender(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	//RenderBoundingBox();
}
