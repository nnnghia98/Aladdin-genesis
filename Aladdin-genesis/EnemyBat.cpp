#include "EnemyBat.h"

bool EnemyBat::isLoadedSprite = false;

void EnemyBat::LoadSprite()
{
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_BAT);

	sprites->Add(41941, 9, 18, 16, 34, texture);
	sprites->Add(41942, 20, 10, 41, 32, texture);
	sprites->Add(41943, 48, 13, 67, 36, texture);
	sprites->Add(41944, 76, 18, 97, 32, texture);
	sprites->Add(41946, 10, 60, 34, 75, texture);
	sprites->Add(41947, 39, 52, 52, 75, texture);
	sprites->Add(41948, 56, 58, 86, 75, texture);
	sprites->Add(41949, 89, 67, 121, 83, texture);
	sprites->Add(41950, 128, 67, 136, 92, texture);
	sprites->Add(41951, 143, 67, 163, 83, texture);
	sprites->Add(41952, 165, 61, 199, 75, texture);
	sprites->Add(41954, 10, 119, 23, 132, texture);
	sprites->Add(41955, 38, 111, 89, 139, texture);
	sprites->Add(41956, 93, 113, 115, 136, texture);
	sprites->Add(41957, 128, 101, 150, 154, texture);
	sprites->Add(41958, 160, 106, 189, 155, texture);
	sprites->Add(41959, 199, 106, 228, 159, texture);
	sprites->Add(41960, 233, 110, 264, 154, texture);
	sprites->Add(41961, 275, 106, 298, 157, texture);
	sprites->Add(41962, 306, 106, 335, 157, texture);

	isLoadedSprite = true;
}

EnemyBat::EnemyBat(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = ENEMYBAT;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 1;
	LoadResource();
	currentState = BAT_STAY;
	vx = 0.1f;
	health = 1;
	stayPoint.x = x;
	stayPoint.y = y;
}

EnemyBat::~EnemyBat()
{
}


void EnemyBat::LoadResource()
{

	//Animations * anim = Animations::GetInstance();
	if (!isLoadedSprite)
		LoadSprite();
	//bat fly
	Animation * ani = new Animation(120, 0);
	ani->Add(41941, 3000);
	this->animations[BAT_STAY] = ani;

	//bat attack
	ani = new Animation(120, 4);
	ani->Add(41942);
	ani->Add(41943);
	ani->Add(41944);
	ani->Add(41946);
	ani->Add(41947);
	ani->Add(41948);
	ani->Add(41949);
	ani->Add(41950);
	ani->Add(41951);
	ani->Add(41952);
	//anim->Add(205, ani);
	this->animations[BAT_FLY] = ani;

	//bat death
	ani = new Animation(120);
	ani->Add(41954);
	ani->Add(41955);
	ani->Add(41956);
	ani->Add(41957);
	ani->Add(41958);
	ani->Add(41959);
	ani->Add(41960);
	ani->Add(41961);
	ani->Add(41962);
	this->animations[BAT_DEATH] = ani;
}

void EnemyBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = (float)x;
	top = (float)y;
	right = left + (float)width;
	bottom = top + (float)height;
	if (currentState == BAT_DEATH || health <= 0)
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
}

void EnemyBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	if (health < 0)
		return;
	if (currentState == BAT_STAY)
	{
		if (stayPoint.distance(aladdinPosition) < 100)
		{
			currentState = BAT_FLY;
			d = stayPoint.distance(aladdinPosition) / 35;
			count = 0;
			n = 1;
		}
	}
	else if (currentState == BAT_FLY)
	{
		count++;
		if (count >= 100)
			n = -1;
		if (n == 1)
		{
			float dtemp = aladdinPosition.distance(x, y);
			dx = (aladdinPosition.x - x) * d / dtemp;
			dy = (aladdinPosition.y - y) * d / dtemp;
		}
		else 
		{
			float dtemp = stayPoint.distance(x, y);
			dx = (stayPoint.x - x) * d / dtemp;
			dy = (stayPoint.y - y) * d / dtemp;
			if (dtemp < d)
			{
				dx = stayPoint.x - x;
				dy = stayPoint.y - y;
			}
		}
		x += dx;
		y += dy;
		if (stayPoint.x == x && stayPoint.y == y)
			currentState = BAT_STAY;
	}

	
}

void EnemyBat::Render(int flip)
{
	if (this->health > 0 || animations[BAT_DEATH]->GetCountFrame()-2 > animations[BAT_DEATH]->GetCurrentFrame())
		animations[currentState]->Render(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	
}

void EnemyBat::SetCurrentState(int state)
{
	currentState = state;
	if (state == BAT_DEATH)
		currentState = BAT_DEATH;
	
}