#include "EnemyBig.h"
#include "Sound.h"

bool EnemyBig::isLoadedSprite = false;

void EnemyBig::LoadSprite()
{
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ENEMY);

	//ENEMY_WALK
	sprites->Add(51020, 2, 320, 49, 372, texture, -2);
	sprites->Add(51021, 55, 318, 107, 372, texture, -4);
	sprites->Add(51022, 111, 317, 167, 372, texture, -5);
	sprites->Add(51023, 173, 318, 224, 372, texture, -4);
	sprites->Add(51024, 230, 320, 279, 372, texture, -2);
	sprites->Add(51025, 284, 319, 326, 372, texture, -3);
	sprites->Add(51026, 334, 316, 378, 372, texture, -6);
	sprites->Add(51027, 382, 318, 429, 372, texture, -4);
	sprites->Add(51028, 5, 449, 49, 502, texture, -3);
	sprites->Add(51029, 56, 448, 93, 502, texture, -4);
	sprites->Add(51030, 98, 449, 152, 502, texture, -3);
	sprites->Add(51031, 157, 449, 215, 502, texture, -3);
	sprites->Add(51032, 221, 449, 270, 502, texture, -3);
	sprites->Add(51033, 278, 449, 322, 502, texture, -3);
	sprites->Add(51034, 6, 573, 61, 625, texture, -2);
	sprites->Add(51035, 65, 581, 132, 625, texture, 6);
	sprites->Add(51036, 140, 583, 210, 625, texture, 8);
	sprites->Add(51037, 216, 582, 291, 625, texture, 7);
	sprites->Add(51038, 297, 580, 385, 625, texture, 5);
	sprites->Add(51039, 395, 579, 490, 625, texture, 4);
	sprites->Add(51040, 6, 642, 49, 702, texture, -10);
	sprites->Add(51041, 61, 629, 104, 702, texture, -23);
	sprites->Add(51042, 116, 636, 168, 702, texture, -16);
	sprites->Add(51043, 178, 646, 292, 702, texture, -6);
	sprites->Add(51044, 300, 629, 391, 702, texture, -23);
	sprites->Add(51045, 179, 719, 292, 775, texture, -6);
	sprites->Add(51046, 305, 704, 397, 777, texture, -23);
	sprites->Add(51047, 6, 812, 60, 860, texture, 2);
	sprites->Add(51048, 71, 789, 134, 860, texture, -21);
	sprites->Add(51049, 138, 803, 203, 860, texture, -7);
	sprites->Add(51050, 210, 794, 281, 860, texture, -16);
	sprites->Add(51051, 290, 796, 364, 860, texture, -14);
	sprites->Add(51052, 382, 804, 448, 860, texture, -6);


	isLoadedSprite = true;
}

EnemyBig::EnemyBig(int id, float x, float y, int width, int height, oType type, int leftMargin, int rightMargin)
{
	GameObject::GameObject();
	type = ENEMYFAT;
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

EnemyBig::~EnemyBig()
{
}


void EnemyBig::LoadResource()
{

	//Animations * anim = Animations::GetInstance();
	if (!isLoadedSprite)
		LoadSprite();
	Animation * ani = new Animation(120, 0);
	ani->Add(51020);
	ani->Add(51021);
	ani->Add(51022);
	ani->Add(51023);
	ani->Add(51024);
	ani->Add(51025);
	ani->Add(51026);
	ani->Add(51027);
	//anim->Add(203, ani);
	this->animations[ENEMY_WALK] = ani;

	//ENEMY_DEFIANT
	ani = new Animation(120);
	ani->Add(51028);
	ani->Add(51029);
	ani->Add(51030);
	ani->Add(51031);
	ani->Add(51032);
	ani->Add(51033);

	//anim->Add(204, ani);
	this->animations[ENEMY_DEFIANT] = ani;

	//ENEMY_ATTACKING
	ani = new Animation(90);
	ani->Add(51034);
	ani->Add(51035);
	ani->Add(51036);
	ani->Add(51037);
	ani->Add(51038);
	ani->Add(51039);
	ani->Add(51040);
	ani->Add(51041);
	ani->Add(51042);
	ani->Add(51043);
	ani->Add(51044);
	ani->Add(51045);
	ani->Add(51046);
	//anim->Add(205, ani);
	this->animations[ENEMY_ATTACKING] = ani;

	//ENEMY_DEATH
	ani = new Animation(120);
	ani->Add(51047);
	ani->Add(51048);
	ani->Add(51049);
	ani->Add(51050);
	ani->Add(51051);
	ani->Add(51052);
	//anim->Add(206, ani);
	this->animations[ENEMY_DEATH] = ani;
}

void EnemyBig::GetBoundingBox(float & left, float & top, float & right, float & bottom)
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
			if (nx > 0) {
				right += 60;
				
				top -= 20;
			}
			else {
				
				top -= 20;
				left -= 60;
			}
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

void EnemyBig::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
				x = RightMargin - width-1;
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

void EnemyBig::Render(int flip)
{
	if (this->health <= 0)
		return;
	animations[currentState]->Render(x-Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam(), 255, nx, 47);
}

void EnemyBig::SetCurrentState(int state)
{
	if (!isOnlyStay)
		return;
	if (state == currentState && state != ENEMY_DEATH)
	{
		if(animations[currentState]->GetCountFrame() - 1 == animations[currentState]->GetCurrentFrame())
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
		Sound::GetInstance()->Play(eSound::sound_GuardHit);
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
		//Sound::GetInstance()->Play(eSound::sound_GuardBeckon);
		currentState = ENEMY_DEFIANT;
		animations[currentState]->SetCurrentFrame(0);
		break;
	default:
		break;
	}
}