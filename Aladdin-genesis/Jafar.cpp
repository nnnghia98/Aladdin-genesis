#include "Jafar.h"
#include "Sound.h"
bool Jafar::isLoadedSprite = false;

void Jafar::LoadSprite()
{
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_BOSS);
	sprites->Add(141937, 8, 9, 72, 80, texture, -2);
	sprites->Add(141938, 80, 10, 137, 80, texture, -1);
	sprites->Add(141939, 144, 11, 199, 80, texture, 0);
	sprites->Add(141940, 208, 12, 259, 80, texture, 1);
	sprites->Add(141941, 272, 11, 336, 80, texture, 0);
	sprites->Add(141942, 344, 11, 426, 80, texture, 0);
	sprites->Add(141943, 440, 11, 525, 80, texture, 0);
	sprites->Add(141944, 536, 11, 604, 80, texture, 0);

	sprites->Add(141946, 11, 93, 65, 161, texture, 1);
	sprites->Add(141947, 82, 91, 140, 161, texture, -1);
	sprites->Add(141948, 146, 91, 204, 161, texture, -1);
	sprites->Add(141949, 211, 96, 275, 161, texture, 4);
	sprites->Add(141950, 283, 104, 344, 162, texture, 11);
	sprites->Add(141951, 351, 102, 410, 162, texture, 9);
	sprites->Add(141952, 416, 96, 475, 161, texture, 4);

	sprites->Add(141954, 1, 242, 41, 261, texture, 50);
	sprites->Add(141955, 60, 221, 103, 261, texture, 29);
	sprites->Add(141956, 123, 206, 171, 261, texture, 14);
	sprites->Add(141957, 187, 191, 250, 261, texture, -1);
	sprites->Add(141958, 259, 188, 324, 261, texture, -4);
	sprites->Add(141959, 344, 182, 410, 261, texture, -10);
	sprites->Add(141960, 426, 179, 494, 261, texture, -13);
	sprites->Add(141961, 504, 177, 575, 261, texture, -15);
	sprites->Add(141962, 588, 175, 661, 261, texture, -17);
	sprites->Add(141963, 672, 174, 747, 261, texture, -18);
	sprites->Add(141964, 776, 175, 849, 261, texture, -17);
	sprites->Add(141965, 8, 317, 78, 375, texture, 11);
	sprites->Add(141966, 88, 311, 152, 375, texture, 5);
	sprites->Add(141967, 160, 303, 227, 375, texture, -3);
	sprites->Add(141968, 240, 303, 311, 375, texture, -3);
	sprites->Add(141969, 320, 291, 389, 375, texture, -15);
	sprites->Add(141970, 400, 292, 469, 375, texture, -14);
	sprites->Add(141971, 480, 293, 550, 375, texture, -13);
	sprites->Add(141972, 560, 293, 630, 375, texture, -13);
	sprites->Add(141973, 644, 292, 708, 376, texture, -15);
	sprites->Add(141974, 716, 294, 780, 376, texture, -13);
	sprites->Add(141975, 788, 315, 859, 376, texture, 8);

	sprites->Add(141977, 14, 392, 38, 439, texture, 0);
	sprites->Add(141978, 46, 386, 68, 439, texture, -6);
	sprites->Add(141979, 78, 392, 102, 439, texture, 0);
	sprites->Add(141980, 110, 389, 137, 439, texture, -3);
	sprites->Add(141981, 150, 393, 185, 439, texture, 1);

	sprites->Add(141983, 198, 425, 226, 439, texture);
	sprites->Add(141984, 238, 423, 262, 439, texture);
	sprites->Add(141985, 270, 424, 296, 439, texture);
	sprites->Add(141987, 310, 426, 324, 439, texture);
	sprites->Add(141988, 334, 425, 355, 439, texture);
	sprites->Add(141989, 382, 418, 397, 439, texture);
	sprites->Add(141991, 8, 485, 83, 535, texture, 31);
	sprites->Add(141992, 96, 487, 175, 535, texture, 33);
	sprites->Add(141993, 184, 493, 277, 535, texture, 39);
	sprites->Add(141994, 296, 494, 386, 535, texture, 40);
	sprites->Add(141995, 400, 506, 477, 535, texture, 52);
	sprites->Add(141996, 488, 504, 561, 535, texture, 50);
	sprites->Add(141997, 568, 492, 632, 535, texture, 38);
	sprites->Add(141998, 645, 484, 709, 535, texture, 30);


}

