#include "Bob.h"

bool Bob::isLoadedResource = false;

void Bob::LoadResources()
{
	isLoadedResource = true;
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_RESOURCE_MAP1);
	sprites->Add(51001, 258, 639, 272, 684, texture);
	sprites->Add(51002, 277, 639, 292, 686, texture);
	sprites->Add(51003, 297, 639, 312, 689, texture);
	sprites->Add(51004, 317, 639, 332, 691, texture);
	sprites->Add(51005, 337, 639, 353, 695, texture);
	sprites->Add(51006, 358, 639, 374, 699, texture);
	sprites->Add(51007, 379, 639, 397, 704, texture);
	sprites->Add(51008, 402, 639, 423, 706, texture);
	sprites->Add(51009, 428, 639, 454, 704, texture);
	sprites->Add(51010, 459, 639, 487, 702, texture);
	sprites->Add(51011, 492, 639, 522, 698, texture);
	sprites->Add(51012, 527, 639, 558, 696, texture);
	sprites->Add(51013, 563, 639, 595, 695, texture);
	sprites->Add(51014, 600, 639, 633, 692, texture);
	sprites->Add(51015, 638, 639, 671, 691, texture);
	Animation * ani = new Animation(90);
	ani->Add(51001, 200);
	ani->Add(51002);
	ani->Add(51003);
	ani->Add(51004);
	ani->Add(51005);
	ani->Add(51006);
	ani->Add(51007);
	ani->Add(51008);
	ani->Add(51009);
	ani->Add(51010);
	ani->Add(51011);
	ani->Add(51012);
	ani->Add(51013);
	ani->Add(51014);
	ani->Add(51015, 200);

	anim->Add(51001, ani);
	this->animations[STATE1] = ani;
}

Bob::Bob(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = BOB;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[STATE1] = Animations::GetInstance()->Get(51001);
	currentState = STATE1;
}


Bob::~Bob()
{
}

void Bob::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (id % 2)
	{
		if (animations[STATE1]->GetCurrentFrame() > 11 && animations[STATE1]->GetCurrentFrame() < 15)
		{
			left = (float)x + 10;
			top = (float)y + 25;
			right = left + (float)width - 10;
			bottom = top + (float)height - 30;
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
		
		if (animations[STATE1]->GetCountFrame() - animations[STATE1]->GetCurrentFrame() >= 11)
		{
			left = (float)x + 10;
			top = (float)y + 25;
			right = left + (float)width - 10;
			bottom = top + (float)height - 30;
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

void Bob::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
			if (coObjects->at(i)->GetType() == BOB && coObjects->at(i)->GetId() % 2)
			{
				e = coObjects->at(i);
				return;
			}
		}
		for (; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->GetType() == BOB && coObjects->at(i)->GetId() % 2 == 0)
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

void Bob::Render(int flip)
{
	if (id % 2)
		animations[STATE1]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	else
		animations[STATE1]->CustomRender(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());

}
