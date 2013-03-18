#include "NeoConstants.h"

int NeoConstants::WIN_WIDTH = 800;
int NeoConstants::WIN_HEIGHT = 600;
int NeoConstants::WIDTH_TOLERANCE = 60;
int NeoConstants::HEIGHT_TOLERANCE = 60;
int NeoConstants::FIGURE_VERTICAL_OFFSET = 180;
const int NeoConstants::MOVE_DOWN = 0;
const int NeoConstants::MOVE_LEFT = 1;
const int NeoConstants::MOVE_RIGHT = 2;
const char* NeoConstants::BG_PIC_BASE = "pic\\bg\\";
const char* NeoConstants::SAVE_FILE_LOC = "save\\save.xml";
const char* NeoConstants::MAIN_MENU_FILE_LOC = "menu\\main_menu.xml";
const char* NeoConstants::SAVE_NODE_ROOT_TAG = "saves";
const char* NeoConstants::SAVE_NODE_TAG = "save";
const char* NeoConstants::SCRIPT_ATTR_PIC = "pic";
const char* NeoConstants::SCRIPT_ATTR_POS = "pos";
const char* NeoConstants::SCRIPT_ATTR_SIZE = "size";
const char* NeoConstants::SCRIPT_ATTR_FONT = "font";
const char* NeoConstants::SCRIPT_ATTR_COLOR = "color";
const char* NeoConstants::SCRIPT_ATTR_IMAGE = "image";
const char* NeoConstants::SCRIPT_ATTR_TITLE = "title";
const char* NeoConstants::SCRIPT_ATTR_TO_SCRIPT = "toScript";
const char* NeoConstants::SCRIPT_ATTR_MUSIC = "music";
const char* NeoConstants::SCRIPT_ATTR_SOUND = "sound";
const char* NeoConstants::SCRIPT_ATTR_SOUND_OPTION_CORRECT = "option_correct";
const char* NeoConstants::SCRIPT_ATTR_ID = "id";
const char* NeoConstants::SCRIPT_ATTR_STOP_MUSIC = "stopMusic";
const char* NeoConstants::SCRIPT_ATTR_FIGURE_VERTICAL_OFFSET = "figureVerticalOffset";
const char* NeoConstants::SCRIPT_FILE_LOC = "script\\script.xml";
const char* NeoConstants::CUE_PIC_LOC = "pic\\script\\cue\\";
const char* NeoConstants::DUMMY_PIC_LOC = "pic\\dummy\\dummy.png";
const char* NeoConstants::SCRIPT_TAG_LINE = "line";
const char* NeoConstants::SCRIPT_TAG_OPTIONS = "options";
const char* NeoConstants::SCENE_NAME_TITLE = "titleScene";
const char* NeoConstants::SCENE_NAME_MAIN = "mainScene";
const int NeoConstants::MAIN_MENU_ID = 0;
const int NeoConstants::LOAD_MENU_ID = 1;
NeoConstants::NeoConstants(void)
{
}


NeoConstants::~NeoConstants(void)
{
}
