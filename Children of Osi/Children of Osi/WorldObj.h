#pragma once
#include <string>
#include "Vector2f.h"

class WorldObj
{
public:
	WorldObj();
	WorldObj(float x,float y, bool col);
	~WorldObj();
	void setLoc(Vector2f l);
	Vector2f getLoc();
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	void shiftX(float dist);
	void shiftY(float dist);
	void setRot(Vector2f r);
	Vector2f getRot();
	void setCollision(bool c);
	bool getCollision();
	//void setName(string n);
	//string getName();
private:
	Vector2f loc;
	Vector2f rotation;
	bool collision;
	//string name;
};


