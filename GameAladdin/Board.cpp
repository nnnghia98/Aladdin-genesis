#include "Board.h"
#include "Sound.h"
Board * Board::instance = NULL;

Board::Board()
{
	health = 5;
	heart = 10;
	score = 1230;
	apple = 22;
	redjewel = 5;
	for (int i = 0; i < 6; i++)
		arrScore[i] = 0;
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	Characters::GetInstance();
	sprites->Add(-41, 17, 3007, 137, 3039, texture);
	sprites->Add(-42, 147, 3007, 267, 3039, texture);
	sprites->Add(-43, 277, 3007, 396, 3039, texture);
	sprites->Add(-44, 406, 3007, 525, 3039, texture);
	sprites->Add(-46, 17, 3054, 129, 3086, texture);
	sprites->Add(-47, 139, 3054, 251, 3086, texture);
	sprites->Add(-48, 261, 3054, 372, 3086, texture);
	sprites->Add(-49, 382, 3054, 493, 3086, texture);
	sprites->Add(-51, 17, 3101, 121, 3133, texture);
	sprites->Add(-52, 131, 3101, 235, 3133, texture);
	sprites->Add(-53, 245, 3101, 348, 3133, texture);
	sprites->Add(-54, 358, 3101, 461, 3133, texture);
	sprites->Add(-56, 17, 3148, 113, 3180, texture);
	sprites->Add(-57, 123, 3148, 219, 3180, texture);
	sprites->Add(-58, 229, 3148, 324, 3180, texture);
	sprites->Add(-59, 334, 3148, 429, 3180, texture);
	sprites->Add(-61, 17, 3195, 105, 3227, texture);
	sprites->Add(-62, 116, 3195, 204, 3227, texture);
	sprites->Add(-63, 214, 3195, 301, 3227, texture);
	sprites->Add(-64, 311, 3195, 398, 3227, texture);
	sprites->Add(-66, 17, 3242, 97, 3274, texture);
	sprites->Add(-67, 107, 3242, 187, 3274, texture);
	sprites->Add(-68, 197, 3242, 276, 3274, texture);
	sprites->Add(-69, 286, 3242, 365, 3274, texture);
	sprites->Add(-71, 17, 3289, 88, 3321, texture);
	sprites->Add(-72, 98, 3289, 169, 3321, texture);
	sprites->Add(-73, 179, 3289, 251, 3321, texture);
	sprites->Add(-74, 261, 3289, 333, 3321, texture);
	sprites->Add(-76, 17, 3336, 80, 3365, texture);
	sprites->Add(-77, 90, 3336, 153, 3365, texture);
	sprites->Add(-78, 163, 3336, 227, 3365, texture);
	sprites->Add(-79, 237, 3335, 301, 3365, texture);
	sprites->Add(-81, 17, 3380, 65, 3404, texture);
	sprites->Add(HEAD_ALADDIN, 13, 3568, 35, 3593, texture);
	sprites->Add(APPLE_BOARD, 17, 3437, 28, 3449, texture);
	sprites->Add(REDJEWEL_BOARD, 49, 3435, 66, 3451, texture);

	Animation * ani = new Animation(120,0);
	ani->Add(-41);
	ani->Add(-42);
	ani->Add(-43);
	ani->Add(-44);
	animations->Add(ANI_HEALTH_9, ani);
	ani = new Animation(120, 0);
	ani->Add(-46);
	ani->Add(-47);
	ani->Add(-48);
	ani->Add(-49);
	animations->Add(ANI_HEALTH_8, ani);

	ani = new Animation(120, 0);
	ani->Add(-51);
	ani->Add(-52);
	ani->Add(-53);
	ani->Add(-54);
	animations->Add(ANI_HEALTH_7, ani);
	ani = new Animation(120, 0);
	ani->Add(-56);
	ani->Add(-57);
	ani->Add(-58);
	ani->Add(-59);
	animations->Add(ANI_HEALTH_6, ani);

	ani = new Animation(120, 0);
	ani->Add(-61);
	ani->Add(-62);
	ani->Add(-63);
	ani->Add(-64);
	animations->Add(ANI_HEALTH_5, ani);

	ani = new Animation(120, 0);
	ani->Add(-66);
	ani->Add(-67);
	ani->Add(-68);
	ani->Add(-69);
	animations->Add(ANI_HEALTH_4, ani);

	ani = new Animation(120, 0);
	ani->Add(-71);
	ani->Add(-72);
	ani->Add(-73);
	ani->Add(-74);
	animations->Add(ANI_HEALTH_3, ani);

	ani = new Animation(120, 0);
	ani->Add(-76);
	ani->Add(-77);
	ani->Add(-78);
	ani->Add(-79);
	animations->Add(ANI_HEALTH_2, ani);

	ani = new Animation(120, 0);
	ani->Add(-81);
	animations->Add(ANI_HEALTH_1, ani);
}

void Board::ProcessScore()
{
	int i = 5;
	int tmp = score;
	while (tmp > 0)
	{
		if (i < 0)
			break;
		arrScore[i] = tmp % 10;
		tmp /= 10;
		i--;
	}
}

