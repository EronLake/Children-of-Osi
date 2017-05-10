#include "stdafx.h"
#include "PhysicsManager.h"
#include "CheckClass.h"


PhysicsManager::PhysicsManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{

	LOG("PhysicsManager Object Constructed");
}

PhysicsManager::PhysicsManager(MessageLog * _mLog, TaskBuffer * _tBuffer, QuadTree * _physicsQuadTree, UniformGrid* _uniformGrid, RiverObj* _rivObj)
	: Manager(_mLog, _tBuffer)
{
	LOG("PhysicsManager W/QT Object Constructed");
	//init a movement obj 
	moveHelper = new Movement(_physicsQuadTree, _uniformGrid, _rivObj);
	moveHelper->manager = this;
	

	//init mapping of tasks to functions
	task_map["Move_Up"] = &Movement::move_up;
	task_map["Move_Up_Left"] = &Movement::move_up_left;
	task_map["Move_Up_Right"] = &Movement::move_up_right;
	task_map["Move_Down"] = &Movement::move_down;
	task_map["Move_Down_Left"] = &Movement::move_down_left;
	task_map["Move_Down_Right"] = &Movement::move_down_right;
	task_map["Move_Left"] = &Movement::move_left;
	task_map["Move_Right"] = &Movement::move_right;
	task_map["Talk"] = &Movement::talk;
	task_map["Attack"] = &Movement::attack;
}


PhysicsManager::~PhysicsManager()
{
	LOG("PhysicsManager Object Destroyed");
	delete(moveHelper);
}

void PhysicsManager::register_manager()
{
	tBuffer->add_to_table("MOVE", this);
	tBuffer->add_to_table("INTERACT", this);
	tBuffer->add_to_table("COMBAT", this);

}

void PhysicsManager::execute_task(Task* current_task)
{
	int result;
	NPC* obj;
	if (current_task->objToUpdate->getType() >= WorldObj::TYPE_SOLDIER) {
		if (!(obj = CheckClass::isNPC(current_task->objToUpdate))) {
			result = 1;
			LOG("Error: No movable object");
		}
		else {
			moveHelper->moveSpeed = obj->getSpeed();
			moveHelper->diagXSpeed = obj->getDiagXSpeed();
			moveHelper->diagYSpeed = obj->getDiagYSpeed();

			auto it = task_map.find(current_task->name);
			if (it == task_map.end()) {
				result = 1;
				LOG("Error: Task '" << current_task->name << "' does not exist.");
			}
			else {
				physics_buffer.push_back(std::pair<std::string, WorldObj*>(current_task->name, obj));
				//result = (moveHelper->*(it->second))(obj);
				cout << "pushed to physics buffer, size is " << physics_buffer.size() << endl;
				result = 0;
			}
		}

		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
	}
	else {
		current_task->updateStatus("FAILED");
	}
	this->send_result(current_task);
}

void PhysicsManager::process_task(std::pair<std::string,WorldObj*> _pair)
{
	auto it = task_map.find(_pair.first);
	(moveHelper->*(it->second))(_pair.second);
}
