#ifndef _ALADDIN_
#define _ALADDIN_
#include "GameObject.h"

#define ALADDIN_WALK_SPEED 0.16f//0.12f
#define ALADDIN_GRAVITY 0.0016f
#define ALADIN_JUMP_SPEED 0.53f
#define ALADIN_STOP_SPEED 0.03f
#define ALADDIN_CLIMB_SPEED 0.11f

#define ALADDIN_IDLE1 1 // nhìn qua lại
#define ALADDIN_IDLE2 2 // ném táo 1
#define ALADDIN_IDLE3 3 // ném táo 2
#define ALADDIN_IDLE_LOOK_UP 4 // nhìn lên
//#define ALADDIN_IDLE_LOOK_DOWN 6 // nhìn xuống
#define ALADDIN_IDLE_SIT 5 // ngồi xuống

#define ALADDIN_RUNNING1 6 // Chạy
#define ALADDIN_RUNNING2 7 // Chạy -> dừng lại

#define ALADDIN_PUSHING 8

#define ALADDIN_JUMPING 9
#define ALADDIN_JUMPING_FOWARD 10
// #define ALADDIN_FALLING 13

#define ALADDIN_STAYING_ATTACKING 11
#define ALADDIN_SITTING_ATTACKING 12
#define ALADDIN_STAYING_COMBO_ATTACKING 13
#define ALADDIN_RUNING_ATTACKING 14
#define ALADDIN_JUMPING_ATTACKING 15

#define ALADDIN_STAYING_ATTACKING_BY_APPLE 16
#define ALADDIN_SITTING_ATACKING_BY_APPLE 17
#define ALADDIN_RUNNING_ATTACKING_BY_APPLE 18
#define ALADDIN_JUMPING_ATTACKING_BY_APPLE 19

#define ALADDIN_CLIMBING_ATTACKING 25
#define ALADDIN_CLIMBING_ATTACKING_BY_APPLE 26

#define ALADDIN_CLIMBING 20
#define ALADDIN_FALLING 21 // nhảy ra khỏi dây

#define ALADDIN_DAMAGE 22
#define ALADDIN_DEATH 23
#define ALADDIN_VICTORY 24

#define ALADDIN_GROUP_STATE_IDLE 100
#define ALADDIN_GROUP_STATE_ATTACKING 101
#define ALADDIN_GROUP_STATE_JUMPPING 102
#define ALADDIN_GROUP_STATE_RUNNING 103
#define ALADDIN_GROUP_STATE_CLIMBING 104
#define ALADDIN_GROUP_STATE_END 105 // Trạng thái không bị tấn công


#include "Brick.h"
#include "Rope.h"
#include "MovingBrick.h"
#include "Apple.h"
#include "AppleOfAladdin.h"
#include "RedJewel.h"
#include "Genie.h"
#include "Heart.h"
#include "RestartPoint.h"
#include "EnemyFat.h"
#include "EnemyThin.h"
#include "EnemyBat.h"
#include "EnemySkeleton.h"

class Aladdin: public GameObject
{
private:
	bool isCollisWithBrick;
	int ny;
	DWORD stime; // Thời gian để xét các state

	float dxt; // quảng đường dich chuyển ước tính
	//int groupState; // Nhóm state: là nhóm những state để xét chuyển trạng thái
	
	// Các biến của Rope đang va chạm
	float ropeX;
	float ropeY;
	int ropeWidth;
	int ropeHeight;

	int applesCount; // số táo hiện có của aladdin
	int redJewelCount; // số redjewel hiện tại
	int score;
	int heart;
	vector<AppleOfAladdin*> apples; // danh sách apple được ném ra: để xét va chạm
	AppleOfAladdin * a;
	float gravity;
public:
	bool isCollsionWithRestartPoint;
	bool isAttacking, isJumping, isClimbing, isIdle, isRunning, isInjured, isSitting; 
	bool isCollisionWithWall;
	bool isCollisionWithNextLevelPoint;
	Aladdin();
	~Aladdin();
	DWORD GetTime() { return stime; }
	void SetGravity(float gravity) { this->gravity = gravity; };
	void SetTime(DWORD stime) { this->stime = stime; }

	void LoadResource();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
	void SetCurrentState(int currentState);
	Animation * GetAnimations(int state) { return animations[state]; };
	void CollisionWithBrick(vector<LPGAMEOBJECT>* coObject);
	void CollisionWithWall(vector<LPGAMEOBJECT>* coObject);
	void CollisionWithRope(vector<LPGAMEOBJECT>* coObject);
	void CollisionWithItem(vector<LPGAMEOBJECT>* coObject);
	void CollisionWithEnemy(vector<LPGAMEOBJECT>* coObject);
	int GetGroupState(int state);
	int GetCurrentGroupState();

	int GetScore() { return score; }
	void SetScore(int score) { this->score = score; }
	int GetApplesCount() { return applesCount; }
	void SetApplesCount(int apple) { this->applesCount = apple; }
	int GetRedJewelCount() { return redJewelCount; }
	void SetReJewelCount(int ReJewel) { this->redJewelCount = ReJewel; }
	int GetHealth() { return health; }
	int GetHeart() { return heart; }
	void SetHeart(int heart) { this->heart = heart; }
	bool isAttackBySword();
};
#endif // !_ALADDIN
