#pragma once
#include "LivingObj.h"
#include "Factions.h"

class NPC :
	public LivingObj
{
public:
	NPC();
	NPC(float x, float y, bool col);
	~NPC();
	void setFaction(int f);
	int getFaction();
	void setSpeed(float);
	float getSpeed();
private:
	int faction;
	float speed;
};

