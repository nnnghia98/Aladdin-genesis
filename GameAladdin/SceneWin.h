#ifndef __SCENEWIN__
#define __SCENEWIN__

#include "Scene.h"

class SceneWin : public Scene
{
private:
	DWORD dTime;
	float x;
	float y;
public:

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();

	SceneWin();
	~SceneWin();
};

#endif