#include "Sprites.h"

Sprites * Sprites::__instance = NULL;

Sprites::~Sprites()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites.end();
	}
}

void Sprite::SetSprite(int left, int top, int right, int bottom)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int balance, int balanceX)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->balance = balance;
	this->balanceX = balanceX;
}

void Sprite::Draw(float x, float y, int alpha, int flip, int dif)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	D3DXMATRIX oldMatrixTransform; // Lấy tramsform ban đầu để set lại sau quá trình transform -> tác dụng: lật hình
	D3DXMATRIX newMatrixTransform;
	Game::GetInstance()->GetSpriteHandler()->GetTransform(&oldMatrixTransform);
	if (dif == 37) 
	{
		if (flip == -1) { // Thực hiện flip nếu hướng di chuyển nx = -1
			D3DXMatrixScaling(&newMatrixTransform, -1.0f, 1.0f, .0f);
			Game::GetInstance()->GetSpriteHandler()->SetTransform(&newMatrixTransform);
			x = -x - right + left + (right - left - dif);// -balanceX;// -37);
		}
		else
		{
			//x += balanceX;
		}
		D3DXVECTOR3 position(x, (y + balance), 0.0f);
		Game::GetInstance()->GetSpriteHandler()->Draw(texture, &rect, NULL, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}
	else
	{
		if (flip == 1) { // Thực hiện flip nếu hướng di chuyển nx = -1
			D3DXMatrixScaling(&newMatrixTransform, -1.0f, 1.0f, .0f);
			Game::GetInstance()->GetSpriteHandler()->SetTransform(&newMatrixTransform);
			x = -x - right + left;
		}
		else
			x -= (right- left - dif);
		D3DXVECTOR3 position(x, (y + balance), 0.0f);
		Game::GetInstance()->GetSpriteHandler()->Draw(texture, &rect, NULL, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}

	
	Game::GetInstance()->GetSpriteHandler()->SetTransform(&oldMatrixTransform);
}

void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int blance, int balanceX)
{
	Sprite* s = new Sprite(id, left, top, right, bottom, tex, blance, balanceX);
	sprites[id] = s;
}

Sprite * Sprites::Get(int id)
{
	return sprites[id];
}

Sprites * Sprites::GetInstance()
{
	if (__instance == NULL) __instance = new Sprites();
	return __instance;
}
