#include "stdafx.h"
#include "ActionConfig.h"
#include <ctime>


ActionConfig::ActionConfig()
{
}


ActionConfig::~ActionConfig()
{
}


void ActionConfig::import_config(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, Hero* owner)
{
	//iterates through every player
	for (auto i = Containers::hero_table.begin(); i != Containers::hero_table.end(); i++)
	{
		if (i->second->name != owner->name)
		{
			Json::Value root;
			Json::Reader reader;


			std::ifstream file("action_config.json");
			file >> root;
			for (auto itr = root.begin(); itr != root.end(); itr++)
			{
				set_action_obj(gameplay_func, tBuffer, owner, i->second,
					(*itr)["utility"].asFloat(), (*itr)["why"].asFloat(), (*itr)["type"].asString(),
					(*itr)["name"].asString(), (*itr)["exe_name"].asString(),
					(*itr)["aggression"].asInt(), (*itr)["kindness"].asInt(), (*itr)["honor"].asInt(),
					(*itr)["pride"].asInt(), (*itr)["recklessness"].asInt(), (*itr)["extroversion"].asInt(), 
					(*itr)["greed"].asInt());

			}
		}
	}
}

void ActionConfig::set_action_obj(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, Hero* owner,
									Hero* receiver, float utility, float why, std::string type, std::string name, std::string exe_name,
									int a, int k, int h, int p, int r, int e, int g)
{

	gameplay_func->add_action(name, utility, why, owner, receiver, owner, exe_name);
	tBuffer->run();

	Containers::action_table[name]->setMultipliers(a, k, h, p, r, e, g);

	std::cout << std::to_string(Containers::action_table[name]->multipliers->getAggression()) << std::endl;

	//for the add the action pointer to the current respective reiciver action pool
	if (type == "micro") {
		
		//needs to differenciate from pos and neg
		owner->actionPool_map[receiver->name]->micro.push_back(Containers::action_table[name]);
	}
	//then macro
	else if (type == "macro")
	{
		//needs to differenciate from pos and neg
		owner->actionPool_map[receiver->name]->end_states.push_back(Containers::action_table[name]);
	}
	else if (type == "end_states")
	{
		//needs to differenciate from pos and neg
		owner->actionPool_map[receiver->name]->macro.push_back(Containers::action_table[name]);
		owner->actionPool_map[receiver->name]->end_states.push_back(Containers::action_table[name]);
	}
	
	return;
}

