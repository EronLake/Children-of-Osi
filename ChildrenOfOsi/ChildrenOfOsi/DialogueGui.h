#pragma once
#include "common.h"
#include "Rectangle.h"
#include "GameWindow.h"
#include "DialogueController.h"

class DialogueGui
{

private:
	Rectangle* background;
	Rectangle* swordIcon;
	Rectangle* heartIcon;
	Rectangle* faceIcon;
	Rectangle* questionIcon;
	Rectangle* dialogueBox;
	Rectangle* responseBox1;
	Rectangle* responseBox2;
	Rectangle* portrait1;
	Rectangle* portrait2;

	//Texture
	Texture* backgroundTex;
	Texture* swordTex;
	Texture* swordGlowTex;
	Texture* heartTex;
	Texture* heartGlowTex;
	Texture* faceTex;
	Texture* faceGlowTex;
	Texture* questionTex;
	Texture* questionGlowTex;
	Texture* dialogueBoxTex;
	Texture* responseBoxTex;
	
	glm::vec3 black;
	glm::vec3 red;

public:
	DialogueGui();
	~DialogueGui();
	void loadTexture();
	void setSprite();
	void drawGui();
	void setPortrait1(Sprite portrait1Sprite);
	void setPortrait2(Sprite portrait2Sprite);
	void setSwordGlow();
	void setHeartGlow();
	void setFaceGlow();
	void setQuestionGlow();
	std::string remove_chars_from_string(string &str, char* charsToRemove);
	std::string replace_str_char(string str, const string& replace, char ch);
	
};

