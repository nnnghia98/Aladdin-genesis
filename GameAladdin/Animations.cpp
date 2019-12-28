#include "Animations.h"



void Animation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	Sprite* sprite = Sprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::Render(float x, float y, int alpha, int flip, int dif)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size())
				if (frameLoop != -1)
					currentFrame = frameLoop;
				else
					currentFrame--;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha, flip, dif);
}

void Animation::RenderReverse(float x, float y, int alpha, int flip)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
		flagReverse = 1;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			if (flagReverse > 0)
				currentFrame++;
			else
				currentFrame--;
			lastFrameTime = now;
			if (currentFrame == frames.size() || currentFrame == -1)
			{
				currentFrame -= flagReverse;
				flagReverse = -flagReverse;
			}	
		}

	}
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
		flagReverse = 1;
	}
	frames[currentFrame]->GetSprite()->Draw(x, y, alpha, flip);
}

void Animation::CustomRender(float x, float y, int alpha, int flip)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
		flagReverse = 1;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			if (flagReverse > 0)
				currentFrame++;
			else
				currentFrame--;
			lastFrameTime = now;
			if (currentFrame == frames.size() || currentFrame == -1)
			{
				currentFrame -= flagReverse;
				flagReverse = -flagReverse;
			}
		}

	}
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
		flagReverse = 1;
	}
	frames[frames.size() - currentFrame - 1]->GetSprite()->Draw(x, y, alpha, flip);
}

Animations * Animations::__instance = NULL;

Animations * Animations::GetInstance()
{
	if (__instance == NULL) __instance = new Animations();
	return __instance;
}

Animations::~Animations()
{
	if (__instance != NULL)
	delete __instance;
}

void Animations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION Animations::Get(int id)
{
	return animations[id];
}

Animation::~Animation() 
{
	for (auto p : frames)
	{
		delete p;
	}
	frames.clear();
}