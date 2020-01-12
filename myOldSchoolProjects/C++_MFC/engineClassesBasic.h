#ifndef ENGINE_CLASSES_BASIC
#define ENGINE_CLASSES_BASIC

enum MusicCommandType
{
	CMD_PLAY,
	CMD_INPLAY,
	CMD_FADEOUT,
	CMD_STOP,
	CMD_WAIT,
	CMD_PAUSE,
	CMD_COUNT
};

enum InteractiveSceneType
{
	USER_INTERFACE_SCENE,
	WORLD_GAME_SCENE,
	INTERACTIVE_SCENE_COUNT
};

enum InteractionType
{
	MN_SENSES,
	MN_ACTION,
	MN_INVENTORY,
	MN_NAVIGATE,
	MN_COUNT
};

enum InteractionSubType
{
	SUB_LOOK,
	SUB_SMELL,
	SUB_TASTE,
	SUB_TEXTURE,
	SUB_SOUND,
	SUB_TYPE_LAST
};

enum LayerType
{
	NAVIGABLE_SCENE,
	NON_NAVIGABELE_SCENE,
	SPECIAL_ACTION_SCENE,
	SCENE_OVERLAYS,
	STANDART_USER_INTERFACE_ELEMENTS,
	USER_INTERFACE_OVERLAYS
};

enum LightingModeType
{
	LT_OFF,
	LT_SOLID,
	LT_MAPPED
};

enum TextType
{
	TXT_STRING,
	TXT_FEEDBACK 	
};

enum HotSpotModeType
{
	HT_IMAGE,
	HT_ANIM,
	HT_CHAR,
	HT_RECT
};

const int TIME_COUNT = 16;
const int ALTITUDE_MAP_COUNT = 255;
#endif