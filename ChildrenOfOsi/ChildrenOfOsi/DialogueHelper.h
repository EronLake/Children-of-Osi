#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"


typedef std::vector<std::string> dialogue_point;
typedef std::vector<std::string> dialogue_template;

class DialogueHelper
{
private:
	std::vector<dialogue_point> possible_conv_pts;
	std::vector<dialogue_point> possible_reply_pts;


public:
	DialogueHelper();
	~DialogueHelper();

	//functions where heroes make dialogue choices
	dialogue_point choose_conv_pt(dialogue_point);
	dialogue_point choose_reply_pt(dialogue_point);
	std::vector<dialogue_point> get_possible_conv_pts();
	std::vector<dialogue_point> get_possible_reply_pts();

	std::string gen_dialog(dialogue_point, Hero*);
	std::string gen_reply(dialogue_point);

	dialogue_template get_template();
	dialogue_point get_dialog(std::string name);

};

