#include "stdafx.h"
#include "DialogueGui.h"

DialogueGui::DialogueGui()
{
  this->background_rect = new Rectangle({DialogueGui::BACKGROUND_X, DialogueGui::BACKGROUND_Y}, DialogueGui::BACKGROUND_WIDTH, DialogueGui::BACKGROUND_HEIGHT);
  this->header_rect = new Rectangle({DialogueGui::HEADER_X, DialogueGui::HEADER_Y}, DialogueGui::HEADER_WIDTH, DialogueGui::HEADER_HEIGHT);
  this->icon_sword_rect = new Rectangle({DialogueGui::ICON_SWORD_X, DialogueGui::ICON_SWORD_Y}, DialogueGui::ICON_WIDTH, DialogueGui::ICON_HEIGHT);
  this->icon_heart_rect = new Rectangle({DialogueGui::ICON_HEART_X, DialogueGui::ICON_HEART_Y}, DialogueGui::ICON_WIDTH, DialogueGui::ICON_HEIGHT);
  this->icon_face_rect = new Rectangle({DialogueGui::ICON_FACE_X, DialogueGui::ICON_FACE_Y}, DialogueGui::ICON_WIDTH, DialogueGui::ICON_HEIGHT);
  this->icon_question_rect = new Rectangle({DialogueGui::ICON_QUESTION_X, DialogueGui::ICON_QUESTION_Y}, DialogueGui::ICON_WIDTH, DialogueGui::ICON_HEIGHT);
  this->speaker_left_rect = new Rectangle({DialogueGui::SPEAKER_LEFT_X, DialogueGui::SPEAKER_LEFT_Y}, DialogueGui::SPEAKER_LEFT_WIDTH, DialogueGui::SPEAKER_LEFT_HEIGHT);
  this->speaker_right_rect = new Rectangle({DialogueGui::SPEAKER_RIGHT_X, DialogueGui::SPEAKER_RIGHT_Y}, DialogueGui::SPEAKER_RIGHT_WIDTH, DialogueGui::SPEAKER_RIGHT_HEIGHT);

  this->background_tex = new Texture();
  this->header_tex = new Texture();
  this->icon_sword_tex = new Texture();
  this->icon_sword_glow_tex = new Texture();
  this->icon_heart_tex = new Texture();
  this->icon_heart_glow_tex = new Texture();
  this->icon_face_tex = new Texture();
  this->icon_face_glow_tex = new Texture();
  this->icon_question_tex = new Texture();
  this->icon_question_glow_tex = new Texture();
  this->speaker_left_tex = nullptr;
  this->speaker_right_tex = nullptr;

  text_color_default = glm::vec3(0, 0, 0);
  text_color_selected = glm::vec3(50, 0, 0);
  DialogueController::scroll_control = 0;
}


DialogueGui::~DialogueGui()
{
  delete this->background_rect;
  delete this->header_rect;
  delete this->icon_sword_rect;
  delete this->icon_heart_rect;
  delete this->icon_face_rect;
  delete this->icon_question_rect;
  delete this->speaker_left_rect;
  delete this->speaker_right_rect;

  delete this->background_tex;
  delete this->header_tex;
  delete this->icon_sword_glow_tex;
  delete this->icon_sword_tex;
  delete this->icon_heart_tex;
  delete this->icon_heart_glow_tex;
  delete this->icon_face_tex;
  delete this->icon_face_glow_tex;
  delete this->icon_question_tex;
  delete this->icon_question_glow_tex;
}

void DialogueGui::loadTexture()
{
  this->background_tex->setFile(SPRITES_PATH + "Dialogue_Background.png", 1);
  this->header_tex->setFile(SPRITES_PATH + "Dialogue_Header.png", 1);

  this->icon_sword_tex->setFile(SPRITES_PATH + "Dialogue_IconSword.png", 1);
  this->icon_sword_glow_tex->setFile(SPRITES_PATH + "Dialogue_IconSword_Glow.png", 1);
  this->icon_heart_tex->setFile(SPRITES_PATH + "Dialogue_IconHeart.png", 1);
  this->icon_heart_glow_tex->setFile(SPRITES_PATH + "Dialogue_IconHeart_Glow.png", 1);
  this->icon_face_tex->setFile(SPRITES_PATH + "Dialogue_IconFace.png", 1);
  this->icon_face_glow_tex->setFile(SPRITES_PATH + "Dialogue_IconFace_Glow.png", 1);
  this->icon_question_tex->setFile(SPRITES_PATH + "Dialogue_IconQuestion.png", 1);
  this->icon_question_glow_tex->setFile(SPRITES_PATH + "Dialogue_IconQuestion_Glow.png", 1);
}

