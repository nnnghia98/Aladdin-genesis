#ifndef __SCENEGAME_H__
#define __SCENEGAME_H__
#include "SceneManager.h"
#include "Scene.h"
#include "Map.h"
#include "Textures.h"
#include "Grid.h"
#include "Aladdin.h"
#include "Board.h"
#include "PointReset.h"
#include "Foreground.h"
#include "Jafar.h"
class SceneGame:public Scene
{
private: 
	Aladdin * aladdin;
	Map * map;
	Camera * camera;
	Grid * grid;	
	int idMap; // Level trong game, có 2 level tương ứng với 2 Map
	Textures * textures;
	int StateCurrent;
	PointReset * pointReset;

	DWORD EndTime;
	int count;

	int dyc;// biến dùng tạo hiệu ứng chuyển động cho cam

	vector<LPGAMEOBJECT> obj;
	vector<LPGAMEOBJECT> *mapObj;
	Foreground * foreground;
	ForegroundObject * foregroundx;
	ForegroundObject * foregroundxboss;
	int level;
public:
	bool isGameOver;
	void KeyState(BYTE *state); // Bắt các sự kiện phím để xử lý
	void OnKeyDown(int KeyCode); // 
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();

	void SetLevel(int level);

	SceneGame();
	~SceneGame();
};

#endif