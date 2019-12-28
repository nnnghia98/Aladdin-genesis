#include "SceneIntro.h"
#include "SceneManager.h"
#include "Animations.h"
#include "Textures.h"
#include "Sound.h"

void SceneIntro::KeyState(BYTE * state)
{
}

void SceneIntro::OnKeyDown(int KeyCode)
{
}

void SceneIntro::OnKeyUp(int KeyCode)
{
}

void SceneIntro::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	if (Sprites::GetInstance()->Get(80202) != nullptr)
		return;
	sprites->Add(80202, 9, 12, 252, 102, texture);
	Sound::GetInstance()->StopAll();
	Sound::GetInstance()->Play(eSound::sound_Story);

}

void SceneIntro::Update(DWORD dt)
{
	dTime += dt;
	if (a < 10)
		SceneManager::GetInstance()->SetScene(SceneManager::GetInstance()->sceneGame);

	if (a >= 100)
		flag = -1;
	a += 1*flag;
}

void SceneIntro::Render()
{
	Sprites::GetInstance()->Get(80202)->Draw(10, 40, a);
}

SceneIntro::SceneIntro()
{
	dTime = 0;
	LoadResources();
	a = 10;
	flag = 1;
}


SceneIntro::~SceneIntro()
{
}