void DialogueGui::setSprite()
{
  this->background_rect->sprite.setTexture(this->background_tex);
  this->header_rect->sprite.setTexture(this->header_tex);
  this->setSwordGlow();
}

/**
 * Sets the current topic filter selection to the sword icon.
 */
void DialogueGui::setSwordGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_glow_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_tex);
}

/**
 * Sets the current topic filter selection to the heart icon.
 */
void DialogueGui::setHeartGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_glow_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_tex);
}

/**
 * Sets the current topic filter selection to the face icon.
 */
void DialogueGui::setFaceGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_glow_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_tex);
}

/**
 * Sets the current topic filter selection to the question mark icon.
 */
void DialogueGui::setQuestionGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_glow_tex);
}

/**
 * Sets the texture for the left-side speaker portrait to that specified.
 *
 * Param speakerTexture: The new texture to be used
 */
void DialogueGui::setLeftSpeaker(Texture *speakerTexture)
{
  this->speaker_left_tex = speakerTexture;
}

/**
 * Sets the texture for the right-side speaker portrait to that specified.
 *
 * Param speakerTexture: The new texture to be used
 */
void DialogueGui::setRightSpeaker(Texture *speakerTexture)
{
  this->speaker_right_tex = speakerTexture;
}

/**
 * Draws all elements of the dialogue GUI.
 */
void DialogueGui::drawGui()
{
  // Draw the dialogue background and icon header
  GameWindow::drawSprite(this->background_rect->getX(), this->background_rect->getY(),
    this->background_rect->getWidth(), this->background_rect->getHeight(), this->background_rect->getSprite());
  GameWindow::drawSprite(this->header_rect->getX(), this->header_rect->getY(),
    this->header_rect->getWidth(), this->header_rect->getHeight(), this->header_rect->getSprite());

  // Draw the four topic grouping icons
  GameWindow::drawSprite(this->icon_sword_rect->getX(), this->icon_sword_rect->getY(),
    this->icon_sword_rect->getWidth(), this->icon_sword_rect->getHeight(), this->icon_sword_rect->getSprite());
  GameWindow::drawSprite(this->icon_heart_rect->getX(), this->icon_heart_rect->getY(),
    this->icon_heart_rect->getWidth(), this->icon_heart_rect->getHeight(), this->icon_heart_rect->getSprite());
  GameWindow::drawSprite(this->icon_face_rect->getX(), this->icon_face_rect->getY(),
    this->icon_face_rect->getWidth(), this->icon_face_rect->getHeight(), this->icon_face_rect->getSprite());
  GameWindow::drawSprite(this->icon_question_rect->getX(), this->icon_question_rect->getY(),
    this->icon_question_rect->getWidth(), this->icon_question_rect->getHeight(), this->icon_question_rect->getSprite());

  this->drawGuiText();

  /*std::string message = DialogueController::getMessage();
  GameWindow::createText(message, 266, 303, 500, 80, text_color_default);

  std::vector<std::vector<std::string>> options;
  if(DialogueController::getState() == 1) {
    options = DialogueController::getOptions();
    for(int i = 0; i <= 4; ++i) {
      if(options.size() <= (DialogueController::scroll_control + i))
        break;

      std::string option_str = replace_str_char(options[DialogueController::scroll_control + i][1], "_", ' ');
      if(option_str.find("Advise To", 0) != string::npos || option_str.find("Ask About", 0) != string::npos)
        option_str += (" " + options[DialogueController::scroll_control + i][3]);

      if(DialogueController::getSelect() == i)
        GameWindow::createText(option_str, 292, 390 + (18 * i), 544, 45, text_color_selected);
      else
        GameWindow::createText(option_str, 292, 390 + (18 * i), 544, 45, text_color_default);
    }
  }
  else if(DialogueController::getState() == 2) {
    options = DialogueController::getReplyOptions();
    for(int i = 0; i <= 4; ++i) {
      if(options.size() <= (DialogueController::scroll_control + i))
        break;

      std::string option_str = replace_str_char(options[DialogueController::scroll_control + i][1], "_", ' ');
      if(option_str.find("Take Advice", 0) != string::npos || option_str.find("Tell About", 0) != string::npos)
        option_str += (" " + options[DialogueController::scroll_control + i][3]);

      if(DialogueController::getSelect() == i)
        GameWindow::createText(option_str, 292, 390 + (18 * i), 544, 45, text_color_selected);
      else
        GameWindow::createText(option_str, 292, 390 + (18 * i), 544, 45, text_color_default);

    }
  }
  else if(DialogueController::getState() == 5)
    GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  else if(DialogueController::getState() == 6)
    GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  else if(DialogueController::getState() == 7)
    GameWindow::createText("Exit", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  else if(DialogueController::getState() == 8)
    GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  else if(DialogueController::getState() == 9)
    GameWindow::createText("Exit", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  else if(DialogueController::getState() == 10)
    GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);*/
}

