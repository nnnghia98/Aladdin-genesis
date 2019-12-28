#ifndef __SCENEDEALTH__
#define __SCENEDEALTH__

#include "Scene.h"

class SceneDealth : public Scene
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

	SceneDealth();
	~SceneDealth();
};

#endif // !__SCENEL