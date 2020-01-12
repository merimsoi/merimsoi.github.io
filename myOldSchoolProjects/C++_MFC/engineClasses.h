#ifndef ENGINE_CLASSES
#define ENGINE_CLASSES
#include <list>

#include "StdList.h"
#include "StdString.h"
#include "engineClassesBasic.h"
#include <afxtempl.h>


class MusicSample
{	
public:
	MusicSample();
	MusicSample(DWORD id,LPCTSTR fileName);
	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);

//Attributes
	short m_sampleID;
	CStdString m_fileName;
	unsigned long m_startSample;
	unsigned long m_endSample;
};

class MusicScript
{
public:	
	MusicScript();
	MusicScript(DWORD id);

	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
//Attributes
	short m_scriptID;
	short m_commandCount;
	short m_loopStart;
	short m_loopEnd;
	short m_currentCommand;	

	StdListClass<MusicCommandType> m_command;
	StdListClass<short> m_sampleID;
  StdListClass<short> m_repeatCommand;
	StdListClass<bool> m_waitForCommandFinish;
	StdListClass<unsigned long> m_commandStartTime;
	StdListClass<unsigned long> m_commandEndTime;
	StdListClass<unsigned long> m_obeyCommand; 
};

class CharacterInfo
{
public:
	CharacterInfo();
	CharacterInfo(short characterId,LPCTSTR characterName);
	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);

//Attributes:
	short m_characterId;
	CStdString m_characterName;
	short m_clipCount;
	short m_defaultClip;
	StdListClass<CStdString> m_fileName; 
	StdListClass<CStdString> m_colorFile; 
  StdListClass<CStdString> m_vertexTable; 
  StdListClass<unsigned long> m_typeId;
	StdListClass<short> m_frameStart;
	StdListClass<short> m_frameEnd;
	StdListClass<short> m_framesPerSecond;
	StdListClass<short> m_loopCount;
};

class CharacterContext
{
public:
	CharacterContext();
  CharacterContext(DWORD id);
	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);

//Attributes:	
	short m_characterId;
	bool m_characterIsVisible;
	bool m_adjustForLight;
	short m_nodeCount;
  StdListClass<unsigned long> m_typeId;
  StdListClass<long> m_transX;
  StdListClass<long> m_transY;
  StdListClass<long> m_transZ;
  StdListClass<unsigned long> m_clockValue;
	short m_currentFrame;
	short m_nextFrame;
	unsigned long m_currentFrameClockValue;
	unsigned long m_nextFrameClockValue;
};

class SkyDefinition
{
public:
	SkyDefinition();
	SkyDefinition(DWORD id,LPCTSTR fileName);
  BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);	
//Attributes:	
	short m_skyID;
	CStdString m_fileName;
	short m_width;
	short m_height;
	short m_left;
	short m_top;
  short m_frameCount;
	short m_currentFrame;
	unsigned long m_currentFrameClockValue;
	unsigned long	m_frameClockInterval;
};

class StagingInfo
{
public:
	StagingInfo();
	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:
	CStdString m_imageFileName;
	short m_widthStart;
	short m_heightStart;
	short m_leftStart;
	short m_topStart;
	unsigned long m_startClockValue;
	short m_widthEnd;
	short m_heightEnd;
	short m_leftEnd;
	short m_topEnd;
	unsigned long m_endClockValue;
	CStdString m_alphaFileName;
	short m_leftAlpha;
	short m_topAlpha;
	CStdString m_mapFileName;
	unsigned char m_mapColorCount;
	long m_mapAltitudeIndex[ALTITUDE_MAP_COUNT];
	short m_mapLeft;
	short m_mapTop;
	short m_mapHeight;
	short m_mapWidth;
	LightingModeType m_lightingMode;
	CStdString m_lighterFileName;
	short m_lightAngleX;
	short m_lightAngleY;
	short m_lightAngleZ;
	unsigned char m_lightR;
	unsigned char m_lightG;
	unsigned char m_lightB;
	short m_cameraAngle;
	long m_cameraHeight;
};

class ImageInfo
{
public:
	ImageInfo();
	ImageInfo(DWORD id,LPCTSTR fileName);
	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:	
	short m_imageID;
	CStdString m_fileName;
	short m_widthStart;
	short m_heightStart;
	short m_leftStart;
	short m_topStart;
	short m_zStart;
	short m_zEnd;
	unsigned long m_startClockValue;
	short m_frameInterval; 
	short m_widthEnd;
	short m_heightEnd;
	short m_leftEnd;
	short m_topEnd;
	unsigned long m_endClockValue;
	short m_frameCount;
	short m_currentFrame;
	unsigned long m_currentFrameClockValue;
	unsigned long m_currentFrameClockInterval;
	short m_loopsRemaining;
	CStdString m_aplhaFileName;
	short m_leftAlpha;
	short m_topAlpha;
	bool m_imageIsVisible;
};