void DialogueGui::drawGuiText()
{
  GameWindow::createText(DialogueController::getMessage(),
    DialogueGui::MESSAGE_X, DialogueGui::MESSAGE_Y,
    DialogueGui::MESSAGE_WIDTH, DialogueGui::MESSAGE_HEIGHT,
    text_color_default);

  switch(DialogueController::getState()) {
    case 1:
      for(int i = 0; i <= 4; ++i) {
        if(DialogueController::getOptions().size() <= (DialogueController::scroll_control + i))
          break;

        std::string option_str = replace_str_char(DialogueController::getOptions()[DialogueController::scroll_control + i][1], "_", ' ');
        if(option_str.find("Advise To", 0) != string::npos || option_str.find("Ask About", 0) != string::npos)
          option_str += (" " + DialogueController::getOptions()[DialogueController::scroll_control + i][3]);

        GameWindow::createText(option_str,
          DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * i),
          DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
          (DialogueController::getSelect() == i) ? this->text_color_selected : text_color_default);
      }

      break;
    case 2:
      for(int i = 0; i <= 4; ++i) {
        if(DialogueController::getReplyOptions().size() <= (DialogueController::scroll_control + i))
          break;

        std::string option_str = replace_str_char(DialogueController::getReplyOptions()[DialogueController::scroll_control + i][1], "_", ' ');
        if(option_str.find("Take Advice", 0) != string::npos || option_str.find("Tell About", 0) != string::npos)
          option_str += (" " + DialogueController::getReplyOptions()[DialogueController::scroll_control + i][3]);

        GameWindow::createText(option_str,
          DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * i),
          DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
          (DialogueController::getSelect() == i) ? this->text_color_selected : text_color_default);
      }

      break;
    case 5:
      GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
      break;
    case 6:
      GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
      break;
    case 7:
      GameWindow::createText("Exit", 292, 390 + (18 * 1), 544, 45, text_color_selected);
      break;
    case 8:
      GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
      break;
    case 9:
      GameWindow::createText("Exit", 292, 390 + (18 * 1), 544, 45, text_color_selected);
      break;
    case 10:
      GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
      break;
  }
}

/*Removes all appearances of a specified char(charsToRemove) from a
specified string(str)*/
std::string DialogueGui::remove_chars_from_string(string &str, char* charsToRemove)
{
  for(unsigned int i = 0; i < strlen(charsToRemove); ++i) {
    str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
  }
  return str;
}

/*Replaces all appearances of a specified string(replace) with a
specified char(ch)*/
std::string DialogueGui::replace_str_char(string str, const string& replace, char ch)
{

// set our locator equal to the first appearance of any character in replace
  size_t found = str.find_first_of(replace);

  while(found != string::npos) { // While our position in the sting is in range.
    str[found] = ch; // Change the character at position.
    found = str.find_first_of(replace, found + 1); // Relocate again.
  }

  return str; // return our new string.
}
