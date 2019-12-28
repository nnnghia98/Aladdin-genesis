#include "SceneDealth.h"

#include "Textures.h"
#include "Animations.h"
#include "Characters.h"

void SceneDealth::KeyState(BYTE * state)
{
}

void SceneDealth::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_C)
		SceneManager::GetInstance()->SetScene(SceneManager::GetInstance()->sceneGame);
}

void SceneDealth::OnKeyUp(int KeyCode)
{
}

void SceneDealth::LoadResources()
{
	Characters::GetInstance();
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	if (Animations::GetInstance()->Get(80112) != nullptr)
		return;
	sprites->Add(80112, 8, 2588, 45, 2639, texture, 10);
	sprites->Add(80113, 55, 2582, 92, 2639, texture, 4);
	sprites->Add(80114, 102, 2584, 145, 2639, texture, 6);
	sprites->Add(80115, 155, 2586, 216, 2639, texture, 8);
	sprites->Add(80116, 226, 2588, 287, 2639, texture, 10);
	sprites->Add(80117, 297, 2578, 361, 2639, texture, 0);
	sprites->Add(80118, 371, 2567, 441, 2639, texture, -11);
	sprites->Add(80119, 451, 2556, 527, 2639, texture, -22);
	sprites->Add(80120, 537, 2553, 614, 2639, texture, -25);
	sprites->Add(80122, 8, 2657, 85, 2742, texture, -24);
	sprites->Add(80123, 95, 2657, 170, 2742, texture, -24);
	sprites->Add(80124, 180, 2657, 255, 2742, texture, -24);
	sprites->Add(80125, 265, 2659, 333, 2742, texture, -22);
	sprites->Add(80126, 343, 2661, 409, 2742, texture, -20);
	sprites->Add(80127, 419, 2668, 485, 2742, texture, -13);
	sprites->Add(80129, 84, 2757, 150, 2831, texture, -13);
	sprites->Add(80130, 160, 2757, 226, 2831, texture, -13);


	Animation * ani = new Animation(90, 0);
	ani->Add(80112);
	ani->Add(80113);
	ani->Add(80114);
	ani->Add(80115);
	ani->Add(80116);
	ani->Add(80117);
	ani->Add(80118);
	ani->Add(80119);
	ani->Add(80120);
	ani->Add(80122);
	ani->Add(80123);
	ani->Add(80124);
	ani->Add(80125);
	ani->Add(80126);
	ani->Add(80127);
	ani->Add(80129);
	ani->Add(80130, 10000);

	Animations::GetInstance()->Add(80112, ani);
}

void SceneDealth::Update(DWORD dt)
{
	
}

void SceneDealth::Render()
{
	Animations::GetInstance()->Get(80112)->Render(120, 80);
	Sprites::GetInstance()->Get(CHAR_P)->Draw(60, 150);
	Sprites::GetInstance()->Get(CHAR_R)->Draw(72, 150);
	Sprites::GetInstance()->Get(CHAR_E)->Draw(84, 150);
	Sprites::GetInstance()->Get(CHAR_S)->Draw(96, 150);
	Sprites::GetInstance()->Get(CHAR_S)->Draw(108, 150);
	Sprites::GetInstance()->Get(CHAR_C)->Draw(132, 150);
	Sprites::GetInstance()->Get(CHAR_T)->Draw(156, 150);
	Sprites::GetInstance()->Get(CHAR_O)->Draw(168, 150);
	Sprites::GetInstance()->Get(CHAR_N)->Draw(192, 150);
	Sprites::GetInstance()->Get(CHAR_E)->Draw(204, 150);
	Sprites::GetInstance()->Get(CHAR_W)->Draw(216, 150);
	Sprites::GetInstance()->Get(CHAR_G)->Draw(240, 150);
	Sprites::GetInstance()->Get(CHAR_A)->Draw(252, 150);
	Sprites::GetInstance()->Get(CHAR_M)->Draw(264, 150);
	Sprites::GetInstance()->Get(CHAR_E)->Draw(278, 150);
}

SceneDealth::SceneDealth()
{
	LoadResources();
	dTime = 0;
}


SceneDealth::~SceneDealth()
{
}
