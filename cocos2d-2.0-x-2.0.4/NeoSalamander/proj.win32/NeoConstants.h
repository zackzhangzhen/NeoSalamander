#pragma once
class NeoConstants
{
public:
	NeoConstants(void);
	~NeoConstants(void);

	//window
	static int WIN_WIDTH;
	static int WIN_HEIGHT;
	static int WIDTH_TOLERANCE;
	static int HEIGHT_TOLERANCE;

	//motion
	static const int MOVE_DOWN;
	static const int MOVE_LEFT;
	static const int MOVE_RIGHT;

	//script - attr
	static const char* SCRIPT_FILE_LOC;
	static const char* BG_PIC_BASE;
	static const char* BG_PIC_DEFAULT;
	static const char* SCRIPT_ATTR_POS;
	static const char* SCRIPT_ATTR_SIZE;
	static const char* SCRIPT_ATTR_FONT;
	static const char* SCRIPT_ATTR_COLOR;
	static const char* SCRIPT_ATTR_IMAGE;
	static const char* SCRIPT_ATTR_PIC;
	static const char* SCRIPT_ATTR_TITLE;
	static const char* SCRIPT_ATTR_TO_SCRIPT;
	static const char* SCRIPT_ATTR_MUSIC;
	static const char* SCRIPT_ATTR_SOUND;
	static const char* SCRIPT_ATTR_SOUND_OPTION_CORRECT;
	static const char* SCRIPT_ATTR_ID;
	static const char* SCRIPT_ATTR_STOP_MUSIC;
	static const char* SCRIPT_ATTR_FIGURE_VERTICAL_OFFSET;
	static const char* CUE_PIC_LOC;

	//script - tag
	static const char* SCRIPT_TAG_LINE;
	static const char* SCRIPT_TAG_OPTIONS;
	static const char* SCRIPT_TAG_AUTO_LINES;
	static const char* SCRIPT_TAG_AUTO_SCRIPT;
	static const char* SCRIPT_TAG_DLG;
	static const char* SCRIPT_TAG_AUTO_DLG;
	static const char* STARTING_SCRIPT_ID;

	//autoline
	static const char* PRE_BLANK;
	static const char* FADE_IN_TIME;
	static const char* PRESENT_TIME;
	static const char* FADE_OUT_TIME;
	static const char* POST_BLANK;

	static const int PRE_BLANK_DEFAULT = 1;
	static const int FADE_IN_TIME_DEFAULT = 2;
	static const int PRESENT_TIME_DEFAULT = 4;
	static const int FADE_OUT_TIME_DEFAULT = 2;
	static const int POST_BLANK_DEFAULT = 1;

	//Dlg elment's position
	static int FIGURE_VERTICAL_OFFSET;

	static const char* DUMMY_PIC_LOC;

	//Dlg type
	static const int DLG_TYPE_NORMAL = 0;
	static const int DLG_TYPE_AUTO = 1;

	//Save	
	static const char* SAVE_FILE_LOC;
	static const char* SAVE_NODE_ROOT_TAG;
	static const char* SAVE_NODE_TAG;

	//Menu	
	static const char* MAIN_MENU_FILE_LOC;
	static const int MAIN_MENU_ID;
	static const int LOAD_MENU_ID;
	static const char* LOAD_MENU_BACK_BUTTON_ID;
	static const char* BACK_MENU_NORMAL_IMAGE_PATH;
	static const char* BACK_MENU_SELECTED_IMAGE_PATH;

	//Sound
	static const char* DEFAULT_SOUND_NAME;

	//Scene
	static const char* SCENE_NAME_TITLE;
	static const char* SCENE_NAME_MAIN;
	static const int GAME_MENU_DEFAULT_COLOR = 3;
};

