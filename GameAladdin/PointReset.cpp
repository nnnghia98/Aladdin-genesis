#include "PointReset.h"


PointReset::PointReset()
{
}

void PointReset::SetPointReset(vector<LPGAMEOBJECT> &coObjects, Aladdin * aladdin)
{
	for (int i = 0; i < coObjects.size(); i++)
	{
		stateOfObject[coObjects[i]->GetId()] = coObjects[i]->GetCurrentState();
	}
	this->aladdin = new Aladdin();
	float x;
	float y;
	aladdin->GetPosition(x, y);
	this->aladdin->SetPosition(x, y-3);
	this->aladdin->SetHealth(aladdin->GetHealth());
	this->aladdin->SetScore(aladdin->GetScore());
	this->aladdin->SetApplesCount(aladdin->GetApplesCount());
	this->aladdin->SetReJewelCount(aladdin->GetRedJewelCount());
}

void PointReset::ResetState(vector<LPGAMEOBJECT> &coObjects, Aladdin * aladdin)
{
	for (int i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->SetCurrentState(stateOfObject[coObjects[i]->GetId()]);
		switch (coObjects[i]->GetType())
		{
		case oType::ENEMYBAT:
			coObjects[i]->SetHealth(1);			
			break;
		case oType::ENEMYSKELETON:
			coObjects[i]->SetHealth(1);
			break;
		case oType::ENEMYFAT:
		case oType::ENEMYTHIN:
			coObjects[i]->SetHealth(2);
			break;
		}
	}
	aladdin->SetApplesCount(this->aladdin->GetApplesCount());
	aladdin->SetHealth(this->aladdin->GetHealth());
	aladdin->SetReJewelCount(this->aladdin->GetRedJewelCount());
	aladdin->SetScore(this->aladdin->GetScore());
	float x;
	float y;
	this->aladdin->GetPosition(x, y);
	aladdin->SetPosition(x, y);
}

PointReset::~PointReset()
{
}