void Board::RenderNumber(float x, float y, int num)
{
	int arr[5];
	for (int i = 0; i < 5; i++)
		arr[i] = -1;
	int i = 4;
	while (num > 0)
	{
		if (i < 0)
			break;
		arr[i] = num % 10;
		num /= 10;
		i--;
	}
	for (int i = 0; i < 5; i++)
	{
		if (arr[i] == -1)
			continue;
		switch (arr[i])
		{
		case 0:
			Sprites::GetInstance()->Get(NUM_0)->Draw(x, y);
			break;
		case 1:
			Sprites::GetInstance()->Get(NUM_1)->Draw(x, y);
			break;
		case 2:
			Sprites::GetInstance()->Get(NUM_2)->Draw(x, y);
			break;
		case 3:
			Sprites::GetInstance()->Get(NUM_3)->Draw(x, y);
			break;
		case 4:
			Sprites::GetInstance()->Get(NUM_4)->Draw(x, y);
			break;
		case 5:
			Sprites::GetInstance()->Get(NUM_5)->Draw(x, y);
			break;
		case 6:
			Sprites::GetInstance()->Get(NUM_6)->Draw(x, y);
			break;
		case 7:
			Sprites::GetInstance()->Get(NUM_7)->Draw(x, y);
			break;
		case 8:
			Sprites::GetInstance()->Get(NUM_8)->Draw(x, y);
			break;
		case 9:
			Sprites::GetInstance()->Get(NUM_9)->Draw(x, y);
			break;
		}
		x += 8;
	}
}

Board::~Board()
{
}

void Board::Update(DWORD dt, int health, int heart, int score, int redjewel, int apple)
{
	this->health = health;
	this->heart = heart;
	this->redjewel = redjewel;
	this->apple = apple;
	if (this->score < score)
	{
		this->score += (score - this->score+SCORE_RENDER_SPEED_LEVEL) / SCORE_RENDER_SPEED_LEVEL;

		Sound::GetInstance()->Play(eSound::sound_BonesTinkle);
	}
	if (this->score > score)
		this->score = score;
}

void Board::Render()
{
	// render health
	if (health > 9)
		health = 9;
	if (health <= 0)
		health = 1;
	switch (health)
	{
	case 1:
		Animations::GetInstance()->Get(ANI_HEALTH_1)->Render(20, 20);
		break;
	case 2:
		Animations::GetInstance()->Get(ANI_HEALTH_2)->Render(20, 20);
		break;
	case 3:
		Animations::GetInstance()->Get(ANI_HEALTH_3)->Render(20, 20);
		break;
	case 4:
		Animations::GetInstance()->Get(ANI_HEALTH_4)->Render(20, 20);
		break;
	case 5:
		Animations::GetInstance()->Get(ANI_HEALTH_5)->Render(20, 20);
		break;
	case 6:
		Animations::GetInstance()->Get(ANI_HEALTH_6)->Render(20, 20);
		break;
	case 7:
		Animations::GetInstance()->Get(ANI_HEALTH_7)->Render(20, 20);
		break;
	case 8:
		Animations::GetInstance()->Get(ANI_HEALTH_8)->Render(20, 20);
		break;
	case 9:
		Animations::GetInstance()->Get(ANI_HEALTH_9)->Render(20, 20);
		break;
	}
	
	// render score
	ProcessScore();
	float x = 230;
	float y = 30;
	for (int i = 0; i < 6; i++)
	{
		switch (arrScore[i])
		{
		case 0:
			Sprites::GetInstance()->Get(NUM_0)->Draw(x, y);
			break;
		case 1:
			Sprites::GetInstance()->Get(NUM_1)->Draw(x, y);
			break;
		case 2:
			Sprites::GetInstance()->Get(NUM_2)->Draw(x, y);
			break;
		case 3:
			Sprites::GetInstance()->Get(NUM_3)->Draw(x, y);
			break;
		case 4:
			Sprites::GetInstance()->Get(NUM_4)->Draw(x, y);
			break;
		case 5:
			Sprites::GetInstance()->Get(NUM_5)->Draw(x, y);
			break;
		case 6:
			Sprites::GetInstance()->Get(NUM_6)->Draw(x, y);
			break;
		case 7:
			Sprites::GetInstance()->Get(NUM_7)->Draw(x, y);
			break;
		case 8:
			Sprites::GetInstance()->Get(NUM_8)->Draw(x, y);
			break;
		case 9:
			Sprites::GetInstance()->Get(NUM_9)->Draw(x, y);
			break;
		}
		x += 8;
	}

	// Render heart
	Sprites::GetInstance()->Get(HEAD_ALADDIN)->Draw(20, 185);
	RenderNumber(43, 200, heart);
	// render redjewel
	if (redjewel > 0) 
	{
		Sprites::GetInstance()->Get(REDJEWEL_BOARD)->Draw(225, 195);
		RenderNumber(245, 200, redjewel);
	}
	// render apple
	Sprites::GetInstance()->Get(APPLE_BOARD)->Draw(260, 195);
	if (apple == 0)
		Sprites::GetInstance()->Get(NUM_0)->Draw(272, 200);
	else
		RenderNumber(272, 200, apple);
}

Board * Board::GetInstance()
{
	if (instance == NULL)
		instance = new Board();
	return instance;
}