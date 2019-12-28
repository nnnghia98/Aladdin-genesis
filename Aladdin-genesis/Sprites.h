#ifndef __SPRITE__
#define __SPRITE__
#include <d3dx9.h>
#include <unordered_map>
#include "Game.h"

using namespace std;

class Sprite
{
	int id;				

	int left;
	int top;
	int right;
	int bottom;

	int balance;
	int balanceX;

	LPDIRECT3DTEXTURE9 texture;
public:
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int balance = 0, int balanceX = 0);
	void Draw(float x, float y, int alpha = 255, int flip = 1, int dif = 37);
	void SetSprite(int left, int top, int right, int bottom); 
	void SetTexture(LPDIRECT3DTEXTURE9 texture) { this->texture = texture; }
	Sprite() {};
};

class Sprites
{
	static Sprites * __instance;

	unordered_map<int, Sprite*> sprites;

public:
	void Add(int id,	int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int blance = 0, int balanceX = 0);
	Sprite* Get(int id);
	Sprite* &operator[](int id) { return sprites[id]; }

	static Sprites * GetInstance();

	~Sprites();
};
#endif