class AnimationInfo
{
public:
	AnimationInfo();
	AnimationInfo(DWORD id,LPCTSTR fileName);
	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:	
	short m_animationID;
	CStdString m_fileNameVideo;
	CStdString m_fileNameAudio;
	short m_widthStart;
	short m_heightStart;
	short m_leftStart;
  short m_topStart;
	short m_zStart;
	unsigned long m_startClockValue;
	short m_widthEnd;
	short m_heightEnd;
	short m_leftEnd;
	short m_topEnd;
	short m_zEnd;
	unsigned long m_endClockValue;
  unsigned long m_playStartValue;
	short m_startFrame;
	short m_currentFrame;
	unsigned long m_frameExparation;
	short m_endFrame;
	short m_loopsRemaining;
	unsigned long m_volStartClock;
	short m_volStart;
	unsigned long m_volEndClock;
	short m_volEnd;
  bool m_doVideo;
	bool m_doAudio;
};

class SFXInfo
{
public:
	SFXInfo();
  SFXInfo(DWORD id,LPCTSTR fileName);
  BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:
	short m_sfxID;
	CStdString m_fileName;
	unsigned long m_startClockValue;
	unsigned long m_startPosition;
	unsigned long m_endPosition;
	short m_loopsRemaining;
  unsigned long m_volStartClock;
	short m_volumeStart;
  unsigned long m_volEndClock;
	short m_volumeEnd;
	BOOL m_audioIsEnabled;
};

class TextDisplay
{
public:
	TextDisplay();
	TextDisplay(DWORD id);
  BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:
	short m_textID;
	CStdString m_fontName;
	TextType m_textType;
	CStdString m_displayString;
	unsigned long m_startClockValue;
	unsigned char m_colorRStart;
	unsigned char m_colorGStart;
	unsigned char m_colorBStart;
	short m_fontSizeStart;
	short m_leftRegionStart;
	short m_topRegionStart;
	short m_widthRegionStart;
	short m_heightRegionStart;
	unsigned long m_endClockValue;
	unsigned char m_colorREnd;
	unsigned char m_colorGEnd;
	unsigned char m_colorBEnd;
	short m_fontSizeEnd;
	short m_leftRegionEnd;
	short m_topRegionEnd;
	short m_widthRegionEnd;
	short m_heightRegionEnd;
  BOOL m_showText;
};

class HotspotInfo
{
public:
	HotspotInfo();
	HotspotInfo(DWORD id);

	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:
	short m_hotSpotID;
	HotSpotModeType m_hotSpotMode;
	ImageInfo m_imageInfo;
	AnimationInfo m_animationInfo;
	CharacterContext m_characterInfo;
	short m_leftRect;
	short m_rightRect;
	short m_topRect;
	short m_bottomRect;
	short m_hoverScript;
	short m_unHoverScript;
	CStdString m_feedbackString;
	short m_clickTrigger;
	short m_interactionCount;
	StdListClass<InteractionType> m_interactionType;     
	StdListClass<int> m_interactionSubType;
	StdListClass<CStdString> m_interactionDescription; 
	StdListClass<int> m_interactionTriggerScript;         
	StdListClass<bool> m_interactionOptionIsEnabled;
	StdListClass<short> m_interactionFileSet;
	bool m_transformCursor;
};

class KeyboardTrigger
{
public:
	KeyboardTrigger();
	KeyboardTrigger(DWORD id);
  BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:
	short m_keyID;
	unsigned char m_keyCode;
	short m_triggerScrript;
	bool m_triggerIsEnabled;
};

class ItemDefinition
{
public:
	ItemDefinition();
	ItemDefinition(DWORD id,LPCTSTR fileName);

	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:	
	short m_itemID;
	CStdString m_iconFileName;
	short m_hoverScript;
	CStdString m_feedbackString;
	short m_interactionCount;
	StdListClass<InteractionType> m_interactionType;     
	StdListClass<int> m_interactionSubType;
	StdListClass<CStdString> m_interactionDescription; 
	StdListClass<int> m_interactionTriggerScript;         
	StdListClass<bool> m_interactionOptionIsEnabled;
	StdListClass<short> m_interactionFileSet;
	bool m_itemIsStashed;
};

