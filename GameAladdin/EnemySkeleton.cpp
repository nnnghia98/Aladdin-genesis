#include "EnemySkeleton.h"
#include "Sound.h"

bool EnemySkeleton::isLoadedSprite = false;

void EnemySkeleton::LoadSprite()
{
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_SKELETON);
	isLoadedSprite = true;
	sprites->Add(41915, 16, 70, 102, 96, texture, 55, -5);
	sprites->Add(41916, 138, 67, 218, 96, texture, 52, 1);
	sprites->Add(41917, 262, 50, 337, 95, texture, 36, 6);
	sprites->Add(41918, 394, 36, 456, 96, texture, 21, 19);
	sprites->Add(41919, 518, 28, 568, 95, texture, 14, 31);
	sprites->Add(41920, 639, 24, 687, 95, texture, 10, 33);
	sprites->Add(41921, 761, 20, 809, 95, texture, 6, 33);
	sprites->Add(41922, 882, 14, 933, 95, texture, 0, 30);
	sprites->Add(41923, 1002, 14, 1053, 95, texture, 0, 30);
	sprites->Add(41924, 1122, 14, 1174, 95, texture, 0, 29);
	sprites->Add(41925, 1125, 14, 1193, 95, texture, 0, 13);
	sprites->Add(41926, 1348, 7, 1415, 96, texture, -8, 14);
	sprites->Add(41927, 43, 133, 93, 215, texture, -1, 31);
	sprites->Add(41928, 163, 134, 212, 215, texture, 0, 32);
	sprites->Add(41929, 261, 131, 322, 215, texture, -3, 20);
	sprites->Add(41930, 378, 140, 442, 215, texture, 6, 17);
	sprites->Add(41931, 490, 130, 564, 215, texture, -4, 7);
	sprites->Add(41932, 610, 124, 691, 215, texture, -10, 0);
	sprites->Add(41933, 731, 138, 826, 215, texture, 4, -14);
	sprites->Add(41934, 860, 136, 920, 215, texture, 2, 21);
	sprites->Add(41936, 1009, 180, 1025, 185, texture);
	sprites->Add(41937, 1138, 176, 1144, 191, texture);
	sprites->Add(41938, 1256, 177, 1268, 190, texture);
	sprites->Add(41939, 1376, 181, 1382, 189, texture);
}

void EnemySkeleton::LoadResource()
{
	Animation * ani = new Animation(120);
	ani->Add(41915);
	this->animations[SKELETON_STAY] = ani;
	ani = new Animation(120);
	ani->Add(41916);
	ani->Add(41917);
	ani->Add(41918);
	ani->Add(41919);
	ani->Add(41920);
	ani->Add(41921);
	ani->Add(41922);
	ani->Add(41923);
	ani->Add(41924);
	ani->Add(41925);
	ani->Add(41926);
	ani->Add(41927);
	ani->Add(41928);
	ani->Add(41929);
	ani->Add(41930);
	ani->Add(41931);
	ani->Add(41932);
	ani->Add(41933);
	ani->Add(41934);
	this->animations[SKELETON_DEATH] = ani;
}

void EnemySkeleton::Render(int flip)
{
	if (health>0 && !isDeath)
		animations[currentState]->Render(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam(), 255, nx);
	for (int i = 0; i < skeletons.size(); i++)
	{
		skeletons[i]->Render();
	}
}

void EnemySkeleton::SetCurrentState(int currentState)
{
	this->currentState = currentState;
	if (this->currentState == 1)
		health = 1;
}

void EnemySkeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (isDeath)
	{
		for (int i = 0; i < skeletons.size(); i++)
		{
			Skeleton * ske = skeletons[i];
			skeletons.erase(skeletons.begin() + i);
			delete ske;
		}
		return;
	}
		
	for (int i = 0; i < skeletons.size(); i++)
	{
		skeletons[i]->Update(dt);
		float x, y;
		skeletons[i]->GetPosition(x, y);
	}
	if (aladdinPoint.distance(x, y) < 100)
		currentState = SKELETON_DEATH;
	if (dTime != -1)
	{
		dTime += dt;
		if (dTime > 1500)
		{
			for (int i = 0; i < skeletons.size(); i++)
			{
				Skeleton * ske = skeletons[i];
				skeletons.erase(skeletons.begin() + i);
				delete ske;
			}
			isDeath = true;
		}
		return;
	}
	
	if (currentState == SKELETON_DEATH && animations[currentState]->GetCountFrame() - 2 == animations[currentState]->GetCurrentFrame())
	{
		health = 0;
		time_t t;
		srand((unsigned)time(&t));
		for (int i = 0; i < 10; i++)
		{
			int result1 = rand() % 100 - 50;
			int result2 = rand() % 100 - 80;
			Skeleton * ske = new Skeleton(nx,x,y, (float)result1 / 100, (float)result2 / 100);
			skeletons.push_back(ske);
		}
		dTime = 0;
		Sound::GetInstance()->Play(eSound::sound_Skeleton);
	}
}

void EnemySkeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = (float)x;
	top = (float)y;
	right = left + (float)width;
	bottom = top + (float)height;
	if (isDeath)
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
	if (health <= 0)
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
}

EnemySkeleton::EnemySkeleton(int id, float x, float y, int width, int height, oType type)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->health = 1;
	this->height = height;
	this->type = type;
	if(!isLoadedSprite)
		LoadSprite();
	isDeath = false;
	LoadResource();
	currentState = SKELETON_STAY;
}


EnemySkeleton::~EnemySkeleton()
{
}