void Jafar::LoadResource()
{
	if (!isLoadedSprite)
		LoadSprite();
	
	Animation * ani = new Animation(90, 0);
	ani->Add(141937, 200);
	ani->Add(141938);
	ani->Add(141939);
	ani->Add(141940);
	ani->Add(141941);
	ani->Add(141942);
	ani->Add(141943);
	ani->Add(141944);
	this->animations[JAFAR_ATTACK] = ani;
	
	ani = new Animation(90, 0);
	ani->Add(141946);
	ani->Add(141947);
	ani->Add(141948);
	ani->Add(141949);
	ani->Add(141950);
	ani->Add(141951);
	ani->Add(141952);
	this->animations[JAFAR_THROW_SNAKE] = ani;

	ani = new Animation(90, 11);
	ani->Add(141954);
	ani->Add(141955);
	ani->Add(141956);
	ani->Add(141957);
	ani->Add(141958);
	ani->Add(141959);
	ani->Add(141960);
	ani->Add(141961);
	ani->Add(141962);
	ani->Add(141963);
	ani->Add(141964);
	ani->Add(141965);
	ani->Add(141966);
	ani->Add(141967);
	ani->Add(141968);
	ani->Add(141969);
	ani->Add(141970);
	ani->Add(141971);
	ani->Add(141972);
	ani->Add(141973);
	ani->Add(141974);
	ani->Add(141975);
	this->animations[SNAKE_ATTACK] = ani;

	ani = new Animation(90, 0);
	ani->Add(141977);
	ani->Add(141978);
	ani->Add(141979);
	ani->Add(141980);
	ani->Add(141981);
	this->animations[FIRER] = ani;
}

Jafar::Jafar()
{
	health = 16;
	x = 400;
	y = 280;
	width = 20;
	height = 22;
	vx = 0;
	vy = 0;
	isSnake = false;
	isDeath = false;
	type = oType::JAFAR;
	nx = 1;
	LoadResource();
}


Jafar::~Jafar()
{
}

void Jafar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = (float)x;
	top = (float)y + 10;
	right = left + (float)width - 10;
	bottom = top + (float)height;
}

void Jafar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	dtime += dt;
	for (int i = 0; i < weapon.size(); i++)
	{
		if (weapon[i]->GetType() == oType::MAGIC)
		{
			Magic * m = (Magic*)weapon[i];
			m->Goal.x = aladdinPoint.x;
			m->Goal.y = aladdinPoint.y;
			m->SetNx(nx);
			if (m->isDeath)
			{
				weapon.erase(weapon.begin() + i);
				delete m;
				continue;
			}
		}
		else
		{
			Flame * f = (Flame*)weapon[i];
			if (f->isDeath)
			{
				weapon.erase(weapon.begin() + i);
				delete f;
				continue;
			}
		}

		weapon[i]->Update(dt);
	}
	if (health <= 0)
	{
		isDeath = true;
		for (int i = 0; i < weapon.size(); i++)
		{
			GameObject * f = weapon[i];
			weapon.erase(weapon.begin() + i);
			delete f;
		}
	}
	if (health < 15)
		//Máu d??i 15 thì bi?n thành snake
	{
		currentState = SNAKE_ATTACK;
		isSnake = true;
	}
	if (!isSnake)
	{
		//Tr?ng thái bình th??ng
		if (animations[JAFAR_ATTACK]->GetCurrentFrame() > 0 && dtime > 300)
		{
			GameObject * w = new Magic(x, y, width, height);
	 		weapon.push_back(w);
			dtime = 0;
		}

		Sound::GetInstance()->Play(eSound::sound_JafarLaugh);
	}
	else
	{
		if (animations[SNAKE_ATTACK]->GetCurrentFrame() == 16 && dtime > 200)
		{
			GameObject * w = new Flame(this->x, this->y, 100, 50, this->nx);
			weapon.push_back(w);
			dtime = 0;
			Sound::GetInstance()->Play(eSound::sound_JafarSnake);
		}
	}
	
}

void Jafar::Render(int flip)
{
	// N?u Jafar không ph?i là r?n 
	if (!isSnake)
	{
		animations[JAFAR_ATTACK]->Render(x- Camera::GetInstance()->GetXCam(), y-Camera::GetInstance()->GetYCam(), 255, nx);
	}
	// Khi Jafar chuy?n sang tr?ng thái snake
	else
	{
		animations[SNAKE_ATTACK]->Render(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam(), 255, nx);
		animations[FIRER]->Render(x - Camera::GetInstance()->GetXCam(), y + 20 - Camera::GetInstance()->GetYCam(), 255, nx);
		animations[FIRER]->Render(x + nx*50 - Camera::GetInstance()->GetXCam(), y + 20 - Camera::GetInstance()->GetYCam(), 255, nx);
	}
	for (int i = 0; i < weapon.size(); i++)
	{
		weapon[i]->Render();
	}
}

void Jafar::SetCurrentState(int currentState)
{

}