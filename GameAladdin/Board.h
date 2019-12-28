#ifndef __BOARD__
#define __BOARD__

#include "Characters.h"
#include "Animations.h"
#define ANI_HEALTH_9 -60
#define ANI_HEALTH_8 -61
#define ANI_HEALTH_7 -62
#define ANI_HEALTH_6 -63
#define ANI_HEALTH_5 -64
#define ANI_HEALTH_4 -65
#define ANI_HEALTH_3 -66
#define ANI_HEALTH_2 -67
#define ANI_HEALTH_1 -68
#define HEAD_ALADDIN -83
#define APPLE_BOARD -84
#define REDJEWEL_BOARD -85

#define SCORE_RENDER_SPEED_LEVEL 10
class Board
{
private:
	static Board * instance;

	int health;
	int heart;
	int score;
	int redjewel;
	int apple;
	int arrScore[6];
	Board();
	void ProcessScore();
	void RenderNumber(float x, float y, int num);
public:

	~Board();
	void Update(DWORD dt, int health, int heart, int score, int redjewel, int apple);
	void Render();
	static Board * GetInstance();
};

#endif // !__BOARD__