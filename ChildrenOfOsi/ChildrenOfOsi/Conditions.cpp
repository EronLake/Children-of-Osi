#include "stdafx.h"
#include "Conditions.h"

////////////////////////////////////////////////////////////////////////////////////
//PRECONDITIONS
////////////////////////////////////////////////////////////////////////////////////

Preconditions::Preconditions()
{
	LOG("Precondition Object Constructed");
}


Preconditions::~Preconditions()
{
	LOG("Precondition Object Destroyed");
}

float Preconditions::get_cost()
{
	LOG("virtual function");
	return 0.0;
}

std::string Preconditions::get_type()
{
	return type;
}

std::string Preconditions::get_general_type()
{
	return general_type;
}
//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIP PRECONDITIONS
////////////////////////////////////////////////////////////////////////////////////

RelPrecon::RelPrecon(std::string _rel_type, std::string _rel_bound, int _desired_rel_val)
{
	rel_type = _rel_type;
	rel_bound = _rel_bound;
	desired_rel_val = _desired_rel_val;

	type = "relationship"+ rel_type+ rel_bound;
	general_type = "relationship";

	LOG("RelPrecon Object Constructed");
}


RelPrecon::~RelPrecon()
{
	LOG("Relprecon Object Destroyed");
}

float RelPrecon::get_cost(Hero* curr_hero, Hero* other_hero)
{
	int current_rel;
	if(rel_type == "Affinity")
	{ 
		current_rel = curr_hero->rel[other_hero->name]->getAffinity();
	} 
	else if(rel_type == "Notoriety")
	{
		current_rel = curr_hero->rel[other_hero->name]->getNotoriety();
	}
	else if(rel_type == "Strength")
	{
		current_rel = curr_hero->rel[other_hero->name]->getStrength();
	}

	float cost = 0.0;

	if (rel_bound == "lower" && desired_rel_val > current_rel ||
		rel_bound == "upper" && desired_rel_val < current_rel)
	{
			cost = std::abs(desired_rel_val - current_rel);
	}
	
	return cost;
}

//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIP ASSUMPTION PRECONDITION
////////////////////////////////////////////////////////////////////////////////////

RelEstimPrerec::RelEstimPrerec(std::string _rel_type, std::string _rel_bound, int _desired_rel_val)
{
	rel_type = _rel_type;
	rel_bound = _rel_bound;
	desired_rel_val = _desired_rel_val;

	type = "relationship_estimate" + rel_type + rel_bound;
	general_type = "relationship_estimate";

	LOG("RelEstimPrerec Object Constructed");
}


RelEstimPrerec::~RelEstimPrerec()
{
	LOG("RelEstimPrerec Object Destroyed");
}

float RelEstimPrerec::get_cost(Hero* curr_hero, Hero* other_hero)
{
	int current_est;
	if (rel_type == "Affinity")
	{
		current_est = curr_hero->rel[other_hero->name]->getAffEstimate();
	}
	else if (rel_type == "Notoriety")
	{
		current_est = curr_hero->rel[other_hero->name]->getNotorEstimate();
	}
	else if (rel_type == "Strength")
	{
		current_est = curr_hero->rel[other_hero->name]->getStrEstimate();
	}

	float cost = 0.0;

	if (rel_bound == "lower" && desired_rel_val > current_est ||
		rel_bound == "upper" && desired_rel_val < current_est)
	{
		cost = std::abs(desired_rel_val - current_est);
	}

	return cost;
}

//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//TIME PRECONDITION
////////////////////////////////////////////////////////////////////////////////////

TimePrerec::TimePrerec(int _time_rec)
{
	time_rec = _time_rec;

	type = "time";
	general_type= "time";

	LOG("TimePrerec Object Constructed");
}


TimePrerec::~TimePrerec()
{
	LOG("TimePrerec Object Destroyed");
}

float TimePrerec::get_cost()
{
	float cost = 0.0;
	float magnifier = 1.0;

	/*
	if (clock->get_curr_time() < time_rec) 
	{
		cost = std::abs(clock->get_curr_time() - time_rec)*magnifier;
	}
	*/
	
	return cost;
}

//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//MEMORY NUMBER PRECONDITION
////////////////////////////////////////////////////////////////////////////////////

MemoryNumPrerec::MemoryNumPrerec(int _rec_num_of_mem)
{
	rec_num_of_mem = _rec_num_of_mem;

	type = "memory_number";
	general_type = "memory_number";

	LOG("MemoryNumPrerec Object Constructed");
}


MemoryNumPrerec::~MemoryNumPrerec()
{
	LOG("MemoryNumPrerec Object Destroyed");
}

float MemoryNumPrerec::get_cost(std::vector<Memory*> memories)
{
	float cost = 0.0;
	float magnifier = 10.0;//this has to essentially the cost of an average memory

	if (memories.size() < rec_num_of_mem)
	{
		cost = std::abs((int)(memories.size() - rec_num_of_mem))*magnifier;
	}

	return cost;
}
//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//MEMORY PRECONDITION
////////////////////////////////////////////////////////////////////////////////////
MemPrerec::MemPrerec(std::string _rec_mem)
{
	rec_mem = _rec_mem;

	type = "memory"+rec_mem;
	general_type = "memory";

	LOG("particularMemPrerec Object Constructed");
}


MemPrerec::~MemPrerec()
{
	LOG("particularMemPrerec Object Destroyed");
}

