#pragma once
#include "stdafx.h"
#include "common.h"
#include "ChildrenOfOsi.h"
#include "DialogueController.h"
#include "GameWindow.h"
#include "RenderHelper.h"
#include "Containers.h"
#include "AIController.h"
#include "Village.h"



class Input
{
private:
	WorldObj* player;
	ChildrenOfOsi* gameplay_functions;
	RenderHelper* rHelper;
	TaskBuffer* tBuffer;
	vector<WorldObj*>* recVec;
	AIController* ai;
	pair<float, float> oldPoint;

	short W;
	short A;
	short S;
	short D;
	short Q;
	short E;
	short F;
	int count;
	int count2;

	bool prompted_quest = false;

	bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }

	//Map Editor Functions  
	void add_object();
	void edit_object();
	void edit_field(std::string collide_with, int body_number, float left, float right, float top, float bottom);
	void duplicate_object(std::string collide_with);
	void delete_object(std::string collide_with);
	double previous_x_mouse_pos = 0;
	void interactive_resize(std::string collide_with, double mouseX);

	//River/Mountain Point Tool
	void add_point_to_file();
	void skip_line();

public:
	Input(ChildrenOfOsi* _gameplay_functions, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec);
	Input(ChildrenOfOsi* _gameplay_functions, WorldObj * _player, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec);
	~Input();
	//Region* Desert;
	//Region* Ogun;
	//Region* Mountain;
	//Region* Jungle;
	//Region current_region;
	//Region next_region;

	void InputCheck();

};

