#ifndef _BASIC_H_
#define _BASIC_H_

#include "engineClasses.h"

enum NodeType
{
	TEMPLATE_NODE,
	DYNAMIC_NODE,
	UNDEFINED_NODE
};

const ROOT_NUM = 1; 
const WORLD_LEVEL_NUM = 7;
const SCENE_DEFINITION_NUM = 8;

const CLOSE_TREE_NODE = 0;
const OPEN_TREE_NODE = 1;
const CHILD_TREE_NODE = 2;
const LIST_NODE = 3;
const TEMPLATE_DYNAMIC_NODE = 4;

const FORMS_NUM = 16;
const DWORD DEFAULT_WORLD_ID = 0;
const DWORD DEFAULT_SCENE_ID = 0;

const LPCTSTR NEW_STR = "New ";
const LPCTSTR WORLD_STR = "World";
const LPCTSTR MUSIC_SCRIPT_STR = "Music Script";
const LPCTSTR MUSIC_SAMPLE_STR = "Music File";
const LPCTSTR SCENE_DEFINITION_STR = "Scene Definition";
const LPCTSTR SCENES_LIST_STR = "Scenes List";
const LPCTSTR SKY_DEFINITION_STR = "Sky Definition";
const LPCTSTR ITEM_DEFINITION_STR = "Inventory Definition";
const LPCTSTR CAMERA_DEFINITION_STR = "Camera Definition";
const LPCTSTR STAGING_INFO_STR = "Staging Info";
const LPCTSTR IMAGE_INFO_STR = "Image Info";
const LPCTSTR ANIMATION_INFO_STR = "Animation Info";
const LPCTSTR CHARACTER_INFO_STR = "Character Info";
const LPCTSTR CHARACTER_CONTEXT_STR = "Character Context";
const LPCTSTR SFX_INFO_STR = "Sound Effect Info";
const LPCTSTR TEXT_DISPLAY_STR = "Text Display";
const LPCTSTR HOT_SPOT_INFO_STR = "HotSpot Info";
const LPCTSTR KEYBOARD_TRIGGER_STR = "Keyboard Trigger";

const LPCTSTR SubTypeStr[SUB_TYPE_LAST] = {
							                             "SUB_LOOK",
																					 "SUB_SMELL",
																					 "SUB_TASTE",
																					 "SUB_TEXTURE",
																					 "SUB_SOUND"}; 


const int  MAIN_WND_WIDTH  = 715;
const int  MAIN_WND_HEIGHT = 500;

const int  NOT_FOUND = -1;
const int  UNDEFINED_SCENE = -1;

const unsigned long UNSIGNED_LONG_MIN = 0;
const unsigned long UNSIGNED_LONG_MAX = 4294967295;

const short SHORT_MIN_VALUE = -32768;
const short SHORT_MAX_VALUE = 32767;

const unsigned char UNSIGNED_CHAR_MIN = 0;
const unsigned char UNSIGNED_CHAR_MAX = 255;

const unsigned char COLOR_MIN = 0;
const unsigned char COLOR_MAX = 239;

const unsigned char VOLUME_MIN = 0;
const unsigned char VOLUME_MAX = 100;

const int SPIN_DEFAULT_MIN_VAL = 0;
const int ONE_MIN_VALUE = 1;
const int SPIN_DEFAULT_MAX_VAL = 10000;
const int RGB_MIN_VAL = 0;
const int RGB_MAX_VAL = 255;
const int FONT_MIN_SIZE = 8;
const int FONT_MAX_SIZE = 72;
const int MIN_ANGLE = -90;
const int MAX_ANGLE = 90;
const int TEMP_BUFF_LEN = 256;

#define RUNTIME_SAVE_MESSAGE WM_USER + 100
#define UPDATE_WORLD_OBJECT  WM_USER + 101
#define CHANGE_SCENE_ID      WM_USER + 102
#define UPDATE_DELETING_IN_WORLD WM_USER + 103

#endif  // #ifndef _BASIC_H_
