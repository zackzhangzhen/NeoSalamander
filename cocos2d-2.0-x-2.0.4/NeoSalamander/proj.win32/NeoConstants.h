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
	static const char* SCRIPT_ATTR_POS;
	static const char* SCRIPT_ATTR_SIZE;
	static const char* SCRIPT_ATTR_FONT;
	static const char* SCRIPT_ATTR_COLOR;
	static const char* SCRIPT_ATTR_IMAGE;
	static const char* SCRIPT_ATTR_PIC;
	static const char* SCRIPT_ATTR_TITLE;
	static const char* SCRIPT_ATTR_TO_SCRIPT;
	static const char* SCRIPT_ATTR_MUSIC;
	static const char* SCRIPT_ATTR_ID;
	static const char* SCRIPT_ATTR_STOP_MUSIC;
	static const char* SCRIPT_ATTR_FIGURE_VERTICAL_OFFSET;
	static const char* CUE_PIC_LOC;

	//script - tag
	static const char* SCRIPT_TAG_LINE;
	static const char* SCRIPT_TAG_OPTIONS;

	//Dlg elment's position
	static int FIGURE_VERTICAL_OFFSET;

	static const char* DUMMY_PIC_LOC;
};

