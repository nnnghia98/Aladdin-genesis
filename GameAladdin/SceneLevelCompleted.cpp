#include "SceneLevelCompleted.h"
#include "Textures.h"
#include "Animations.h"
#include "Sound.h"
void SceneLevelCompleted::KeyState(BYTE * state)
{
}

void SceneLevelCompleted::OnKeyDown(int KeyCode)
{
}

void SceneLevelCompleted::OnKeyUp(int KeyCode)
{
}

void SceneLevelCompleted::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	if (Animations::GetInstance()->Get(80102) != nullptr)
		return;
	sprites->Add(80101, 513, 2851, 745, 2997, texture);
	sprites->Add(80102, 8, 2901, 43, 2958, texture, 4);
	sprites->Add(80103, 53, 2898, 89, 2958, texture, 1);
	sprites->Add(80104, 99, 2895, 137, 2958, texture, -2);
	sprites->Add(80105, 147, 2899, 195, 2958, texture, 2);
	sprites->Add(80106, 205, 2897, 245, 2958, texture, 0);
	sprites->Add(80107, 255, 2897, 292, 2958, texture, 0);
	sprites->Add(80108, 302, 2899, 339, 2958, texture, 2);
	sprites->Add(80109, 349, 2896, 393, 2958, texture, -1);
	sprites->Add(80110, 403, 2899, 452, 2958, texture, 2);
	Animation * ani = new Animation(90, 0);
	ani->Add(80102);
	ani->Add(80103);
	ani->Add(80104);
	ani->Add(80105);
	ani->Add(80106);
	ani->Add(80107);
	ani->Add(80108);
	ani->Add(80109);
	ani->Add(80110);
	Animations::GetInstance()->Add(80102, ani);
	Sound::GetInstance()->Play(eSound::sound_LevelComplete);
}

void SceneLevelCompleted::Update(DWORD dt)
{
	dTime += dt;
	x += 2;
	if (dTime > 3000)
		SceneManager::GetInstance()->SetScene(SceneManager::GetInstance()->sceneGame);
}

void SceneLevelCompleted::Render()
{
	Sprites::GetInstance()->Get(80101)->Draw(30, 0);
	Animations::GetInstance()->Get(80102)->Render(x, y);
}

SceneLevelCompleted::SceneLevelCompleted()
{
	LoadResources();
	dTime = 0;
	x = 0;
	y = 140;	
}


SceneLevelCompleted::~SceneLevelCompleted()
{
}
