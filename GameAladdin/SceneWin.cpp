#include "SceneWin.h"
#include "Characters.h"
#include "Sound.h"

void SceneWin::KeyState(BYTE * state)
{
}

void SceneWin::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_C)
		SceneManager::GetInstance()->SetScene(SceneManager::GetInstance()->sceneGame);
}

void SceneWin::OnKeyUp(int KeyCode)
{
}

void SceneWin::LoadResources()
{
	Sound::GetInstance()->StopAll();
	Sound::GetInstance()->Play(eSound::sound_Story);
}

void SceneWin::Update(DWORD dt)
{
}

void SceneWin::Render()
{
	Characters::GetInstance();
	Sprites::GetInstance()->Get(CHAR_Y)->Draw(115, 50);
	Sprites::GetInstance()->Get(CHAR_O)->Draw(128, 50);
	Sprites::GetInstance()->Get(CHAR_U)->Draw(141, 50);
	Sprites::GetInstance()->Get(CHAR_W)->Draw(167, 50);
	Sprites::GetInstance()->Get(CHAR_I)->Draw(180, 50);
	Sprites::GetInstance()->Get(CHAR_N)->Draw(193, 50);

	Sprites::GetInstance()->Get(CHAR_P)->Draw(50, 80);
	Sprites::GetInstance()->Get(CHAR_R)->Draw(62, 80);
	Sprites::GetInstance()->Get(CHAR_E)->Draw(74, 80);
	Sprites::GetInstance()->Get(CHAR_S)->Draw(86, 80);
	Sprites::GetInstance()->Get(CHAR_S)->Draw(98, 80);
	Sprites::GetInstance()->Get(CHAR_C)->Draw(122, 80);
	Sprites::GetInstance()->Get(CHAR_T)->Draw(146, 80);
	Sprites::GetInstance()->Get(CHAR_O)->Draw(158, 80);
	Sprites::GetInstance()->Get(CHAR_N)->Draw(182, 80);
	Sprites::GetInstance()->Get(CHAR_E)->Draw(194, 80);
	Sprites::GetInstance()->Get(CHAR_W)->Draw(206, 80);
	Sprites::GetInstance()->Get(CHAR_G)->Draw(230, 80);
	Sprites::GetInstance()->Get(CHAR_A)->Draw(242, 80);
	Sprites::GetInstance()->Get(CHAR_M)->Draw(254, 80);
	Sprites::GetInstance()->Get(CHAR_E)->Draw(268, 80);

}

SceneWin::SceneWin()
{
	LoadResources();
}


SceneWin::~SceneWin()
{
}