float MemPrerec::get_cost(std::vector<Memory*> memories)
{
	float cost = 0.0;
	float magnifier = 10.0;//this has to essentially the cost of an average memory

	for (int i = 0; i < memories.size(); i++)
	{
		if (memories[i]->getContent() == rec_mem)
			return cost;
	}
	
	cost = 10.0; // cost must equal average of given mem once actions have cost of doing them
				 // we may be able to use that to make the function por acurate

	return cost;
}

////////////////////////////////////////////////////////////////////////////////////
//STATE PRECONDITION
////////////////////////////////////////////////////////////////////////////////////
StatePrerec::StatePrerec()
{
	/*state_manager st_man,
	std::string required state,
	std::vectorr<relevant villages>*/

	type = "state";
	general_type = "state";

	LOG("particularMemPrerec Object Constructed");
}


StatePrerec::~StatePrerec()
{
	LOG("particularMemPrerec Object Destroyed");
}

float StatePrerec::get_cost()
{
	float cost = 0.0;
	float magnifier = 10.0;//this has to essentially the cost of an average state change

	return cost;
}








////////////////////////////////////////////////////////////////////////////////////
//MEMORY POSTCONDITION
////////////////////////////////////////////////////////////////////////////////////
Postcondition::Postcondition()
{
	/*state_manager st_man,
	std::string required state,
	std::vectorr<relevant villages>*/

	type = "state";

	LOG("particularMemPrerec Object Constructed");
}


Postcondition::~Postcondition()
{
	LOG("particularMemPrerec Object Destroyed");
}

float Postcondition::get_utility()
{
	LOG("virtual function");
	return 0.0;
}

float Postcondition::get_utility(Hero* curr_hero, Hero* other_hero)
{
	LOG("virtual function");
	return 0.0;
}

void Postcondition::apply_utility()
{
	LOG("virtual function");
}

void Postcondition::apply_utility(Hero* curr_hero, Hero* other_hero)
{
	LOG("virtual function");
}

std::string Postcondition::get_type()
{
	return type;
}

std::string Postcondition::get_general_type()
{
	return general_type;
}


//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIP POSTCONDITION
////////////////////////////////////////////////////////////////////////////////////

RelPost::RelPost(std::string _rel_type, int _utility)
{
	rel_type = _rel_type;
	utility = _utility;
	std::string bound;
	if (utility > 0) {
		bound = "upper";
	}
	else {
		bound = "lower";
	}

	type = "relationship"+rel_type+bound;
	general_type = "relationship";

	LOG("RelEstimPost Object Constructed");
}


RelPost::~RelPost()
{
	LOG("RelEstimPost Object Destroyed");
}

float RelPost::get_utility(Hero* curr_hero, Hero* other_hero)
{
	return utility;
}

void RelPost::apply_utility(Hero* curr_hero, Hero* other_hero)
{
	if (rel_type == "Affinity")
	{
		curr_hero->rel[other_hero->name]->addAffinity(utility);
	}
	else if (rel_type == "Notoriety")
	{
		curr_hero->rel[other_hero->name]->addNotoriety(utility);
	}
	else if (rel_type == "Strength")
	{
		curr_hero->rel[other_hero->name]->addStrength(utility);
	}
}

//Returns null plug string if the postcondition does not complete
//any of the given preconditions
//Returns the string key of the precondition if one is found

std::string RelPost::fulfills_which(vector<std::string> preconds, Precond_vec vec)
{
	
	string pre_fulfilled = "\0"; 
	/*
	for (int precond_string = 0; precond_string < preconds.size(); precond_string++) {
		Preconditions* precond = map[precond_string].get();
		if (precond->get_type() != "relationship") //Skip non-relation preconds
		{
			continue;
		}
		else
		{
			RelPrecon* rel_pre = dynamic_cast<RelPrecon*>(precond);
		}
		

	}
	*/
	return pre_fulfilled;
}

//---------------------------------------------------------------------------------



////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIP ASSUMPTION POSTCONDITION
////////////////////////////////////////////////////////////////////////////////////

RelEstimPost::RelEstimPost( std::string _rel_type, int _utility)
{
	rel_type = _rel_type;
	utility = _utility;
	std::string bound;
	if (utility > 0) {
		bound = "upper";
	}
	else {
		bound = "lower";
	}

	type = "relationship_estimate"+rel_type+bound;
	general_type = "relationship_estimate";

	LOG("RelEstimPost Object Constructed");
}


RelEstimPost::~RelEstimPost()
{
	LOG("RelEstimPost Object Destroyed");
}

float RelEstimPost::get_utility(Hero* curr_hero, Hero* other_hero)
{
	return utility;
}

void RelEstimPost::apply_utility(Hero* curr_hero, Hero* other_hero)
{
	if (rel_type == "Affinity")
	{
		curr_hero->rel[other_hero->name]->addAffEstimate(utility);
	}
	else if (rel_type == "Notoriety")
	{
		curr_hero->rel[other_hero->name]->addNotorEstimate(utility);
	}
	else if (rel_type == "Strength")
	{
		curr_hero->rel[other_hero->name]->addStrEstimate(utility);
	}
}

//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//STATE POSTCONDITION
////////////////////////////////////////////////////////////////////////////////////
StatePost::StatePost(int _utility)
{
	/*state_manager st_man,
	std::string required state,
	std::vectorr<relevant villages>*/
	utility = _utility;

	type = "state";
	general_type = "state";

	LOG("StatePost Object Constructed");
}


StatePost::~StatePost()
{
	LOG("StatePost Object Destroyed");
}

float StatePost::get_utility()
{
	return utility;
}

void StatePost::apply_utility()
{
	LOG("Still needs to be implimented");
}
