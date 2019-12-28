#ifndef __SCENELEVELCOMPLETED__
#define __SCENELEVELCOMPLETED__

#include "Scene.h"

class SceneLevelCompleted: public Scene
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

	SceneLevelCompleted();
	~SceneLevelCompleted();
};

#endif // !__SCENELEVELCOMPLETED__