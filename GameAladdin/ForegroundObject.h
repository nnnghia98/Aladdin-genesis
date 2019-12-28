#ifndef __FOREGROUNDOBJECT__
#define __FOREGROUNDOBJECT__

#include "Sprites.h"
#include "Camera.h"
class ForegroundObject
{
public:
	float x; 
	float y;
	int width;
	int height;
	int  idSprite;
	void Render();
	void RenderWithEffect(float a, float b, float speed = 1.3);
	void RenderWithEffect(float speed = 1.3);

	ForegroundObject(int idSprite, float x, float y, int width = 0, int height = 0);
	~ForegroundObject();
};

#endif // !__FOREGROUNDOBJECT__