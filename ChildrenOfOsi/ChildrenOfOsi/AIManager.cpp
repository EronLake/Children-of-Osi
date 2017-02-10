#include "stdafx.h"
#include "PhysicsManager.h"
#include "AIManager.h"



AIManager::AIManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
	LOG("AIManager Object Constructed");
}

AIManager::AIManager(MessageLog * _mLog, TaskBuffer * _tBuffer, QuadTree * _physicsQuadTree)
	: Manager(_mLog, _tBuffer)
{
	LOG("AIManager W/QT Object Constructed");
	//init a movement obj 
	moveHelper = new Movement(_physicsQuadTree);

	//init mapping of tasks to functions
	task_map["Move_Up"] = &Movement::move_up;
	task_map["Move_Down"] = &Movement::move_down;
	task_map["Move_Left"] = &Movement::move_left;
	task_map["Move_Right"] = &Movement::move_right;
}


AIManager::~AIManager()
{
	LOG("AIManager Object Destroyed");
	delete(moveHelper);
}

void AIManager::register_manager()
{
	tBuffer->add_to_table("MOVE", this);
}

void AIManager::execute_task(Task* current_task)
{
	int result;
	if (current_task->objToUpdate == nullptr) {
		result = 1;
		LOG("Error: No player object");
	}
	else {
		auto it = task_map.find(current_task->name);
		if (it == task_map.end()) {
			result = 1;
			LOG("Error: Task '" << current_task->name << "' does not exist.");
		}
		else {
			result = (moveHelper->*(it->second))(current_task->objToUpdate);
		}
	}

	if (result == 0) {
		current_task->updateStatus("COMPLETED");
	}
	else {
		current_task->updateStatus("FAILED");
	}
	this->send_result(current_task);
}
