#include "AppleOfAladdin.h"

bool AppleOfAladdin::isLoadedResource = false;

void AppleOfAladdin::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);

	sprites->Add(41811, 422, 1501, 429, 1508, texture);
	sprites->Add(41812, 433, 1501, 442, 1508, texture);
	sprites->Add(41813, 445, 1501, 452, 1509, texture);
	sprites->Add(41814, 455, 1501, 464, 1507, texture);
	Animation * ani = new Animation(300, 0);
	ani->Add(41811, 60);
	ani->Add(41812, 60);
	ani->Add(41813, 60);
	ani->Add(41814, 60);
	anim->Add(41811, ani);

	sprites->Add(41816, 476, 1512, 483, 1522, texture);
	sprites->Add(41817, 493, 1504, 513, 1522, texture);
	sprites->Add(41818, 523, 1500, 552, 1522, texture);
	sprites->Add(41819, 562, 1497, 593, 1522, texture);
	sprites->Add(41820, 603, 1495, 633, 1522, texture);
	ani = new Animation(90, -1);
	ani->Add(41816);
	ani->Add(41817);
	ani->Add(41818);
	ani->Add(41819);
	ani->Add(41820);
	anim->Add(41816, ani);
}

AppleOfAladdin::AppleOfAladdin(float x, float y, float nx)
{
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->width = 11;
	this->height = 11;
	this->ny = 1.0f;
	this->vx = APPLE_SPEED_X;
	this->vy = -APPLE_SPEED_Y;
	
	if (isLoadedResource == false)
		LoadResources();
	currentState = 1;
	this->animations[APPLE_STATE_1] = Animations::GetInstance()->Get(41811);
	this->animations[APPLE_STATE_2] = Animations::GetInstance()->Get(41816);
}


AppleOfAladdin::~AppleOfAladdin()
{
}

void AppleOfAladdin::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == APPLE_STATE_1) {
		left = (float)x;
		top = (float)y;
		right = left + (float)width;
		bottom = top + (float)height;
	}
	else
	{
		left = -1;
		top = -1;
		right = -1;
		bottom = -1;
	}
}

void AppleOfAladdin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += APPLE_GRAVITY * dt;
	
	// xét va chạm giữa apple với các đối tượng
	CollisionWithEnemy(coObjects);
	CollisionWithObjectMap(coObjects);
	if (currentState == APPLE_STATE_1)
	{
		x += dx;
		y += dy;
	}
}

void AppleOfAladdin::Render(int flip)
{
	animations[currentState]->Render(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam(), 255);
}

void AppleOfAladdin::CollisionWithEnemy(vector<LPGAMEOBJECT>* coObject)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	vector<LPGAMEOBJECT> list_enemy;
	list_enemy.clear();
	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetType() == oType::ENEMYFAT
			|| coObject->at(i)->GetType() == oType::ENEMYTHIN
			|| coObject->at(i)->GetType() == oType::ENEMYBAT
			|| coObject->at(i)->GetType() == oType::ENEMYSKELETON
			|| coObject->at(i)->GetType() == oType::JAFAR)
		{
			list_enemy.push_back(coObject->at(i));
		}
	}

	CalcPotentialCollisions(&list_enemy, coEvents);

	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		currentState = APPLE_STATE_2;
		coEventsResult[0]->obj->SetCurrentState(4);
		if(coEventsResult[0]->obj->GetType() == ENEMYBAT)
			coEventsResult[0]->obj->MulHealth();
		if (coEventsResult[0]->obj->GetType() == JAFAR)
			coEventsResult[0]->obj->MulHealth();
		if (coEventsResult[0]->obj->GetType() == ENEMYSKELETON)
		{
			EnemySkeleton * e = (EnemySkeleton *)coEventsResult[0]->obj;
			e->isDeath = true;
			e->MulHealth();
		}
	}
	else
	{
		RECT r1;
		float la, ta, ra, ba;
		GetBoundingBox(la, ta, ra, ba);
		r1.left = la;
		r1.top = ta;
		r1.right = ra;
		r1.bottom = ba;

		for (UINT i = 0; i < list_enemy.size(); i++)
		{
			float lo, to, ro, bo;
			list_enemy[i]->GetBoundingBox(lo, to, ro, bo);
			RECT r2;
			r2.left = lo;
			r2.top = to;
			r2.right = ro;
			r2.bottom = bo;
			RECT dest;
			if (IntersectRect(&dest, &r1, &r2) == true)
			{
				list_enemy[i]->SetCurrentState(4);
				if (list_enemy[i]->GetType() == ENEMYBAT)
					list_enemy[i]->MulHealth();
				if (list_enemy[i]->GetType() == ENEMYSKELETON)
				{
					EnemySkeleton * e = (EnemySkeleton *)list_enemy[i];
					e->isDeath = true;
					e->MulHealth();
				}
				currentState = APPLE_STATE_2;
				if (list_enemy[i]->GetType() == JAFAR)
				{
					list_enemy[i]->MulHealth();
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void AppleOfAladdin::CollisionWithObjectMap(vector<LPGAMEOBJECT>* coObject)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	vector<LPGAMEOBJECT> list_mapobj;
	list_mapobj.clear();
	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetType() == oType::WALL || coObject->at(i)->GetType() == oType::BRICK || coObject->at(i)->GetType() == oType::MOVINGBRICK)
		{
			list_mapobj.push_back(coObject->at(i));
		}
	}

	CalcPotentialCollisions(&list_mapobj, coEvents);

	if (coEvents.size() != 0)
	{
		currentState = APPLE_STATE_2;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
