#include "stdafx.h"
#include "PlayerActExecFunctions.h"


PlayerActExecFunctions::PlayerActExecFunctions()
{
}


PlayerActExecFunctions::~PlayerActExecFunctions()
{
}


void PlayerActExecFunctions::execute_start(std::string act_name, Hero* receiver) {

	std::cout << "------------EX_START-------------" << std::endl;

	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);

	//note: act_name should corrispond to the action names in json so they can be looked up in action table
	
	// import action based off of an already exting action of the reciver
	Action* ref_action = Containers::action_table[act_name + "_" + std::to_string(receiver->name)];

	Action* cur_action = new Action(player, receiver, player, ref_action->getUtility(), ref_action->getWhy(),
		ref_action->name, ref_action->exe_name);

	//for multipliers and preconditions it points the the references' actual objects
	//sets multipliers to references multipliers
	cur_action->multipliers = ref_action->multipliers;
	cur_action->aff_mult = cur_action->aff_mult;
	cur_action->str_mult = cur_action->str_mult;
	cur_action->noto_mult = cur_action->noto_mult;

	//sets preconditions to references preconditions
	cur_action->req_preconds = ref_action->req_preconds;

	cur_action->doer_succ_postconds = ref_action->doer_succ_postconds;
	cur_action->receiver_succ_postconds = ref_action->receiver_succ_postconds;

	cur_action->doer_fail_postconds = ref_action->doer_fail_postconds;
	cur_action->receiver_fail_postconds = ref_action->receiver_fail_postconds;

	//set to current action 
	player->cur_action = cur_action;

	//create the memory based off of the newly created current action
	ActionHelper::create_memory(cur_action, player);
	//creates the memory for the reciever as well
	ActionHelper::create_memory(cur_action, receiver);

	if ((act_name == "Occupy" || act_name == "Fight") &&
		((!player->getInCombat()) && (!player->getInCombat())))
	{
		//we need to create a fight here if their action is a violent action
		if (act_name == "duel") {
			Fight* fight_obj = new Fight(player->getParty(), receiver->getParty(), true);
		}
		else {
			Fight* fight_obj = new Fight(player->getParty(), receiver->getParty(), false);
		}
	}

	//ADITIONAL FUNCTION act_name == "Conquer" || act_name == "Duel" ||act_name == "Spar" ||

}



void PlayerActExecFunctions::execute_end(bool if_succ) {

	std::cout << "------------EX_END-------------" << std::endl;

	///FOR ALESSIO

	//if another soldier is starts the fight it would cause a problem (check if player is in a fight/has cur action)
	//is called after warning hit
	//is called when hero is incapacited

	//NEED TO STILL DO MEMORIES
	//STILL NEED TO DO QUEST CHECK
	
	///////////////////////////////////////////


	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);

	Action* cur_action = player->cur_action;

	if (cur_action->name == "conquer" && player->getParty()->get_fight()->is_over()) {
		if (cur_action->getReceiver()->getVillage()->get_village_health() > 0) {
			cur_action->getReceiver()->getVillage()->defenders->add_party_to_party(cur_action->getReceiver()->getVillage()->barracks);
			if (player->getParty()->get_fight()!=nullptr)player->getParty()->get_fight()->add_to_defenders(cur_action->getReceiver()->getVillage()->defenders);
			return;
		}
	}

	Memory* doer_mem = player->find_mem(cur_action->getName() + std::to_string(cur_action->time_stamp));
	Memory* receiver_mem = cur_action->getReceiver()->find_mem(cur_action->getName() + 
							std::to_string(cur_action->time_stamp));

	if (doer_mem == nullptr)
	{
		perror("something is wrong with the current hero memory creation function");
	}
	

	////////////CAN WE PUT THIS AT THE END WITH THE DEALLOCATION///////////

	
	
	cur_action->apply_postconditions(if_succ);	//Apply post-conditions based off if it was succesful or not
	cur_action->executed = true;
	
	//if the action was successful check if the action was in the active quests
	if (if_succ) { check_quest(); }
	
	//reason sould be handled as a dialog response choice
	if (if_succ){
		doer_mem->setCategory("success");
		receiver_mem->setCategory("failure");
	}else{ 
		doer_mem->setCategory("failure");
		receiver_mem->setCategory("success");
	}
	doer_mem->setWhen(/*get global frame*/0);

	/*
	dealocate memory for fight if there was a fight
	and end the fight if a fight was involved
	*/
	if (player->getInCombat()) {
		player->getParty()->get_fight()->end_combat();
		delete player->getParty()->get_fight(); 
	}

	//dealocate memory for action
	
	//for multipliers and preconditions it points the the references' actual objects
	//sets multipliers to references multipliers
	cur_action->multipliers = nullptr;
	cur_action->aff_mult = nullptr;
	cur_action->str_mult = nullptr;
	cur_action->noto_mult = nullptr;
	//sets preconditions to references preconditions

	delete player->cur_action;
}
/*
void PlayerActExecFunctions::execute_dialog()
{
	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);

	Action* cur_action = player->cur_action;

	if ((act_name == "Occupy" || act_name == "Fight") &&
		((!player->getInCombat()) && (!player->getInCombat())))
	{
		//we need to create a fight here if their action is a violent action
		if (act_name == "duel") {
			Fight* fight_obj = new Fight(player->getParty(), receiver->getParty(), true);
		}
		else {
			Fight* fight_obj = new Fight(player->getParty(), receiver->getParty(), false);
		}
	}
}
*/

void PlayerActExecFunctions::check_quest() {

	std::cout << "------------CHECK QUEST-------------" << std::endl;

	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);

	for (auto itr : player->get_quests())
	{
		if (player->cur_action->getName() == itr.first->getName())
		{
			LOG("MARK QUEST AS COMPLETED")
		}
	}

}

