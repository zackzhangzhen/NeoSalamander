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

	//script
	static const char* SCRIPT_FILE_LOC;
	static const char* BG_PIC_BASE;
	static const char* SCRIPT_ATTR_PIC;
	static const char* SCRIPT_ATTR_NEXT;
	static const char* SCRIPT_ATTR_FIGURE_VERTICAL_OFFSET;
	static const char* CUE_PIC_LOC;

	//Dlg elment's position
	static int FIGURE_VERTICAL_OFFSET;

	static const char* DUMMY_PIC_LOC;
};