class CameraDefinition
{
public:
	CameraDefinition();
	CameraDefinition(DWORD id);
  BOOL SaveToFile(HANDLE& hFile);	
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:	
	short m_sceneID;
	bool m_cameraIsFrozen;
	bool m_cameraIsEnabled;
  LayerType m_layer;
	bool m_sceneIsInitialized;
	bool m_applyColorFilter;
	bool m_applyTrasparency;
	unsigned long m_startClockValue;
	unsigned char m_colorHStart;
	unsigned char m_colorLStart;
  unsigned char	m_colorSStart;
	unsigned char m_transparencyStart;
	unsigned long m_endClockValue;
	unsigned char m_colorHEnd;
	unsigned char m_colorLEnd;
	unsigned char m_colorSEnd;
	unsigned char m_transparencyEnd;
};

class SceneDefinition
{
public:
	SceneDefinition();
	SceneDefinition(DWORD id);

	BOOL SaveToFile(HANDLE& hFile);
	BOOL ReadFromFile(HANDLE& hFile);
	
//Attributes:	
	short m_sceneID;
	bool  m_sceneIsNavigable;
  short m_filesetID;
	short m_entranceScript;	
	short m_exitScript;
	short m_activeText;

	bool m_displayInventory;
	short m_leftInventoryDisplay;
	short m_topInventoryDisplay;
	short m_widthInventoryDisplay;
	short m_heightInventoryDisplay;

	short m_bgMusicCode;       //music script ID
  short m_skyID;             //sky ID
	StagingInfo stage;

	short m_imageCount;
	StdListClass<ImageInfo> m_images;

	short m_animationCount;
	StdListClass<AnimationInfo> m_animations;

	short m_characterCount;
	StdListClass<CharacterContext> m_sceneCharacters;

	short m_sfxCount;
	StdListClass<SFXInfo> m_sfx;

	short m_textOverlayCount;
  StdListClass<TextDisplay> m_textOverlays;

	short m_clickCount;
	StdListClass<HotspotInfo> m_clickSpots;

	short m_keyCount;
	StdListClass<KeyboardTrigger> m_keys;
};

class World
{	
public:
	World();
	World(World& world)
	{
		*this = world;
	}
	World& operator = (const World& world)
	{
    m_clockValue = world.m_clockValue;
	  m_clockIsPowered = world.m_clockIsPowered;

	  m_bgMusicCount = world.m_bgMusicCount;
	  m_bgMusicScript = world.m_bgMusicScript;

	  m_bgMusicFileCount = world.m_bgMusicFileCount;
	  m_bgMusicSample = world.m_bgMusicSample;

    m_numberOfCharacters = world.m_numberOfCharacters;
	  m_characters = world.m_characters;

	  m_numberOfScenes = world.m_numberOfScenes;
	  m_scenes = world.m_scenes;

	  m_numberOfSkies = world.m_numberOfSkies;
	  m_skies = world.m_skies;

	  m_inventorySize = world.m_inventorySize;
	  m_inventory = world.m_inventory;

	  m_cameraCount = world.m_cameraCount;
	  m_camera = world.m_camera;

    m_recordCount = world.m_recordCount;
	  m_trackID = world.m_trackID;
	  m_trackRecord = world.m_trackRecord; 

		for (int i = 0; i < INTERACTIVE_SCENE_COUNT; i++)
		{
			m_interactiveScene[i] = world.m_interactiveScene[i];
		}
		for (i = 0; i < TIME_COUNT; i++)
		{
			m_timedScript[i] = world.m_timedScript[i];
		}
		for (i = 0; i < TIME_COUNT; i++)
		{
			m_timerValue[i] = world.m_timerValue[i];
		}
	   m_currentBGMusic = world.m_currentBGMusic;
	   m_previousBGMusic = world.m_previousBGMusic;
		 return *this;
	}

	BOOL SaveToFile(DWORD& key,HANDLE& hFile);
	BOOL ReadFromFile(DWORD& key,HANDLE& hFile);

	unsigned long m_clockValue;
	bool m_clockIsPowered;

	short m_bgMusicCount;
	StdListClass<MusicScript> m_bgMusicScript;

	short m_bgMusicFileCount;
	StdListClass<MusicSample> m_bgMusicSample;

  short m_numberOfCharacters;
	StdListClass<CharacterInfo> m_characters;

	short m_numberOfScenes;
	StdListClass<SceneDefinition> m_scenes;

	short m_numberOfSkies;
	StdListClass<SkyDefinition> m_skies;

	short m_inventorySize;
	StdListClass<ItemDefinition> m_inventory;

	short m_cameraCount;
	StdListClass<CameraDefinition> m_camera;

  short m_recordCount;
	StdListClass<short> m_trackID;
	StdListClass<long> m_trackRecord; 

	InteractiveSceneType m_interactiveScene[INTERACTIVE_SCENE_COUNT];
  short m_timedScript[TIME_COUNT];
	short m_timerValue[TIME_COUNT];

	short m_currentBGMusic;
	short m_previousBGMusic;
};

#endif //ENGINE_CLASSES