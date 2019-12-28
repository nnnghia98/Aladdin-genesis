#ifndef __FOREGROUND__
#define __FOREGROUND__
#include "Game.h"
#include "ForegroundObject.h"
using namespace std;
class Foreground
{
public:
	vector<ForegroundObject *> list_foregroundObject;
	Foreground();
	~Foreground();
};

#endif // !__FOREGROUND__

