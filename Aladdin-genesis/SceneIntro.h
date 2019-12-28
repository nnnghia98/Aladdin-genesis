#ifndef __SCENEINTRO__
#define __SCENEINTRO__

#include "Scene.h"

class SceneIntro : public Scene
{
private:
	DWORD dTime;
	int a;
	int flag;
public:

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();

	SceneIntro();
	~SceneIntro();
};

#endif // !__SCENELEVELCOMPLETED__