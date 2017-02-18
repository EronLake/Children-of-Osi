#include "stdafx.h"
#include "Player.h"



Player::Player()
{
}

Player::Player(int name, float x, float y, bool col):Hero(name,x,y,col)
{
}


Player::~Player()
{
}

void Player::setTalkDist(float dist)
{
	talk.setX((*this).getX()-dist);
	talk.setY((*this).getY()-dist);
	talk.setWidth((*this).getWidth()+(2*dist));
	talk.setHeight((*this).getHeight()+(2*dist));
}
