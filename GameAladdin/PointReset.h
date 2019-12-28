#ifndef __PointReset__
#define __PointReSet__

#include "Aladdin.h"
class PointReset // đây là class lưu lại trạng thái game khi ăn được restart point
{
private:
	unordered_map<int, int> stateOfObject;
	Aladdin * aladdin;
public:
	PointReset();
	void SetPointReset(vector<LPGAMEOBJECT> &coObjects, Aladdin * aladdin);
	void ResetState(vector<LPGAMEOBJECT> &coObjects, Aladdin * aladdin);
	~PointReset();
};
#endif // !__PointReset__