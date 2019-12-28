#include "EnemySmall.h"

bool EnemySmall::isLoadedSprite = false;

void EnemySmall::LoadSprite()
{
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ENEMY);

	//ENEMY_WALK
	sprites->Add(41889, 2, 9, 47, 76, texture);
	sprites->Add(41890, 53, 10, 98, 76, texture);
	sprites->Add(41891, 109, 11, 155, 76, texture);
	sprites->Add(41892, 164, 11, 209, 76, texture);
	sprites->Add(41893, 214, 10, 251, 76, texture);
	sprites->Add(41894, 259, 9, 302, 76, texture);
	sprites->Add(41895, 308, 9, 358, 76, texture);
	sprites->Add(41896, 363, 11, 399, 76, texture);
	sprites->Add(41898, 9, 82, 46, 156, texture);
	sprites->Add(41899, 53, 96, 102, 156, texture);
	sprites->Add(41900, 109, 98, 201, 156, texture);
	sprites->Add(41901, 203, 97, 289, 156, texture);
	sprites->Add(41902, 292, 96, 369, 156, texture);
	sprites->Add(41903, 382, 96, 423, 156, texture);
	sprites->Add(41905, 8, 175, 52, 233, texture);
	sprites->Add(41906, 59, 185, 99, 233, texture);
	sprites->Add(41907, 114, 160, 153, 233, texture);
	sprites->Add(41908, 161, 165, 202, 233, texture);
	sprites->Add(41909, 210, 171, 256, 233, texture);
	sprites->Add(41910, 268, 162, 310, 233, texture);
	sprites->Add(41911, 318, 184, 365, 233, texture);
	sprites->Add(41912, 378, 185, 418, 233, texture);
	sprites->Add(41913, 433, 166, 478, 233, texture);


	isLoadedSprite = true;
}

EnemySmall::EnemySmall(int id, float x, float y, int width, int height, oType type, int leftMargin, int rightMargin)
{
	GameObject::GameObject();
	type = ENEMYTHIN;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	if (leftMargin == -1)
		LeftMargin = x;
	else
		LeftMargin = leftMargin;
	if (RightMargin == -1)
		RightMargin = x;
	else
		RightMargin = rightMargin;
	nx = 1;
	LoadResource();
	currentState = ENEMY_WALK;
	vx = 0.1f;
	health = 2;
	isOnlyStay = false;
}

EnemySmall::~EnemySmall()
{
}


void EnemySmall::LoadResource()
{

	//Animations * anim = Animations::GetInstance();
	if (!isLoadedSprite)
		LoadSprite();
	Animation * ani = new Animation(120, 0);
	ani->Add(41889);
	ani->Add(41890);
	ani->Add(41891);
	ani->Add(41892);
	ani->Add(41893);
	ani->Add(41894);
	ani->Add(41895);
	ani->Add(41896);
	//anim->Add(203, ani);
	this->animations[ENEMY_WALK] = ani;

	//ENEMY_DEFIANT
	ani = new Animation(120);
	ani->Add(41889);

	//anim->Add(204, ani);
	this->animations[ENEMY_DEFIANT] = ani;

	//ENEMY_ATTACKING
	ani = new Animation(90);
	ani->Add(41898);
	ani->Add(41899);
	ani->Add(41900);
	ani->Add(41901);
	ani->Add(41902);
	ani->Add(41903);
	//anim->Add(205, ani);
	this->animations[ENEMY_ATTACKING] = ani;

	//ENEMY_DEATH
	ani = new Animation(120);
	ani->Add(41905);
	ani->Add(41906);
	ani->Add(41907);
	ani->Add(41908);
	ani->Add(41909);
	ani->Add(41910);
	ani->Add(41911);
	ani->Add(41912);
	ani->Add(41913);
	//anim->Add(206, ani);
	this->animations[ENEMY_DEATH] = ani;
}

void EnemySmall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState != ENEMY_DEATH || health > 0)
	{
		left = (float)x;
		top = (float)y;
		right = left + (float)width;
		bottom = top + (float)height;
		switch (currentState)
		{
		case ENEMY_ATTACKING:
			if (nx > 0)
				right += 20;
			else
				left -= 20;
			break;
		case ENEMY_WALK:

			break;
		case ENEMY_DEATH:
			break;
		default:

			break;
		}
	}
	else
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
}

void EnemySmall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	if (!isOnlyStay)
	{
		currentState = ENEMY_WALK;
		x += dx;
		if (x + width > RightMargin || x < LeftMargin)
		{
			isOnlyStay = true;
			if (x + width > RightMargin)
				x = RightMargin - width - 1;
			else
				x = LeftMargin + 1;
		}
	}
	if (animations[ENEMY_DEATH]->GetCountFrame() - 1 == animations[ENEMY_DEATH]->GetCurrentFrame())
		animations[ENEMY_DEATH]->SetCurrentFrame(0);
	if (isOnlyStay)
	{
		srand(time(NULL));
		int result = rand() % 5 + 1;
		if (result == 1)
		{
			SetCurrentState(ENEMY_ATTACKING);
		}
		else
		{
			SetCurrentState(ENEMY_DEFIANT);
		}
	}
}

void EnemySmall::Render(int flip)
{
	if (this->health <= 0)
		return;
	animations[currentState]->Render(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam(), 255, nx, 47);
	//DebugOut((wchar_t*)L"cur state %d, total = %d, frame = %d, health = %d\n", currentState, animations[currentState]->GetCountFrame(), animations[currentState]->GetCurrentFrame(), health);
}

void EnemySmall::SetCurrentState(int state)
{
	if (!isOnlyStay)
		return;
	if (state == currentState && state != ENEMY_DEATH)
	{
		if (animations[currentState]->GetCountFrame() - 1 == animations[currentState]->GetCurrentFrame())
			animations[currentState]->SetCurrentFrame(0);
		return;
	}

	if (currentState == ENEMY_DEATH && animations[currentState]->GetCountFrame() - 2 > animations[currentState]->GetCurrentFrame())
		return;
	switch (state)
	{
	case ENEMY_ATTACKING:
		currentState = ENEMY_ATTACKING;
		animations[currentState]->SetCurrentFrame(0);
		break;
	case ENEMY_DEATH:
		if (state == ENEMY_DEATH && currentState == ENEMY_DEATH)
			break;
		this->health--;
		currentState = ENEMY_DEATH;
		animations[currentState]->SetCurrentFrame(0);
		break;
	case ENEMY_DEFIANT:
		if (currentState == ENEMY_ATTACKING && animations[currentState]->GetCountFrame() - 2 > animations[currentState]->GetCurrentFrame())
			break;
		currentState = ENEMY_DEFIANT;
		animations[currentState]->SetCurrentFrame(0);
		break;
	default:
		break;
	}
}