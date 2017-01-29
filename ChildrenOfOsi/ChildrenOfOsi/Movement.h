#pragma once
#include "stdafx.h"
#include "common.h"
#include "QuadTree.h"
#include "Task.h"

class Movement {
public:
	Movement(QuadTree* QT);
	~Movement();
	//void playerAction(string task_name, WorldObj* player);
	//static void initTree(WorldObj* screen);
	int move_up(WorldObj* obj);
	int move_down(WorldObj* obj);
	int move_left(WorldObj* obj);
	int move_right(WorldObj* obj);
	//void init_task_map();

private:

	QuadTree* tree;
	bool collision(WorldObj* recA, WorldObj* recB);
	bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }
	//hold obj to check with. init before each move funcs call
	std::vector<WorldObj*> objVec;
};
