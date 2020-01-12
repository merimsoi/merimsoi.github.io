#include "stdafx.h"
#include "engineClasses.h"
#include "basic.h"

MusicSample::MusicSample()
{
	m_sampleID = 0;		
	m_fileName = "";
	m_startSample = 0;
	m_endSample = 0;
}

MusicSample::MusicSample(DWORD id,LPCTSTR fileName)
{
	m_sampleID = id;		
	m_fileName = fileName;
	m_startSample = 0;
	m_endSample = 0;
}

BOOL MusicSample::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		retVal = WriteFile(hFile, 
						          (const void*)&m_sampleID,
						           sizeof(m_sampleID), 
  										 &dwBytesWritten,
											 NULL); 
	}

	int fileNameLen = strlen(m_fileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&fileNameLen,
											 sizeof(fileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_fileName.operator PCTSTR() ,
											fileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)&m_startSample,
											sizeof(m_startSample), 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)&m_endSample,
											sizeof(m_endSample), 
											&dwBytesWritten,
											NULL); 
	}

	return retVal;
}

BOOL MusicSample::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&m_sampleID,
			                sizeof(m_sampleID), 
			                &dwBytesRead,
			                NULL); 
	}

	int fileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&fileNameLen,
			                sizeof(fileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											fileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_fileName = tempBuff;
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&m_startSample,
											sizeof(m_startSample), 
											&dwBytesRead,
											NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
			               (void*)&m_endSample,
			                sizeof(m_endSample), 
			                &dwBytesRead,
			                NULL); 
	}

	return retVal;
}


MusicScript::MusicScript()
{
	m_scriptID = 0;
	m_commandCount = 0;
	m_loopStart = 0;
	m_loopEnd = 0;
	m_currentCommand = 0;
	m_command.Clear();
	m_sampleID.Clear();
  m_repeatCommand.Clear();
	m_waitForCommandFinish.Clear();
	m_commandStartTime.Clear();
	m_commandEndTime.Clear();
	m_obeyCommand.Clear();
}

MusicScript::MusicScript(DWORD id)
{
	m_scriptID = id;
	m_commandCount = 0;
	m_loopStart = 0;
	m_loopEnd = 0;
	m_currentCommand = 0;

	m_command.Clear();
	m_sampleID.Clear();
  m_repeatCommand.Clear();
	m_waitForCommandFinish.Clear();
	m_commandStartTime.Clear();
	m_commandEndTime.Clear();
	m_obeyCommand.Clear();
}

BOOL MusicScript::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)&m_scriptID,
											sizeof(m_scriptID), 
											&dwBytesWritten,
											NULL); 
	}


	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)&m_commandCount,
											sizeof(m_commandCount), 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
												(const void*)&m_loopStart,
												sizeof(m_loopStart), 
												&dwBytesWritten,
												NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)&m_loopEnd,
											sizeof(m_loopEnd), 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)&m_currentCommand,
											sizeof(m_currentCommand), 
											&dwBytesWritten,
											NULL); 
	}

	m_command.ScanInit(DIRECTION_FORWARD);
	if (retVal)
	{
		while(m_command.HasMoreElements())
		{
			MusicCommandType& musicCommand =	m_command.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&musicCommand  ,
								          sizeof(musicCommand), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_sampleID.ScanInit(DIRECTION_FORWARD);
		while(m_sampleID.HasMoreElements())
		{
			short& sampleId =	m_sampleID.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&sampleId,
								          sizeof(sampleId), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_repeatCommand.ScanInit(DIRECTION_FORWARD);
		while(m_repeatCommand.HasMoreElements())
		{
			short& repeatCommand =	m_repeatCommand.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&repeatCommand,
								          sizeof(repeatCommand), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_waitForCommandFinish.ScanInit(DIRECTION_FORWARD);
		while(m_waitForCommandFinish.HasMoreElements())
		{
			bool& isWait =	m_waitForCommandFinish.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&isWait,
								          sizeof(isWait), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_commandStartTime.ScanInit(DIRECTION_FORWARD);
		while(m_commandStartTime.HasMoreElements())
		{
			unsigned long& commandStartTime =	m_commandStartTime.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&commandStartTime,
								          sizeof(commandStartTime), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_commandEndTime.ScanInit(DIRECTION_FORWARD);
		while(m_commandEndTime.HasMoreElements())
		{
			unsigned long& commandEndTime =	m_commandEndTime.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&commandEndTime,
								          sizeof(commandEndTime), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_obeyCommand.ScanInit(DIRECTION_FORWARD);
		while(m_obeyCommand.HasMoreElements())
		{
			unsigned long& obeyCommand =	m_obeyCommand.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&obeyCommand,
								          sizeof(obeyCommand), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	return retVal;
}

BOOL MusicScript::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&m_scriptID,
											sizeof(m_scriptID), 
											&dwBytesRead,
											NULL); 
	}


	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&m_commandCount,
											sizeof(m_commandCount), 
											&dwBytesRead,
											NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&m_loopStart,
											sizeof(m_loopStart), 
											&dwBytesRead,
											NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&m_loopEnd,
											sizeof(m_loopEnd), 
											&dwBytesRead,
											NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
							(void*)&m_currentCommand,
							sizeof(m_currentCommand), 
							&dwBytesRead,
							NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_commandCount; i++)
		{
			MusicCommandType musicCommand; 
			retVal = ReadFile(hFile, 
												(void*)&musicCommand,
												sizeof(musicCommand), 
												&dwBytesRead,
												NULL); 
			m_command.PushBack(musicCommand);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_commandCount; i++)
		{
			short sampleId; 
			retVal = ReadFile(hFile, 
												(void*)&sampleId,
												sizeof(sampleId), 
												&dwBytesRead,
												NULL); 
			m_sampleID.PushBack(sampleId);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_commandCount; i++)
		{
			short repeatCommand;
			retVal = ReadFile(hFile, 
												(void*)&repeatCommand,
												sizeof(repeatCommand), 
												&dwBytesRead,
												NULL); 
			m_repeatCommand.PushBack(repeatCommand);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_commandCount; i++)
		{
			bool isWait;
			retVal = ReadFile(hFile, 
												(void*)&isWait,
												sizeof(isWait), 
												&dwBytesRead,
												NULL); 
			m_waitForCommandFinish.PushBack(isWait);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_commandCount; i++)
		{
			unsigned long commandStartTime; 
			retVal = ReadFile(hFile, 
												(void*)&commandStartTime,
												sizeof(commandStartTime), 
												&dwBytesRead,
												NULL); 
			m_commandStartTime.PushBack(commandStartTime);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_commandCount; i++)
		{
			unsigned long commandEndTime;
			retVal = ReadFile(hFile, 
												(void*)&commandEndTime,
												sizeof(commandEndTime), 
												&dwBytesRead,
												NULL); 
			m_commandEndTime.PushBack(commandEndTime);
		}
	}
		
	if (retVal)
	{
		for (int i = 0; i < m_commandCount; i++)
		{
			unsigned long obeyCommand;
			retVal = ReadFile(hFile, 
												(void*)&obeyCommand,
												sizeof(obeyCommand), 
												&dwBytesRead,
												NULL); 
			m_obeyCommand.PushBack(obeyCommand);
		}
	}	

	return retVal;
}

SkyDefinition::SkyDefinition()
{
	m_skyID = 0;
	m_fileName = "";
	m_width = 0;
	m_height = 0;
	m_left = 0;
	m_top = 0;
  m_frameCount = 0;
	m_currentFrame = 0;
	m_currentFrameClockValue = 0;
	m_frameClockInterval = 0;
}

SkyDefinition::SkyDefinition(DWORD id,LPCTSTR fileName)
{
	m_skyID = id;
	m_fileName = fileName;
	m_width = 0;
	m_height = 0;
	m_left = 0;
	m_top = 0;
  m_frameCount = 0;
	m_currentFrame = 0;
	m_currentFrameClockValue = 0;
	m_frameClockInterval = 0;
}

BOOL SkyDefinition::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_skyID,
							          sizeof(m_skyID), 
                        &dwBytesWritten,
							          NULL); 
	}

	int fileNameLen = strlen(m_fileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&fileNameLen,
											 sizeof(fileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_fileName.operator PCTSTR() ,
											fileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_width,
							          sizeof(m_width), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_height,
							          sizeof(m_height), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_left,
							          sizeof(m_left), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_top,
							          sizeof(m_top), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_frameCount,
							          sizeof(m_frameCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_currentFrame,
							          sizeof(m_currentFrame), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_currentFrameClockValue,
							          sizeof(m_currentFrameClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_frameClockInterval,
							          sizeof(m_frameClockInterval), 
                        &dwBytesWritten,
							          NULL); 
	}


	return retVal;
}

BOOL SkyDefinition::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                 (void*)&m_skyID,
							         sizeof(m_skyID), 
                       &dwBytesRead,
							         NULL); 
	}

	int fileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&fileNameLen,
			                sizeof(fileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											fileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_fileName = tempBuff;
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_width,
							         sizeof(m_width), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_height,
							         sizeof(m_height), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_left,
							         sizeof(m_left), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_top,
							         sizeof(m_top), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_frameCount,
							         sizeof(m_frameCount), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_currentFrame,
							         sizeof(m_currentFrame), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_currentFrameClockValue,
							         sizeof(m_currentFrameClockValue), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_frameClockInterval,
							        sizeof(m_frameClockInterval), 
                      &dwBytesRead,
							        NULL); 
	}


	return retVal;
}


StagingInfo::StagingInfo()
{
	m_imageFileName = "";
	m_widthStart = 0;
	m_heightStart = 0;
	m_leftStart = 0;
	m_topStart = 0;
	m_startClockValue = 0;
	m_widthEnd = 0;
	m_heightEnd = 0;
	m_leftEnd = 0;
	m_topEnd = 0;
	m_endClockValue = 0;
	m_alphaFileName = "";
	m_leftAlpha = 0;
	m_topAlpha = 0;
	m_mapFileName = "";
	m_mapColorCount = 0;
	for (int i = 0; i < ALTITUDE_MAP_COUNT ; i++)
	{
		m_mapAltitudeIndex[i] = 0;
	}
	
	m_mapLeft = 0;
	m_mapTop = 0;
	m_mapHeight = 0;
	m_mapWidth = 0;
	m_lightingMode = LT_OFF;
	m_lighterFileName = "";
  m_lightAngleX = 0;
	m_lightAngleY = 0;
	m_lightAngleZ = 0;
	m_lightR = 0;
	m_lightG = 0;
	m_lightB = 0;
	m_cameraAngle = 0;
	m_cameraHeight = 0;
}

BOOL StagingInfo::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;

	int imageFileNameLen = strlen(m_imageFileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&imageFileNameLen,
											 sizeof(imageFileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_imageFileName.operator PCTSTR() ,
											imageFileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_widthStart,
							          sizeof(m_widthStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_heightStart,
							          sizeof(m_heightStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftStart,
							          sizeof(m_leftStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topStart,
							          sizeof(m_topStart), 
                        &dwBytesWritten,
							          NULL); 
	}
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_startClockValue,
							          sizeof(m_startClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_widthEnd,
							          sizeof(m_widthEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_heightEnd,
							          sizeof(m_heightEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftEnd,
							          sizeof(m_leftEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topEnd,
							          sizeof(m_topEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_endClockValue,
							          sizeof(m_endClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	int alphaFileNameLen = strlen(m_alphaFileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&alphaFileNameLen,
											 sizeof(alphaFileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_alphaFileName.operator PCTSTR() ,
											alphaFileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftAlpha,
							          sizeof(m_leftAlpha), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topAlpha,
							          sizeof(m_topAlpha), 
                        &dwBytesWritten,
							          NULL); 
	}

	int mapFileNameLen = strlen(m_mapFileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&mapFileNameLen,
											 sizeof(mapFileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_mapFileName.operator PCTSTR() ,
											mapFileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_mapColorCount,
							          sizeof(m_mapColorCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_mapAltitudeIndex,
							          sizeof(m_mapAltitudeIndex), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_mapLeft,
							          sizeof(m_mapLeft), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_mapTop,
							          sizeof(m_mapTop), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_mapHeight,
							          sizeof(m_mapHeight), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_mapWidth,
							          sizeof(m_mapWidth), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_lightingMode,
							          sizeof(m_lightingMode), 
                        &dwBytesWritten,
							          NULL); 
	}

	int lighterFileNameLen = strlen(m_lighterFileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&lighterFileNameLen,
											 sizeof(lighterFileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_lighterFileName.operator PCTSTR() ,
											lighterFileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_lightR,
							          sizeof(m_lightR), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_lightG,
							          sizeof(m_lightG), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_lightB,
							          sizeof(m_lightB), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_cameraAngle,
							          sizeof(m_cameraAngle), 
                        &dwBytesWritten,
							          NULL); 
	}
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_cameraHeight,
							          sizeof(m_cameraHeight), 
                        &dwBytesWritten,
							          NULL); 
	}

	return retVal;
}

BOOL StagingInfo::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	char tempBuff[TEMP_BUFF_LEN];

	int imageFileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&imageFileNameLen,
			                sizeof(imageFileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											imageFileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_imageFileName = tempBuff;
	}


	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_widthStart,
							         sizeof(m_widthStart), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_heightStart,
							        sizeof(m_heightStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftStart,
							         sizeof(m_leftStart), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topStart,
							         sizeof(m_topStart), 
                       &dwBytesRead,
							         NULL); 
	}
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_startClockValue,
							        sizeof(m_startClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_widthEnd,
							        sizeof(m_widthEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_heightEnd,
							         sizeof(m_heightEnd), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftEnd,
							         sizeof(m_leftEnd), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topEnd,
							         sizeof(m_topEnd), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_endClockValue,
							         sizeof(m_endClockValue), 
                       &dwBytesRead,
							         NULL); 
	}

	int alphaFileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&alphaFileNameLen,
			                sizeof(alphaFileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											alphaFileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_alphaFileName = tempBuff;
	}


	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftAlpha,
							        sizeof(m_leftAlpha), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topAlpha,
							         sizeof(m_topAlpha), 
                       &dwBytesRead,
							         NULL); 
	}

	int mapFileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&mapFileNameLen,
			                sizeof(mapFileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											mapFileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_mapFileName = tempBuff;
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_mapColorCount,
							         sizeof(m_mapColorCount), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_mapAltitudeIndex,
							        sizeof(m_mapAltitudeIndex), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_mapLeft,
							         sizeof(m_mapLeft), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_mapTop,
							         sizeof(m_mapTop), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_mapHeight,
							         sizeof(m_mapHeight), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_mapWidth,
							         sizeof(m_mapWidth), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_lightingMode,
							         sizeof(m_lightingMode), 
                       &dwBytesRead,
							         NULL); 
	}


	int lighterFileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&lighterFileNameLen,
			                sizeof(lighterFileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											lighterFileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_lighterFileName = tempBuff;
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_lightR,
							         sizeof(m_lightR), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_lightG,
							         sizeof(m_lightG), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_lightB,
							         sizeof(m_lightB), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_cameraAngle,
							        sizeof(m_cameraAngle), 
                      &dwBytesRead,
							        NULL); 
	}
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_cameraHeight,
							         sizeof(m_cameraHeight), 
                       &dwBytesRead,
							         NULL); 
	}

	return retVal;
}

ImageInfo::ImageInfo()
{
  m_imageID = 0;
	m_fileName = "";
	m_widthStart = 0;
	m_heightStart = 0;
	m_leftStart = 0;
	m_topStart = 0;
	m_zStart = 0;
	m_zEnd = 0;
	m_startClockValue = 0;
	m_widthEnd = 0;
	m_heightEnd = 0;
	m_leftEnd = 0;
	m_topEnd = 0;
	m_endClockValue = 0;
	m_frameCount = 0;
	m_currentFrame = 0;
	m_frameInterval = 0;
	m_currentFrameClockValue = 0;
	m_currentFrameClockInterval = 0;
	m_loopsRemaining = 0;
	m_aplhaFileName = "";
	m_leftAlpha = 0;
	m_topAlpha = 0;
	m_imageIsVisible = FALSE;
}

ImageInfo::ImageInfo(DWORD id,LPCTSTR fileName)
{
  m_imageID = id;
	m_fileName = fileName;
	m_widthStart = 0;
	m_heightStart = 0;
	m_leftStart = 0;
	m_topStart = 0;
	m_zStart = 0;
	m_zEnd = 0;
	m_startClockValue = 0;
	m_widthEnd = 0;
	m_heightEnd = 0;
	m_leftEnd = 0;
	m_topEnd = 0;
	m_endClockValue = 0;
	m_frameCount = 0;
	m_currentFrame = 0;
	m_frameInterval = 0;
	m_currentFrameClockValue = 0;
	m_currentFrameClockInterval = 0;
	m_loopsRemaining = 0;
	m_aplhaFileName = "";
	m_leftAlpha = 0;
	m_topAlpha = 0;
	m_imageIsVisible = FALSE;
}

BOOL ImageInfo::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_imageID,
							          sizeof(m_imageID), 
                        &dwBytesWritten,
							          NULL); 
	}

	int fileNameLen = strlen(m_fileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&fileNameLen,
											 sizeof(fileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_fileName.operator PCTSTR() ,
											fileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_widthStart,
							          sizeof(m_widthStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_heightStart,
							          sizeof(m_heightStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftStart,
							          sizeof(m_leftStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topStart,
							          sizeof(m_topStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_zStart,
							          sizeof(m_zStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_zEnd,
							          sizeof(m_zEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_startClockValue,
							          sizeof(m_startClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_frameInterval,
							          sizeof(m_frameInterval), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_widthEnd,
							          sizeof(m_widthEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_heightEnd,
							          sizeof(m_heightEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftEnd,
							          sizeof(m_leftEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topEnd,
							          sizeof(m_topEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_endClockValue,
							          sizeof(m_endClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_frameCount,
							          sizeof(m_frameCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_currentFrame,
							          sizeof(m_currentFrame), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_currentFrameClockValue,
							          sizeof(m_currentFrameClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_currentFrameClockInterval,
							          sizeof(m_currentFrameClockInterval), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_loopsRemaining,
							          sizeof(m_loopsRemaining), 
                        &dwBytesWritten,
							          NULL); 
	}


	int alphaFileNameLen = strlen(m_aplhaFileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&alphaFileNameLen,
											 sizeof(alphaFileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_aplhaFileName.operator PCTSTR() ,
											alphaFileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftAlpha,
							          sizeof(m_leftAlpha), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topAlpha,
							          sizeof(m_topAlpha), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_imageIsVisible,
							          sizeof(m_imageIsVisible), 
                        &dwBytesWritten,
							          NULL); 
	}

	return retVal;
}

BOOL ImageInfo::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	char tempBuff[TEMP_BUFF_LEN];

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_imageID,
							        sizeof(m_imageID), 
                      &dwBytesRead,
							        NULL); 
	}

	int fileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&fileNameLen,
			                sizeof(fileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											fileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_fileName = tempBuff;
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_widthStart,
							        sizeof(m_widthStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_heightStart,
							        sizeof(m_heightStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftStart,
							        sizeof(m_leftStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topStart,
							        sizeof(m_topStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_zStart,
							        sizeof(m_zStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_zEnd,
							        sizeof(m_zEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_startClockValue,
							        sizeof(m_startClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_frameInterval,
							        sizeof(m_frameInterval), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_widthEnd,
							        sizeof(m_widthEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_heightEnd,
							        sizeof(m_heightEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftEnd,
							        sizeof(m_leftEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topEnd,
							        sizeof(m_topEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_endClockValue,
							        sizeof(m_endClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_frameCount,
							        sizeof(m_frameCount), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_currentFrame,
							        sizeof(m_currentFrame), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_currentFrameClockValue,
							        sizeof(m_currentFrameClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_currentFrameClockInterval,
							        sizeof(m_currentFrameClockInterval), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_loopsRemaining,
							        sizeof(m_loopsRemaining), 
                      &dwBytesRead,
							        NULL); 
	}

	int alphaFileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&alphaFileNameLen,
			                sizeof(alphaFileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											alphaFileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_aplhaFileName = tempBuff;
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftAlpha,
							        sizeof(m_leftAlpha), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topAlpha,
							        sizeof(m_topAlpha), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_imageIsVisible,
							        sizeof(m_imageIsVisible), 
                      &dwBytesRead,
							        NULL); 
	}

	return retVal;
}


CharacterInfo::CharacterInfo()
{
	m_characterId = 0;
	m_characterName = "";
	m_clipCount = 0;
	m_defaultClip = 0;
	m_fileName.Clear(); 
	m_colorFile.Clear(); 
  m_vertexTable.Clear(); 
  m_typeId.Clear();
	m_frameStart.Clear();
	m_frameEnd.Clear();
	m_framesPerSecond.Clear();
	m_loopCount.Clear();
}

CharacterInfo::CharacterInfo(short characterId,LPCTSTR characterName)
{
	m_characterId = characterId;
	m_characterName = characterName;
	m_clipCount = 0;
	m_defaultClip = 0;
	m_fileName.Clear(); 
	m_colorFile.Clear(); 
  m_vertexTable.Clear(); 
  m_typeId.Clear();
	m_frameStart.Clear();
	m_frameEnd.Clear();
	m_framesPerSecond.Clear();
	m_loopCount.Clear();
}

BOOL CharacterInfo::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;
	DWORD dwBytesWritten;

	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&m_characterId,
											 sizeof(m_characterId), 
  										 &dwBytesWritten,
											 NULL); 
	}


	int characterNameLen = strlen(m_characterName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&characterNameLen,
											 sizeof(characterNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_characterName.operator PCTSTR() ,
											characterNameLen, 
											&dwBytesWritten,
											NULL); 
	}

  if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&m_clipCount,
											 sizeof(m_clipCount), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&m_defaultClip,
											 sizeof(m_defaultClip), 
  										 &dwBytesWritten,
											 NULL); 
	}


	short arrayElementCount = m_fileName.Size();
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&arrayElementCount,
											 sizeof(arrayElementCount), 
  										 &dwBytesWritten,
											 NULL); 
	}

	m_fileName.ScanInit(DIRECTION_FORWARD);
	if (retVal)
	{
		while(m_fileName.HasMoreElements())
		{
			CStdString& fileName =	m_fileName.NextElement();

			int fileNameLen = strlen(fileName.operator PCTSTR());
			if (retVal)
			{
				retVal = WriteFile(hFile, 
													(const void*)&fileNameLen,
													sizeof(fileNameLen), 
													&dwBytesWritten,
													NULL); 
			}
			
			if (retVal)
			{
				retVal = WriteFile(hFile, 
													(const void*)fileName.operator PCTSTR() ,
													fileNameLen, 
													&dwBytesWritten,
													NULL); 
			}		
		}
	}

	if (retVal)
	{
		m_colorFile.ScanInit(DIRECTION_FORWARD);
		while(m_colorFile.HasMoreElements())
		{
			CStdString& colorFile =	m_colorFile.NextElement();

			int colorFileNameLen = strlen(colorFile.operator PCTSTR());
			if (retVal)
			{
				retVal = WriteFile(hFile, 
													(const void*)&colorFileNameLen,
													sizeof(colorFileNameLen), 
													&dwBytesWritten,
													NULL); 
			}
			
			if (retVal)
			{
				retVal = WriteFile(hFile, 
													(const void*)colorFile.operator PCTSTR() ,
													colorFileNameLen, 
													&dwBytesWritten,
													NULL); 
			}		
		}
	}

	if (retVal)
	{
		m_vertexTable.ScanInit(DIRECTION_FORWARD);
		while(m_vertexTable.HasMoreElements())
		{
			CStdString& vertexTable =	m_vertexTable.NextElement();

			int vertexTableLen = strlen(vertexTable.operator PCTSTR());
			if (retVal)
			{
				retVal = WriteFile(hFile, 
													(const void*)&vertexTableLen,
													sizeof(vertexTableLen), 
													&dwBytesWritten,
													NULL); 
			}
			
			if (retVal)
			{
				retVal = WriteFile(hFile, 
													(const void*)vertexTable.operator PCTSTR() ,
													vertexTableLen, 
													&dwBytesWritten,
													NULL); 
			}		
		}
	}

	if (retVal)
	{
		m_typeId.ScanInit(DIRECTION_FORWARD);

		while(m_typeId.HasMoreElements())
		{
			unsigned long& typeId = m_typeId.NextElement();
			retVal = WriteFile(hFile, 
		 										(const void*)&typeId,
												 sizeof(typeId), 
  											 &dwBytesWritten,
												 NULL); 

		}
	} 

	if (retVal)
	{
		m_frameStart.ScanInit(DIRECTION_FORWARD);
		while(m_frameStart.HasMoreElements())
		{
			short& frameStart = m_frameStart.NextElement();
			retVal = WriteFile(hFile, 
		 										(const void*)&frameStart,
												 sizeof(frameStart), 
  											 &dwBytesWritten,
												 NULL); 

		}
	}

	if (retVal)
	{
		m_frameEnd.ScanInit(DIRECTION_FORWARD);
		while(m_frameEnd.HasMoreElements())
		{
			short& frameEnd = m_frameEnd.NextElement();
			retVal = WriteFile(hFile, 
	 											(const void*)&frameEnd,
												 sizeof(frameEnd), 
  											 &dwBytesWritten,
												 NULL); 
		}
	}

	if (retVal)
	{
		m_framesPerSecond.ScanInit(DIRECTION_FORWARD);
		while(m_framesPerSecond.HasMoreElements())
		{
			short& framesPerSecond = m_framesPerSecond.NextElement();
			retVal = WriteFile(hFile, 
	 											(const void*)&framesPerSecond,
												 sizeof(framesPerSecond), 
  											 &dwBytesWritten,
												 NULL); 
		}
	}

	if (retVal)
	{
		m_loopCount.ScanInit(DIRECTION_FORWARD);
		while(m_loopCount.HasMoreElements())
		{
		  short& loopCount = m_loopCount.NextElement();
			retVal = WriteFile(hFile, 
	 											(const void*)&loopCount,
												 sizeof(loopCount), 
  											 &dwBytesWritten,
												 NULL); 
		}
	}

  return retVal;
}

BOOL CharacterInfo::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;
	DWORD dwBytesRead;

	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&m_characterId,
			                sizeof(m_characterId), 
			                &dwBytesRead,
			                NULL); 
	}

	int characterNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&characterNameLen,
			                sizeof(characterNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											characterNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_characterName = tempBuff;
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&m_clipCount,
			                sizeof(m_clipCount), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&m_defaultClip,
			                sizeof(m_defaultClip), 
			                &dwBytesRead,
			                NULL); 
	}

	short arrayElementNumber;

	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&arrayElementNumber,
			                sizeof(arrayElementNumber), 
			                &dwBytesRead,
			                NULL); 
	}


	if (retVal)
	{
		for (int i = 0; i < arrayElementNumber; i++)
		{
			CStdString fileName; 

			int fileNameLen;
			if (retVal)
			{
				retVal = ReadFile(hFile, 
													(void*)&fileNameLen,
													sizeof(fileNameLen), 
													&dwBytesRead,
													NULL); 
			}
			
			if (retVal)
			{
				char tempBuff[TEMP_BUFF_LEN];
				retVal = ReadFile(hFile, 
													(void*)tempBuff,
													fileNameLen, 
													&dwBytesRead,
													NULL); 
				
				tempBuff[dwBytesRead] = 0;
				fileName = tempBuff;
			}

			m_fileName.PushBack(fileName);
		}
	}


  if (retVal)
	{
		for (int i = 0; i < arrayElementNumber; i++)
		{
			CStdString colorFileName; 

			int colorFileNameLen;
			if (retVal)
			{
				retVal = ReadFile(hFile, 
													(void*)&colorFileNameLen,
													sizeof(colorFileNameLen), 
													&dwBytesRead,
													NULL); 
			}
			
			if (retVal)
			{
				char tempBuff[TEMP_BUFF_LEN];
				retVal = ReadFile(hFile, 
													(void*)tempBuff,
													colorFileNameLen, 
													&dwBytesRead,
													NULL); 
				
				tempBuff[dwBytesRead] = 0;
				colorFileName = tempBuff;
			}

			m_colorFile.PushBack(colorFileName);
		}
	}

  if (retVal)
	{
		for (int i = 0; i < arrayElementNumber; i++)
		{
			CStdString vertexTable; 

			int vertexTableLen;
			if (retVal)
			{
				retVal = ReadFile(hFile, 
													(void*)&vertexTableLen,
													sizeof(vertexTableLen), 
													&dwBytesRead,
													NULL); 
			}
			
			if (retVal)
			{
				char tempBuff[TEMP_BUFF_LEN];
				retVal = ReadFile(hFile, 
													(void*)tempBuff,
													vertexTableLen, 
													&dwBytesRead,
													NULL); 
				
				tempBuff[dwBytesRead] = 0;
				vertexTable = tempBuff;
			}

			m_vertexTable.PushBack(vertexTable);
		}
	}


	if (retVal)
	{
		for (int i = 0; i < arrayElementNumber; i++)
		{
			unsigned long typeId;
			retVal = ReadFile(hFile, 
						           (void*)&typeId ,
										    sizeof(typeId), 
			                  &dwBytesRead,
										    NULL); 
			m_typeId.PushBack(typeId);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < arrayElementNumber; i++)
		{
			short frameStart;
			retVal = ReadFile(hFile, 
						           (void*)&frameStart ,
										    sizeof(frameStart), 
			                  &dwBytesRead,
										    NULL); 
			m_frameStart.PushBack(frameStart);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < arrayElementNumber; i++)
		{
			short frameEnd;
			retVal = ReadFile(hFile, 
						           (void*)&frameEnd ,
										    sizeof(frameEnd), 
			                  &dwBytesRead,
										    NULL); 
			m_frameEnd.PushBack(frameEnd);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < arrayElementNumber; i++)
		{
			short framesPerSecond;
			retVal = ReadFile(hFile, 
						           (void*)&framesPerSecond ,
										    sizeof(framesPerSecond), 
			                  &dwBytesRead,
										    NULL); 
			m_framesPerSecond.PushBack(framesPerSecond);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < arrayElementNumber; i++)
		{
			short loopCount;
			retVal = ReadFile(hFile, 
						           (void*)&loopCount ,
										    sizeof(loopCount), 
			                  &dwBytesRead,
										    NULL); 
			m_loopCount.PushBack(loopCount);
		}
	}

	return retVal;
}

CharacterContext::CharacterContext()
{
	m_characterId = 0;
	m_characterIsVisible = false;
	m_adjustForLight = false;
	m_nodeCount = 0;
  m_typeId.Clear();
  m_transX.Clear();
  m_transY.Clear();
  m_transZ.Clear();
  m_clockValue.Clear();
	m_currentFrame = 0;
	m_nextFrame = 0;
	m_currentFrameClockValue = 0;
	m_nextFrameClockValue = 0;
}

CharacterContext::CharacterContext(DWORD id)
{
	m_characterId = id;
	m_characterIsVisible = false;
	m_adjustForLight = false;
	m_nodeCount = 0;
  m_typeId.Clear();
  m_transX.Clear();
  m_transY.Clear();
  m_transZ.Clear();
  m_clockValue.Clear();
	m_currentFrame = 0;
	m_nextFrame = 0;
	m_currentFrameClockValue = 0;
	m_nextFrameClockValue = 0;
}

BOOL CharacterContext::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_characterId,
							          sizeof(m_characterId), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_characterIsVisible,
							          sizeof(m_characterIsVisible), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_adjustForLight,
							          sizeof(m_adjustForLight), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_nodeCount,
							          sizeof(m_nodeCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	m_typeId.ScanInit(DIRECTION_FORWARD);
	if (retVal)
	{
		while(m_typeId.HasMoreElements())
		{
			unsigned long& typeId =	m_typeId.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&typeId,
								          sizeof(typeId), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_transX.ScanInit(DIRECTION_FORWARD);
		while(m_transX.HasMoreElements())
		{
			long& transX =	m_transX.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&transX,
								          sizeof(transX), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_transY.ScanInit(DIRECTION_FORWARD);
		while(m_transY.HasMoreElements())
		{
			long& transY =	m_transY.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&transY,
								          sizeof(transY), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_transZ.ScanInit(DIRECTION_FORWARD);
		while(m_transZ.HasMoreElements())
		{
			long& transZ =	m_transZ.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&transZ,
								          sizeof(transZ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		m_clockValue.ScanInit(DIRECTION_FORWARD);
		while(m_clockValue.HasMoreElements())
		{
			unsigned long& clockValue =	m_clockValue.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&clockValue,
								          sizeof(clockValue), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_currentFrame,
							          sizeof(m_currentFrame), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_nextFrame,
							          sizeof(m_nextFrame), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_currentFrameClockValue,
							          sizeof(m_currentFrameClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_nextFrameClockValue,
							          sizeof(m_nextFrameClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	return retVal;
}

BOOL CharacterContext::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_characterId,
							        sizeof(m_characterId), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_characterIsVisible,
							        sizeof(m_characterIsVisible), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_adjustForLight,
							        sizeof(m_adjustForLight), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_nodeCount,
							        sizeof(m_nodeCount), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_nodeCount; i++)
		{
			unsigned long typeId; 
			retVal = ReadFile(hFile, 
												(void*)&typeId,
												sizeof(typeId), 
												&dwBytesRead,
												NULL); 
			m_typeId.PushBack(typeId);
		}
	}

  if (retVal)
	{
		for (int i = 0; i < m_nodeCount; i++)
		{
			long transX; 
			retVal = ReadFile(hFile, 
												(void*)&transX,
												sizeof(transX), 
												&dwBytesRead,
												NULL); 
			m_transX.PushBack(transX);
		}
	}

  if (retVal)
	{
		for (int i = 0; i < m_nodeCount; i++)
		{
			long transY; 
			retVal = ReadFile(hFile, 
												(void*)&transY,
												sizeof(transY), 
												&dwBytesRead,
												NULL); 
			m_transY.PushBack(transY);
		}
	}

  if (retVal)
	{
		for (int i = 0; i < m_nodeCount; i++)
		{
			long transZ; 
			retVal = ReadFile(hFile, 
												(void*)&transZ,
												sizeof(transZ), 
												&dwBytesRead,
												NULL); 
			m_transZ.PushBack(transZ);
		}
	}

  if (retVal)
	{
		for (int i = 0; i < m_nodeCount; i++)
		{
			unsigned long clockValue; 
			retVal = ReadFile(hFile, 
												(void*)&clockValue,
												sizeof(clockValue), 
												&dwBytesRead,
												NULL); 
			m_clockValue.PushBack(clockValue);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_currentFrame,
							        sizeof(m_currentFrame), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_nextFrame,
							        sizeof(m_nextFrame), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_currentFrameClockValue,
							        sizeof(m_currentFrameClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_nextFrameClockValue,
							        sizeof(m_nextFrameClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	return retVal;
}

AnimationInfo::AnimationInfo()
{
	m_animationID = 0;
	m_fileNameVideo = "";
	m_fileNameAudio = "";
	m_widthStart = 0;
	m_heightStart = 0;
	m_leftStart = 0;
  m_topStart = 0;
	m_zStart = 0;
	m_startClockValue = 0;
	m_widthEnd = 0;
	m_heightEnd = 0;
	m_leftEnd = 0;
	m_topEnd = 0;
	m_zEnd = 0;
	m_endClockValue = 0;
  m_playStartValue = 0;
	m_startFrame = 0;
	m_currentFrame = 0;
	m_frameExparation = 0;
	m_endFrame = 0;
	m_loopsRemaining = 0;
	m_volStartClock = 0;
	m_volStart = 0;
	m_volEndClock = 0;
	m_volEnd = 0;
  m_doVideo = FALSE;
	m_doAudio = FALSE;
}

AnimationInfo::AnimationInfo(DWORD id,LPCTSTR fileName)
{
	m_animationID = id;
	m_fileNameVideo = fileName;
	m_fileNameAudio = "";
	m_widthStart = 0;
	m_heightStart = 0;
	m_leftStart = 0;
  m_topStart = 0;
	m_zStart = 0;
	m_startClockValue = 0;
	m_widthEnd = 0;
	m_heightEnd = 0;
	m_leftEnd = 0;
	m_topEnd = 0;
	m_zEnd = 0;
	m_endClockValue = 0;
  m_playStartValue = 0;
	m_startFrame = 0;
	m_currentFrame = 0;
	m_frameExparation = 0;
	m_endFrame = 0;
	m_loopsRemaining = 0;
	m_volStartClock = 0;
	m_volStart = 0;
	m_volEndClock = 0;
	m_volEnd = 0;
  m_doVideo = FALSE;
	m_doAudio = FALSE;
}


BOOL AnimationInfo::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;
	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_animationID,
							          sizeof(m_animationID), 
                        &dwBytesWritten,
							          NULL); 
	}

	int fileNameVideoLen = strlen(m_fileNameVideo.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&fileNameVideoLen,
											 sizeof(fileNameVideoLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_fileNameVideo.operator PCTSTR() ,
											fileNameVideoLen, 
											&dwBytesWritten,
											NULL); 
	}

	int fileNameAudioLen = strlen(m_fileNameAudio.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&fileNameAudioLen,
											 sizeof(fileNameAudioLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_fileNameAudio.operator PCTSTR() ,
											fileNameAudioLen, 
											&dwBytesWritten,
											NULL); 
	}


	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_widthStart,
							          sizeof(m_widthStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_heightStart,
							          sizeof(m_heightStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftStart,
							          sizeof(m_leftStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topStart,
							          sizeof(m_topStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_zStart,
							          sizeof(m_zStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_startClockValue,
							          sizeof(m_startClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_widthEnd,
							          sizeof(m_widthEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_heightEnd,
							          sizeof(m_heightEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftEnd,
							          sizeof(m_leftEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topEnd,
							          sizeof(m_topEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_zEnd,
							          sizeof(m_zEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_endClockValue,
							          sizeof(m_endClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_playStartValue,
							          sizeof(m_playStartValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_startFrame,
							          sizeof(m_startFrame), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_currentFrame,
							          sizeof(m_currentFrame), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_frameExparation,
							          sizeof(m_frameExparation), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_endFrame,
							          sizeof(m_endFrame), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_loopsRemaining,
							          sizeof(m_loopsRemaining), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_volStartClock,
							          sizeof(m_volStartClock), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_volStart,
							          sizeof(m_volStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_volEndClock,
							          sizeof(m_volEndClock), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_volEnd,
							          sizeof(m_volEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_doVideo,
							          sizeof(m_doVideo), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_doAudio,
							          sizeof(m_doAudio), 
                        &dwBytesWritten,
							          NULL); 
	}

	return retVal;
}

BOOL AnimationInfo::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;
	DWORD dwBytesRead;
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_animationID,
							        sizeof(m_animationID), 
                      &dwBytesRead,
							        NULL); 
	}

	int fileNameVideoLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&fileNameVideoLen,
											sizeof(fileNameVideoLen), 
											&dwBytesRead,
											NULL); 
	}
	
	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											fileNameVideoLen, 
											&dwBytesRead,
											NULL); 
		
		tempBuff[dwBytesRead] = 0;
		m_fileNameVideo = tempBuff;
	}

	int fileNameAudioLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&fileNameAudioLen,
											sizeof(fileNameAudioLen), 
											&dwBytesRead,
											NULL); 
	}
	
	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											fileNameAudioLen, 
											&dwBytesRead,
											NULL); 
		
		tempBuff[dwBytesRead] = 0;
		m_fileNameAudio = tempBuff;
	}


	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_widthStart,
							        sizeof(m_widthStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_heightStart,
							        sizeof(m_heightStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftStart,
							        sizeof(m_leftStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topStart,
							        sizeof(m_topStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_zStart,
							        sizeof(m_zStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_startClockValue,
							        sizeof(m_startClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_widthEnd,
							        sizeof(m_widthEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_heightEnd,
							        sizeof(m_heightEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftEnd,
							        sizeof(m_leftEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topEnd,
							        sizeof(m_topEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_zEnd,
							        sizeof(m_zEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_endClockValue,
							        sizeof(m_endClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_playStartValue,
							        sizeof(m_playStartValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_startFrame,
							        sizeof(m_startFrame), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_currentFrame,
							        sizeof(m_currentFrame), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_frameExparation,
							        sizeof(m_frameExparation), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_endFrame,
							        sizeof(m_endFrame), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_loopsRemaining,
							        sizeof(m_loopsRemaining), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_volStartClock,
							        sizeof(m_volStartClock), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_volStart,
							        sizeof(m_volStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_volEndClock,
							        sizeof(m_volEndClock), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_volEnd,
							        sizeof(m_volEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_doVideo,
							        sizeof(m_doVideo), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_doAudio,
							        sizeof(m_doAudio), 
                      &dwBytesRead,
							        NULL); 
	}

	return retVal;
}

SFXInfo::SFXInfo()
{
	m_sfxID = 0;
	m_fileName = "";
	m_startClockValue = 0;
	m_startPosition = 0;
	m_endPosition = 0;
	m_loopsRemaining = 0;
  m_volStartClock = 0;
	m_volumeStart = 0;
  m_volEndClock = 0;
	m_volumeEnd = 0;
	m_audioIsEnabled = FALSE;
}

SFXInfo::SFXInfo(DWORD id,LPCTSTR fileName)
{
	m_sfxID = id;
	m_fileName = fileName;
	m_startClockValue = 0;
	m_startPosition = 0;
	m_endPosition = 0;
	m_loopsRemaining = 0;
  m_volStartClock = 0;
	m_volumeStart = 0;
  m_volEndClock = 0;
	m_volumeEnd = 0;
	m_audioIsEnabled = FALSE;
}

BOOL SFXInfo::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_sfxID,
							          sizeof(m_sfxID), 
                        &dwBytesWritten,
							          NULL); 
	}

	int fileNameLen = strlen(m_fileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&fileNameLen,
											 sizeof(fileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_fileName.operator PCTSTR() ,
											fileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_startClockValue,
							          sizeof(m_startClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_startPosition,
							          sizeof(m_startPosition), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_endPosition,
							          sizeof(m_endPosition), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_loopsRemaining,
							          sizeof(m_loopsRemaining), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_volStartClock,
							          sizeof(m_volStartClock), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_volumeStart,
							          sizeof(m_volumeStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_volEndClock,
							          sizeof(m_volEndClock), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_volumeEnd,
							          sizeof(m_volumeEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_audioIsEnabled,
							          sizeof(m_audioIsEnabled), 
                        &dwBytesWritten,
							          NULL); 
	}

	return retVal;
}

BOOL SFXInfo::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_sfxID,
							          sizeof(m_sfxID), 
                        &dwBytesRead,
							          NULL); 
	}

	int fileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&fileNameLen,
			                sizeof(fileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											fileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_fileName = tempBuff;
	}


	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_startClockValue,
							          sizeof(m_startClockValue), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_startPosition,
							          sizeof(m_startPosition), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_endPosition,
							          sizeof(m_endPosition), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_loopsRemaining,
							          sizeof(m_loopsRemaining), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_volStartClock,
							          sizeof(m_volStartClock), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_volumeStart,
							          sizeof(m_volumeStart), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_volEndClock,
							          sizeof(m_volEndClock), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                 (void*)&m_volumeEnd,
							         sizeof(m_volumeEnd), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_audioIsEnabled,
							         sizeof(m_audioIsEnabled), 
                       &dwBytesRead,
							         NULL); 
	}

	return retVal;
}


TextDisplay::TextDisplay()
{
	m_textID = 0;
	m_fontName = "";
	m_textType = TXT_STRING;
	m_displayString = "";
	m_startClockValue = 0;
	m_colorRStart = 0;
	m_colorGStart = 0;
	m_colorBStart = 0;
	m_fontSizeStart = 0;
	m_leftRegionStart = 0; 
	m_topRegionStart = 0;
	m_widthRegionStart = 0;
	m_heightRegionStart = 0;
	m_endClockValue = 0;
	m_colorREnd = 0;
	m_colorGEnd = 0;
	m_colorBEnd = 0;
	m_fontSizeEnd = 0;
	m_leftRegionEnd = 0;
	m_topRegionEnd = 0;
	m_widthRegionEnd = 0;
	m_heightRegionEnd = 0;
}

TextDisplay::TextDisplay(DWORD id)
{
	m_textID = id;
	m_fontName = "";
	m_textType = TXT_STRING;
	m_displayString = "";
	m_startClockValue = 0;
	m_colorRStart = 0;
	m_colorGStart = 0;
	m_colorBStart = 0;
	m_fontSizeStart = 0;
	m_leftRegionStart = 0; 
	m_topRegionStart = 0;
	m_widthRegionStart = 0;
	m_heightRegionStart = 0;
	m_endClockValue = 0;
	m_colorREnd = 0;
	m_colorGEnd = 0;
	m_colorBEnd = 0;
	m_fontSizeEnd = 0;
	m_leftRegionEnd = 0;
	m_topRegionEnd = 0;
	m_widthRegionEnd = 0;
	m_heightRegionEnd = 0;
}

BOOL TextDisplay::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_textID,
							          sizeof(m_textID), 
                        &dwBytesWritten,
							          NULL); 
	}

	int fontNameLen = strlen(m_fontName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&fontNameLen,
											 sizeof(fontNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_fontName.operator PCTSTR() ,
											fontNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_textType,
							          sizeof(m_textType), 
                        &dwBytesWritten,
							          NULL); 
	}

	int dispStrLen = strlen(m_displayString.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&dispStrLen,
											 sizeof(dispStrLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_displayString.operator PCTSTR() ,
											dispStrLen, 
											&dwBytesWritten,
											NULL); 
	}


	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_startClockValue,
							          sizeof(m_startClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorRStart,
							          sizeof(m_colorRStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorGStart,
							          sizeof(m_colorGStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorBStart,
							          sizeof(m_colorBStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_fontSizeStart,
							          sizeof(m_fontSizeStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftRegionStart,
							          sizeof(m_leftRegionStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topRegionStart,
							          sizeof(m_topRegionStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_widthRegionStart,
							          sizeof(m_widthRegionStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_heightRegionStart,
							          sizeof(m_heightRegionStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_endClockValue,
							          sizeof(m_endClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorREnd,
							          sizeof(m_colorREnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorGEnd,
							          sizeof(m_colorGEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorBEnd,
							          sizeof(m_colorBEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_fontSizeEnd,
							          sizeof(m_fontSizeEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftRegionEnd,
							          sizeof(m_leftRegionEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topRegionEnd,
							          sizeof(m_topRegionEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_widthRegionEnd,
							          sizeof(m_widthRegionEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_heightRegionEnd,
							          sizeof(m_heightRegionEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_showText,
							          sizeof(m_showText), 
                        &dwBytesWritten,
							          NULL); 
	}

	return retVal;
}

BOOL TextDisplay::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	char tempBuff[TEMP_BUFF_LEN];
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_textID,
							        sizeof(m_textID), 
                      &dwBytesRead,
							        NULL); 
	}

	int fontNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&fontNameLen,
			                sizeof(fontNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											fontNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_fontName = tempBuff;
	}


	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_textType,
							        sizeof(m_textType), 
                      &dwBytesRead,
							        NULL); 
	}

	int dispStrLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&dispStrLen,
			                sizeof(dispStrLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											dispStrLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_displayString = tempBuff;
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_startClockValue,
							        sizeof(m_startClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorRStart,
							        sizeof(m_colorRStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorGStart,
							        sizeof(m_colorGStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorBStart,
							        sizeof(m_colorBStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_fontSizeStart,
							        sizeof(m_fontSizeStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftRegionStart,
							        sizeof(m_leftRegionStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topRegionStart,
							        sizeof(m_topRegionStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_widthRegionStart,
							        sizeof(m_widthRegionStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_heightRegionStart,
							        sizeof(m_heightRegionStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_endClockValue,
							        sizeof(m_endClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorREnd,
							        sizeof(m_colorREnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorGEnd,
							        sizeof(m_colorGEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorBEnd,
							        sizeof(m_colorBEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_fontSizeEnd,
							        sizeof(m_fontSizeEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftRegionEnd,
							        sizeof(m_leftRegionEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topRegionEnd,
							        sizeof(m_topRegionEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_widthRegionEnd,
							        sizeof(m_widthRegionEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_heightRegionEnd,
							        sizeof(m_heightRegionEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_showText,
							        sizeof(m_showText), 
                      &dwBytesRead,
							        NULL); 
	}

	return retVal;
}

HotspotInfo::HotspotInfo()
{
	m_hotSpotID = 0;
	m_hotSpotMode = HT_IMAGE;
	m_leftRect = 0;
	m_rightRect = 0;
	m_topRect = 0;
	m_bottomRect = 0;
	m_hoverScript = -1;
	m_unHoverScript = -1;
	m_feedbackString = "";
	m_clickTrigger = 0;
	m_interactionCount = 0;
	m_interactionType.Clear();     
	m_interactionSubType.Clear();
	m_interactionDescription.Clear(); 
	m_interactionTriggerScript.Clear();         
	m_interactionOptionIsEnabled.Clear() ;
	m_interactionFileSet.Clear();
	m_transformCursor = TRUE;
}

HotspotInfo::HotspotInfo(DWORD id)
{
	m_hotSpotID = id;
	m_hotSpotMode = HT_IMAGE;
	m_leftRect = 0;
	m_rightRect = 0;
	m_topRect = 0;
	m_bottomRect = 0;
	m_hoverScript = -1;
	m_unHoverScript = -1;
	m_feedbackString = "";
	m_clickTrigger = 0;
	m_interactionCount = 0;
	m_interactionType.Clear();     
	m_interactionSubType.Clear();
	m_interactionDescription.Clear(); 
	m_interactionTriggerScript.Clear();         
	m_interactionOptionIsEnabled.Clear() ;
	m_interactionFileSet.Clear();
	m_transformCursor = TRUE;
}

BOOL HotspotInfo::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_hotSpotID,
							          sizeof(m_hotSpotID), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_hotSpotMode,
							          sizeof(m_hotSpotMode), 
                        &dwBytesWritten,
							          NULL); 
	}

	m_imageInfo.SaveToFile(hFile);
	m_animationInfo.SaveToFile(hFile);
	m_characterInfo.SaveToFile(hFile);

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftRect,
							          sizeof(m_leftRect), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_rightRect,
							          sizeof(m_rightRect), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topRect,
							          sizeof(m_topRect), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_bottomRect,
							          sizeof(m_bottomRect), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_hoverScript,
							          sizeof(m_hoverScript), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_unHoverScript,
							          sizeof(m_unHoverScript), 
                        &dwBytesWritten,
							          NULL); 
	}


	int feedbackStrLen = strlen(m_feedbackString.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&feedbackStrLen,
											 sizeof(feedbackStrLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_feedbackString.operator PCTSTR() ,
											feedbackStrLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_clickTrigger,
							          sizeof(m_clickTrigger), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_interactionCount,
							          sizeof(m_interactionCount), 
                        &dwBytesWritten,
							          NULL); 
	}


  m_interactionType.ScanInit(DIRECTION_FORWARD);
	if (retVal)
	{
		while(m_interactionType.HasMoreElements())
		{
			InteractionType& interactionType =	m_interactionType.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&interactionType ,
								          sizeof(interactionType ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
	  m_interactionSubType.ScanInit(DIRECTION_FORWARD);
		while(m_interactionSubType.HasMoreElements())
		{
			int& interactionSubType =	m_interactionSubType.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&interactionSubType ,
								          sizeof(interactionSubType ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
	  m_interactionDescription.ScanInit(DIRECTION_FORWARD);
		while(m_interactionDescription.HasMoreElements())
		{
			CStdString& interactionDescription =	m_interactionDescription.NextElement();

			int interactionDescriptionLen = strlen(interactionDescription.operator PCTSTR());
			if (retVal)
			{
				retVal = WriteFile(hFile, 
														(const void*)&interactionDescriptionLen,
														sizeof(interactionDescriptionLen), 
														&dwBytesWritten,
														NULL); 
			}
			
			if (retVal)
			{
				retVal = WriteFile(hFile, 
														(const void*)interactionDescription.operator PCTSTR() ,
														interactionDescriptionLen, 
														&dwBytesWritten,
														NULL); 
			}
		}
	}

	if (retVal)
	{
	  m_interactionTriggerScript.ScanInit(DIRECTION_FORWARD);
		while(m_interactionTriggerScript.HasMoreElements())
		{
			int& triggerScript =	m_interactionTriggerScript.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&triggerScript ,
								          sizeof(triggerScript ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
	  m_interactionOptionIsEnabled.ScanInit(DIRECTION_FORWARD);
		while(m_interactionOptionIsEnabled.HasMoreElements())
		{
			bool& optionIsEnabled =	m_interactionOptionIsEnabled.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&optionIsEnabled ,
								          sizeof(optionIsEnabled), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
	  m_interactionFileSet.ScanInit(DIRECTION_FORWARD);
		while(m_interactionFileSet.HasMoreElements())
		{
			short& fileSet =	m_interactionFileSet.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&fileSet ,
								          sizeof(fileSet ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}
	
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_transformCursor,
							          sizeof(m_transformCursor), 
                        &dwBytesWritten,
							          NULL); 
	}

	return retVal;
}

BOOL HotspotInfo::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_hotSpotID,
							        sizeof(m_hotSpotID), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_hotSpotMode,
							        sizeof(m_hotSpotMode), 
                      &dwBytesRead,
							        NULL); 
	}

	m_imageInfo.ReadFromFile(hFile);
	m_animationInfo.ReadFromFile(hFile);
	m_characterInfo.ReadFromFile(hFile);

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftRect,
							        sizeof(m_leftRect), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_rightRect,
							        sizeof(m_rightRect), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topRect,
							        sizeof(m_topRect), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_bottomRect,
							        sizeof(m_bottomRect), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_hoverScript,
							        sizeof(m_hoverScript), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_unHoverScript,
							        sizeof(m_unHoverScript), 
                      &dwBytesRead,
							        NULL); 
	}

	int feedbackStrLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&feedbackStrLen,
			                sizeof(feedbackStrLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											feedbackStrLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_feedbackString = tempBuff;
	}


	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_clickTrigger,
							        sizeof(m_clickTrigger), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_interactionCount,
							        sizeof(m_interactionCount), 
                      &dwBytesRead,
							        NULL); 
	}


	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			InteractionType interactionType; 
			retVal = ReadFile(hFile, 
						           (void*)&interactionType ,
										    sizeof(interactionType ), 
			                  &dwBytesRead,
										    NULL); 
			m_interactionType.PushBack(interactionType);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			int interactionSubType; 
			retVal = ReadFile(hFile, 
							         (void*)&interactionSubType ,
											  sizeof(interactionSubType ), 
				                &dwBytesRead,
											  NULL); 
			m_interactionSubType.PushBack(interactionSubType);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			CStdString interactionDescription; 

			int interactionDescriptionLen;
			if (retVal)
			{
				retVal = ReadFile(hFile, 
													(void*)&interactionDescriptionLen,
													sizeof(interactionDescriptionLen), 
													&dwBytesRead,
													NULL); 
			}
			
			if (retVal)
			{
				char tempBuff[TEMP_BUFF_LEN];
				retVal = ReadFile(hFile, 
													(void*)tempBuff,
													interactionDescriptionLen, 
													&dwBytesRead,
													NULL); 
				
				tempBuff[dwBytesRead] = 0;
				interactionDescription = tempBuff;
			}

			m_interactionDescription.PushBack(interactionDescription);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			int triggerScript;
			retVal = ReadFile(hFile, 
						           (void*)&triggerScript ,
										    sizeof(triggerScript ), 
			                  &dwBytesRead,
										    NULL); 
			m_interactionTriggerScript.PushBack(triggerScript);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			bool optionIsEnabled;
			retVal = ReadFile(hFile, 
						           (void*)&optionIsEnabled ,
										    sizeof(optionIsEnabled), 
			                  &dwBytesRead,
										    NULL); 
			m_interactionOptionIsEnabled.PushBack(optionIsEnabled);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			short fileSet;
		  retVal = ReadFile(hFile, 
					             (void*)&fileSet ,
									      sizeof(fileSet ), 
		                    &dwBytesRead,
									      NULL); 
			m_interactionFileSet.PushBack(fileSet);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_transformCursor,
							        sizeof(m_transformCursor), 
                      &dwBytesRead,
							        NULL); 
	}

	return retVal;
}

KeyboardTrigger::KeyboardTrigger()
{
	m_keyID = 0;
	m_keyCode = 0;
	m_triggerScrript = 0;
	m_triggerIsEnabled = FALSE;
}

KeyboardTrigger::KeyboardTrigger(DWORD id)
{
	m_keyID = id;
	m_keyCode = 0;
	m_triggerScrript = 0;
	m_triggerIsEnabled = FALSE;
}

BOOL KeyboardTrigger::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;
	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_keyID,
							          sizeof(m_keyID), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_keyCode,
							          sizeof(m_keyCode), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_triggerScrript,
							          sizeof(m_triggerScrript), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_triggerIsEnabled,
							          sizeof(m_triggerIsEnabled), 
                        &dwBytesWritten,
							          NULL); 
	}



	return retVal;
}

BOOL KeyboardTrigger::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;
	DWORD dwBytesRead;
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_keyID,
							        sizeof(m_keyID), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_keyCode,
							        sizeof(m_keyCode), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_triggerScrript,
							        sizeof(m_triggerScrript), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_triggerIsEnabled,
							        sizeof(m_triggerIsEnabled), 
                      &dwBytesRead,
							        NULL); 
	}



	return retVal;
}


ItemDefinition::ItemDefinition()
{
	m_itemID = 0;
	m_iconFileName = "";
	m_hoverScript = -1;
	m_feedbackString = "";
	m_interactionCount = 0;
	m_interactionType.Clear();     
	m_interactionSubType.Clear();
	m_interactionDescription.Clear(); 
	m_interactionTriggerScript.Clear();         
	m_interactionOptionIsEnabled.Clear();
	m_interactionFileSet.Clear();
	m_itemIsStashed = FALSE;
}

ItemDefinition::ItemDefinition(DWORD id,LPCTSTR fileName)
{
	m_itemID = id;
	m_iconFileName = fileName;
	m_hoverScript = -1;
	m_feedbackString = "";
	m_interactionCount = 0;
	m_interactionType.Clear();     
	m_interactionSubType.Clear();
	m_interactionDescription.Clear(); 
	m_interactionTriggerScript.Clear();         
	m_interactionOptionIsEnabled.Clear();
	m_interactionFileSet.Clear();
	m_itemIsStashed = FALSE;
}

BOOL ItemDefinition::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)&m_itemID,
											sizeof(m_itemID), 
											&dwBytesWritten,
											NULL); 
	}

	int iconFileNameLen = strlen(m_iconFileName.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&iconFileNameLen,
											 sizeof(iconFileNameLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_iconFileName.operator PCTSTR() ,
											iconFileNameLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)&m_hoverScript,
											sizeof(m_hoverScript), 
											&dwBytesWritten,
											NULL); 
	}

	int feedbackStrLen = strlen(m_feedbackString.operator PCTSTR());
	if (retVal)
	{
		retVal = WriteFile(hFile, 
	 										(const void*)&feedbackStrLen,
											 sizeof(feedbackStrLen), 
  										 &dwBytesWritten,
											 NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)m_feedbackString.operator PCTSTR() ,
											feedbackStrLen, 
											&dwBytesWritten,
											NULL); 
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
											(const void*)&m_interactionCount,
											sizeof(m_interactionCount), 
											&dwBytesWritten,
											NULL); 
	}

  m_interactionType.ScanInit(DIRECTION_FORWARD);

	if (retVal)
	{
		while(m_interactionType.HasMoreElements())
		{
			InteractionType& interactionType =	m_interactionType.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&interactionType ,
								          sizeof(interactionType ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
	  m_interactionSubType.ScanInit(DIRECTION_FORWARD);
		while(m_interactionSubType.HasMoreElements())
		{
			int& interactionSubType =	m_interactionSubType.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&interactionSubType ,
								          sizeof(interactionSubType ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
	  m_interactionDescription.ScanInit(DIRECTION_FORWARD);
		while(m_interactionDescription.HasMoreElements())
		{
			CStdString& interactionDescription =	m_interactionDescription.NextElement();
			int interactionDescriptionLen = strlen(interactionDescription.operator PCTSTR());
			if (retVal)
			{
				retVal = WriteFile(hFile, 
														(const void*)&interactionDescriptionLen,
														sizeof(interactionDescriptionLen), 
														&dwBytesWritten,
														NULL); 
			}
			
			if (retVal)
			{
				retVal = WriteFile(hFile, 
														(const void*)interactionDescription.operator PCTSTR() ,
														interactionDescriptionLen, 
														&dwBytesWritten,
														NULL); 
			}
		}

	}

	if (retVal)
	{
	  m_interactionTriggerScript.ScanInit(DIRECTION_FORWARD);
		while(m_interactionTriggerScript.HasMoreElements())
		{
			int& triggerScript =	m_interactionTriggerScript.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&triggerScript ,
								          sizeof(triggerScript ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
	  m_interactionOptionIsEnabled.ScanInit(DIRECTION_FORWARD);
		while(m_interactionOptionIsEnabled.HasMoreElements())
		{
			bool& optionIsEnabled =	m_interactionOptionIsEnabled.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&optionIsEnabled ,
								          sizeof(optionIsEnabled), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
	  m_interactionFileSet.ScanInit(DIRECTION_FORWARD);
		while(m_interactionFileSet.HasMoreElements())
		{
			short& fileSet =	m_interactionFileSet.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&fileSet ,
								          sizeof(fileSet ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		retVal = WriteFile(hFile, 
			(const void*)&m_itemIsStashed,
			sizeof(m_itemIsStashed), 
			&dwBytesWritten,
			NULL); 
	}

	return retVal;
}

BOOL ItemDefinition::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&m_itemID,
											sizeof(m_itemID), 
											&dwBytesRead,
											NULL); 
	}

	int iconFileNameLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&iconFileNameLen,
			                sizeof(iconFileNameLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											iconFileNameLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_iconFileName = tempBuff;
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&m_hoverScript,
											sizeof(m_hoverScript), 
											&dwBytesRead,
											NULL); 
	}

	int feedbackStrLen;
	if (retVal)
	{
		retVal = ReadFile(hFile, 
										  (void*)&feedbackStrLen,
			                sizeof(feedbackStrLen), 
			                &dwBytesRead,
			                NULL); 
	}

	if (retVal)
	{
		char tempBuff[TEMP_BUFF_LEN];
		retVal = ReadFile(hFile, 
											(void*)tempBuff,
											feedbackStrLen, 
											&dwBytesRead,
											NULL); 

		tempBuff[dwBytesRead] = 0;
		m_feedbackString = tempBuff;
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&m_interactionCount,
											sizeof(m_interactionCount), 
											&dwBytesRead,
											NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			InteractionType interactionType; 
			retVal = ReadFile(hFile, 
						           (void*)&interactionType ,
										    sizeof(interactionType ), 
			                  &dwBytesRead,
										    NULL); 
			m_interactionType.PushBack(interactionType);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			int interactionSubType; 
			retVal = ReadFile(hFile, 
							         (void*)&interactionSubType ,
											  sizeof(interactionSubType ), 
				                &dwBytesRead,
											  NULL); 
			m_interactionSubType.PushBack(interactionSubType);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			CStdString interactionDescription; 
			int interactionDescriptionLen;
			if (retVal)
			{
				retVal = ReadFile(hFile, 
													(void*)&interactionDescriptionLen,
													sizeof(interactionDescriptionLen), 
													&dwBytesRead,
													NULL); 
			}
			
			if (retVal)
			{
				char tempBuff[TEMP_BUFF_LEN];
				retVal = ReadFile(hFile, 
													(void*)tempBuff,
													interactionDescriptionLen, 
													&dwBytesRead,
													NULL); 
				
				tempBuff[dwBytesRead] = 0;
				interactionDescription = tempBuff;
			}

			m_interactionDescription.PushBack(interactionDescription);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			int triggerScript;
			retVal = ReadFile(hFile, 
						           (void*)&triggerScript ,
										    sizeof(triggerScript ), 
			                  &dwBytesRead,
										    NULL); 
			m_interactionTriggerScript.PushBack(triggerScript);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			bool optionIsEnabled;
			retVal = ReadFile(hFile, 
						           (void*)&optionIsEnabled ,
										    sizeof(optionIsEnabled), 
			                  &dwBytesRead,
										    NULL); 
			m_interactionOptionIsEnabled.PushBack(optionIsEnabled);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_interactionCount; i++)
		{
			short fileSet;
		  retVal = ReadFile(hFile, 
					             (void*)&fileSet ,
									      sizeof(fileSet ), 
		                    &dwBytesRead,
									      NULL); 
			m_interactionFileSet.PushBack(fileSet);
		}
	}

	if (retVal)
	{
		retVal = ReadFile(hFile, 
											(void*)&m_itemIsStashed,
											sizeof(m_itemIsStashed), 
											&dwBytesRead,
											NULL); 
	}

	return retVal;
}


CameraDefinition::CameraDefinition()
{
	m_sceneID = 0;
	m_cameraIsFrozen = FALSE;
	m_cameraIsEnabled = FALSE;
  m_layer = NAVIGABLE_SCENE;
	m_sceneIsInitialized = FALSE;
	m_applyColorFilter = FALSE;
	m_applyTrasparency = FALSE;
	m_startClockValue = 0;
	m_colorHStart = 0;
	m_colorLStart = 0;
  m_colorSStart = 0;
	m_transparencyStart = 0;
	m_endClockValue = 0;
	m_colorHEnd = 0;
	m_colorLEnd = 0;
	m_colorSEnd = 0;
	m_transparencyEnd = 0;
}

CameraDefinition::CameraDefinition(DWORD id)
{
	m_sceneID = id;
	m_cameraIsFrozen = FALSE;
	m_cameraIsEnabled = FALSE;
  m_layer = NAVIGABLE_SCENE;
	m_sceneIsInitialized = FALSE;
	m_applyColorFilter = FALSE;
	m_applyTrasparency = FALSE;
	m_startClockValue = 0;
	m_colorHStart = 0;
	m_colorLStart = 0;
  m_colorSStart = 0;
	m_transparencyStart = 0;
	m_endClockValue = 0;
	m_colorHEnd = 0;
	m_colorLEnd = 0;
	m_colorSEnd = 0;
	m_transparencyEnd = 0;
}

BOOL CameraDefinition::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_sceneID,
							          sizeof(m_sceneID), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_cameraIsFrozen,
							          sizeof(m_cameraIsFrozen), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_cameraIsEnabled,
							          sizeof(m_cameraIsEnabled), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_layer,
							          sizeof(m_layer), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_sceneIsInitialized,
							          sizeof(m_sceneIsInitialized), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_applyColorFilter,
							          sizeof(m_applyColorFilter), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_applyTrasparency,
							          sizeof(m_applyTrasparency), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_startClockValue,
							          sizeof(m_startClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorHStart,
							          sizeof(m_colorHStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorLStart,
							          sizeof(m_colorLStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorSStart,
							          sizeof(m_colorSStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_transparencyStart,
							          sizeof(m_transparencyStart), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_endClockValue,
							          sizeof(m_endClockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorHEnd,
							          sizeof(m_colorHEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorLEnd,
							          sizeof(m_colorLEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_colorSEnd,
							          sizeof(m_colorSEnd), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_transparencyEnd,
							          sizeof(m_transparencyEnd), 
                        &dwBytesWritten,
							          NULL); 
	}


	return retVal;
}

BOOL CameraDefinition::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_sceneID,
							        sizeof(m_sceneID), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_cameraIsFrozen,
							        sizeof(m_cameraIsFrozen), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_cameraIsEnabled,
							        sizeof(m_cameraIsEnabled), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_layer,
							        sizeof(m_layer), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_sceneIsInitialized,
							        sizeof(m_sceneIsInitialized), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_applyColorFilter,
							        sizeof(m_applyColorFilter), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_applyTrasparency,
							        sizeof(m_applyTrasparency), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_startClockValue,
							        sizeof(m_startClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorHStart,
							        sizeof(m_colorHStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorLStart,
							        sizeof(m_colorLStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorSStart,
							        sizeof(m_colorSStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_transparencyStart,
							        sizeof(m_transparencyStart), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_endClockValue,
							        sizeof(m_endClockValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorHEnd,
							        sizeof(m_colorHEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorLEnd,
							        sizeof(m_colorLEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_colorSEnd,
							        sizeof(m_colorSEnd), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_transparencyEnd,
							        sizeof(m_transparencyEnd), 
                      &dwBytesRead,
							        NULL); 
	}


	return retVal;
}

SceneDefinition::SceneDefinition()
{
	m_sceneID = 0;
	m_sceneIsNavigable = FALSE;
  m_filesetID = 0;
	m_entranceScript = -1; 	
	m_exitScript = -1;
	m_activeText = 0;

	m_displayInventory = FALSE;
	m_leftInventoryDisplay = 0;
	m_topInventoryDisplay = 0;
	m_widthInventoryDisplay = 0;
	m_heightInventoryDisplay = 0;

	m_bgMusicCode = 0;  
  m_skyID = -1;        
	
	m_imageCount = 0;
	m_images.Clear();

	m_animationCount = 0;
	m_animations.Clear();

	m_characterCount = 0;
	m_sceneCharacters.Clear();

	m_sfxCount = 0;
	m_sfx.Clear();

	m_textOverlayCount = 0;
  m_textOverlays.Clear();

	m_clickCount = 0;
	m_clickSpots.Clear();

	m_keyCount = 0;
	m_keys.Clear();
}

SceneDefinition::SceneDefinition(DWORD id)
{
	m_sceneID = id;
	m_sceneIsNavigable = FALSE;
  m_filesetID = 0;
	m_entranceScript = -1; 	
	m_exitScript = -1;
	m_activeText = 0;

	m_displayInventory = FALSE;
	m_leftInventoryDisplay = 0;
	m_topInventoryDisplay = 0;
	m_widthInventoryDisplay = 0;
	m_heightInventoryDisplay = 0;

	m_bgMusicCode = 0;  
  m_skyID = -1;        
	
	m_imageCount = 0;
	m_images.Clear();

	m_animationCount = 0;
	m_animations.Clear();

	m_characterCount = 0;
	m_sceneCharacters.Clear();

	m_sfxCount = 0;
	m_sfx.Clear();

	m_textOverlayCount = 0;
  m_textOverlays.Clear();

	m_clickCount = 0;
	m_clickSpots.Clear();

	m_keyCount = 0;
	m_keys.Clear();
}

BOOL SceneDefinition::SaveToFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesWritten;
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_sceneID,
							          sizeof(m_sceneID), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_sceneIsNavigable,
							          sizeof(m_sceneIsNavigable), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_filesetID,
							          sizeof(m_filesetID), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_entranceScript,
							          sizeof(m_entranceScript), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_exitScript,
							          sizeof(m_exitScript), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_activeText,
							          sizeof(m_activeText), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_displayInventory,
							          sizeof(m_displayInventory), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_leftInventoryDisplay,
							          sizeof(m_leftInventoryDisplay), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_topInventoryDisplay,
							          sizeof(m_topInventoryDisplay), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_widthInventoryDisplay,
							          sizeof(m_widthInventoryDisplay), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_heightInventoryDisplay,
							          sizeof(m_heightInventoryDisplay), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_bgMusicCode,
							          sizeof(m_bgMusicCode), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_skyID,
							          sizeof(m_skyID), 
                        &dwBytesWritten,
							          NULL); 
	}

	retVal = stage.SaveToFile(hFile);

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_imageCount,
							          sizeof(m_imageCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	m_images.ScanInit(DIRECTION_FORWARD);
	if (retVal)
	{
		while(m_images.HasMoreElements())
		{
			ImageInfo& imageInfo =	m_images.NextElement();
			retVal = imageInfo.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_animationCount,
							          sizeof(m_animationCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		m_animations.ScanInit(DIRECTION_FORWARD);
		while(m_animations.HasMoreElements())
		{
			AnimationInfo& animationInfo =	m_animations.NextElement();
			retVal = animationInfo.SaveToFile(hFile);
		}		
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_characterCount,
							          sizeof(m_characterCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		m_sceneCharacters.ScanInit(DIRECTION_FORWARD);
		while(m_sceneCharacters.HasMoreElements())
		{
			CharacterContext& characterContext =	m_sceneCharacters.NextElement();
			retVal = characterContext.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_sfxCount,
							          sizeof(m_sfxCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		m_sfx.ScanInit(DIRECTION_FORWARD);
		while(m_sfx.HasMoreElements())
		{
			SFXInfo& sfxInfo =	m_sfx.NextElement();
			retVal = sfxInfo.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_textOverlayCount,
							          sizeof(m_textOverlayCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		m_textOverlays.ScanInit(DIRECTION_FORWARD);
		while(m_textOverlays.HasMoreElements())
		{
			TextDisplay& textDisplay =	m_textOverlays.NextElement();
			retVal = textDisplay.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_clickCount,
							          sizeof(m_clickCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		m_clickSpots.ScanInit(DIRECTION_FORWARD);
		while(m_clickSpots.HasMoreElements())
		{
			HotspotInfo& hotSpot =	m_clickSpots.NextElement();
			retVal = hotSpot.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_keyCount,
							          sizeof(m_keyCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		m_keys.ScanInit(DIRECTION_FORWARD);
		while(m_keys.HasMoreElements())
		{
			KeyboardTrigger& keys =	m_keys.NextElement();
			retVal = keys.SaveToFile(hFile);
		}
	}

	return retVal;
}

BOOL SceneDefinition::ReadFromFile(HANDLE& hFile)
{
	BOOL retVal = TRUE;

	DWORD dwBytesRead;
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_sceneID,
							        sizeof(m_sceneID), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_sceneIsNavigable,
							        sizeof(m_sceneIsNavigable), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_filesetID,
							        sizeof(m_filesetID), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_entranceScript,
							        sizeof(m_entranceScript), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_exitScript,
							        sizeof(m_exitScript), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_activeText,
							        sizeof(m_activeText), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_displayInventory,
							        sizeof(m_displayInventory), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_leftInventoryDisplay,
							        sizeof(m_leftInventoryDisplay), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_topInventoryDisplay,
							        sizeof(m_topInventoryDisplay), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_widthInventoryDisplay,
							        sizeof(m_widthInventoryDisplay), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_heightInventoryDisplay,
							        sizeof(m_heightInventoryDisplay), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_bgMusicCode,
							        sizeof(m_bgMusicCode), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_skyID,
							        sizeof(m_skyID), 
                      &dwBytesRead,
							        NULL); 
	}

	stage.ReadFromFile(hFile);

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_imageCount,
							        sizeof(m_imageCount), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_imageCount; i++)
		{
			ImageInfo imageInfo; 
			retVal = imageInfo.ReadFromFile(hFile);
			m_images.PushBack(imageInfo);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_animationCount,
							        sizeof(m_animationCount), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_animationCount; i++)
		{
			AnimationInfo animationInfo; 
			retVal = animationInfo.ReadFromFile(hFile);
			m_animations.PushBack(animationInfo);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_characterCount,
							        sizeof(m_characterCount), 
                      &dwBytesRead,
									    NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_characterCount; i++)
		{
			CharacterContext characterContext; 
			retVal = characterContext.ReadFromFile(hFile);
			m_sceneCharacters.PushBack(characterContext);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_sfxCount,
							        sizeof(m_sfxCount), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_sfxCount; i++)
		{
			SFXInfo sfxInfo; 
			retVal = sfxInfo.ReadFromFile(hFile);
			m_sfx.PushBack(sfxInfo);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_textOverlayCount,
							        sizeof(m_textOverlayCount), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_textOverlayCount; i++)
		{
			TextDisplay textDisplay; 
			retVal = textDisplay.ReadFromFile(hFile);
			m_textOverlays.PushBack(textDisplay);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_clickCount,
							        sizeof(m_clickCount), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_clickCount; i++)
		{
			HotspotInfo hotSpot; 
			retVal = hotSpot.ReadFromFile(hFile);
			m_clickSpots.PushBack(hotSpot);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_keyCount,
							        sizeof(m_keyCount), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_keyCount; i++)
		{
			KeyboardTrigger keys; 
			retVal = keys.ReadFromFile(hFile);
			m_keys.PushBack(keys);
		}
	}

	return retVal;
}

World::World()
{
	m_clockValue = 0;
	m_clockIsPowered = TRUE;

	m_bgMusicCount = 0;
	m_bgMusicScript.Clear();

	m_bgMusicFileCount = 0;
	m_bgMusicSample.Clear();

  m_numberOfCharacters = 0;
	m_characters .Clear();

	m_numberOfScenes = 0;
	m_scenes.Clear();

	m_numberOfSkies = 0;
	m_skies.Clear();

	m_inventorySize = 0;
	m_inventory.Clear();

	m_cameraCount = 0;
	m_camera.Clear();

  m_recordCount = 0;
	m_trackID.Clear();
	m_trackRecord.Clear(); 

	for (int i = 0; i < INTERACTIVE_SCENE_COUNT; i++)
	{
		m_interactiveScene[i] = USER_INTERFACE_SCENE;
	}

	for (i = 0; i < TIME_COUNT; i++)
	{
		m_timedScript[i] = 0;
		m_timerValue[i] = 0;
	}
	m_currentBGMusic = 0;
	m_previousBGMusic = 0;
}

BOOL World::SaveToFile(DWORD& key,HANDLE& hFile)
{
	BOOL retVal = TRUE;
	DWORD dwBytesWritten;

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&key,
							          sizeof(key), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_clockValue,
							          sizeof(m_clockValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_clockIsPowered,
							          sizeof(m_clockIsPowered), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_bgMusicCount,
							          sizeof(m_bgMusicCount), 
                        &dwBytesWritten,
							          NULL); 
	}

  m_bgMusicScript.ScanInit(DIRECTION_FORWARD);
	if (retVal)
	{
		while(m_bgMusicScript.HasMoreElements())
		{
			MusicScript& musicScript =	m_bgMusicScript.NextElement();
			retVal = musicScript.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_bgMusicFileCount,
							          sizeof(m_bgMusicFileCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
	  m_bgMusicSample.ScanInit(DIRECTION_FORWARD);
		while(m_bgMusicSample.HasMoreElements())
		{
			MusicSample& musicSample =	m_bgMusicSample.NextElement();
			retVal = musicSample.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_numberOfCharacters,
							          sizeof(m_numberOfCharacters), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
	  m_characters.ScanInit(DIRECTION_FORWARD);
		while(m_characters.HasMoreElements())
		{
			CharacterInfo& characterInfo =	m_characters.NextElement();
			retVal = characterInfo.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_numberOfScenes,
							          sizeof(m_numberOfScenes), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
	  m_scenes.ScanInit(DIRECTION_FORWARD);
		while(m_scenes.HasMoreElements())
		{
			SceneDefinition& sceneDefinition =	m_scenes.NextElement();
			retVal = sceneDefinition.SaveToFile(hFile);
		}
	}


	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_numberOfSkies,
							          sizeof(m_numberOfSkies), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
	  m_skies.ScanInit(DIRECTION_FORWARD);
		while(m_skies.HasMoreElements())
		{
			SkyDefinition& skyDefinition =	m_skies.NextElement();
			retVal = skyDefinition.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_inventorySize,
							          sizeof(m_inventorySize), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
	  m_inventory.ScanInit(DIRECTION_FORWARD);
		while(m_inventory.HasMoreElements())
		{
			ItemDefinition& itemDefinition =	m_inventory.NextElement();
			retVal = itemDefinition.SaveToFile(hFile);
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_cameraCount,
							          sizeof(m_cameraCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
	  m_camera.ScanInit(DIRECTION_FORWARD);
		while(m_camera.HasMoreElements())
		{
			CameraDefinition& cameraDefinition =	m_camera.NextElement();
			retVal = cameraDefinition.SaveToFile(hFile);
		}
	}
	
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_recordCount,
							          sizeof(m_recordCount), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
	  m_trackID.ScanInit(DIRECTION_FORWARD);
		while(m_trackID.HasMoreElements())
		{
			short& trackId =	m_trackID.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&trackId ,
								          sizeof(trackId ), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
	  m_trackRecord.ScanInit(DIRECTION_FORWARD);
		while(m_trackRecord.HasMoreElements())
		{
			long& trackRecord =	m_trackRecord.NextElement();
	    retVal = WriteFile(hFile, 
				                 (const void*)&trackRecord  ,
								          sizeof(trackRecord), 
	                        &dwBytesWritten,
								          NULL); 
		}
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_interactiveScene,
							          sizeof(m_interactiveScene), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_timedScript,
							          sizeof(m_timedScript), 
                        &dwBytesWritten,
							          NULL); 
	}
	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_timerValue,
							          sizeof(m_timerValue), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_currentBGMusic,
							          sizeof(m_currentBGMusic), 
                        &dwBytesWritten,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = WriteFile(hFile, 
			                  (const void*)&m_previousBGMusic,
							          sizeof(m_previousBGMusic), 
                        &dwBytesWritten,
							          NULL); 
	}

	return retVal;	
}

BOOL World::ReadFromFile(DWORD& key,HANDLE& hFile)
{
	BOOL retVal = TRUE;
	DWORD dwBytesRead;

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&key,
							          sizeof(key), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_clockValue,
							          sizeof(m_clockValue), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_clockIsPowered,
							         sizeof(m_clockIsPowered), 
                       &dwBytesRead,
							         NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_bgMusicCount,
							          sizeof(m_bgMusicCount), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_bgMusicCount; i++)
		{
			MusicScript musicScript; 
			retVal = musicScript.ReadFromFile(hFile);
			m_bgMusicScript.PushBack(musicScript);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                 (void*)&m_bgMusicFileCount,
							          sizeof(m_bgMusicFileCount), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_bgMusicFileCount; i++)
		{
			MusicSample musicSample; 
			retVal = musicSample.ReadFromFile(hFile);
			m_bgMusicSample.PushBack(musicSample);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                 (void*)&m_numberOfCharacters,
							          sizeof(m_numberOfCharacters), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_numberOfCharacters; i++)
		{
			CharacterInfo characterInfo; 
			retVal = characterInfo.ReadFromFile(hFile);
			m_characters.PushBack(characterInfo);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_numberOfScenes,
							          sizeof(m_numberOfScenes), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_numberOfScenes; i++)
		{
			SceneDefinition sceneDefinition; 
			retVal = sceneDefinition.ReadFromFile(hFile);
			m_scenes.PushBack(sceneDefinition);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                  (void*)&m_numberOfSkies,
							          sizeof(m_numberOfSkies), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_numberOfSkies; i++)
		{
			SkyDefinition skyDefinition; 
			retVal = skyDefinition.ReadFromFile(hFile);
			m_skies.PushBack(skyDefinition);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                 (void*)&m_inventorySize,
							          sizeof(m_inventorySize), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_inventorySize; i++)
		{
			ItemDefinition itemDefinition; 
			retVal = itemDefinition.ReadFromFile(hFile);
			m_inventory.PushBack(itemDefinition);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                 (void*)&m_cameraCount,
							          sizeof(m_cameraCount), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_cameraCount; i++)
		{
			CameraDefinition cameraDefinition; 
			retVal = cameraDefinition.ReadFromFile(hFile);
			m_camera.PushBack(cameraDefinition);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                 (void*)&m_recordCount,
							          sizeof(m_recordCount), 
                        &dwBytesRead,
							          NULL); 
	}

	if (retVal)
	{
		for (int i = 0; i < m_recordCount; i++)
		{
			short trackId; 
			retVal = ReadFile(hFile, 
												(void*)&trackId ,
												sizeof(trackId ), 
												&dwBytesRead,
												NULL); 
			m_trackID.PushBack(trackId);
		}
	}

	if (retVal)
	{
		for (int i = 0; i < m_recordCount; i++)
		{
			long trackRecord; 
			retVal = ReadFile(hFile, 
												(void*)&trackRecord ,
												sizeof(trackRecord ), 
												&dwBytesRead,
												NULL); 
			m_trackRecord.PushBack(trackRecord);
		}
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_interactiveScene,
							        sizeof(m_interactiveScene), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_timedScript,
							         sizeof(m_timedScript), 
                       &dwBytesRead,
							         NULL); 
	}
	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_timerValue,
							        sizeof(m_timerValue), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_currentBGMusic,
							        sizeof(m_currentBGMusic), 
                      &dwBytesRead,
							        NULL); 
	}

	if (retVal)
	{
		 retVal = ReadFile(hFile, 
			                (void*)&m_previousBGMusic,
							        sizeof(m_previousBGMusic), 
                      &dwBytesRead,
							        NULL); 
	}

	return retVal;	
}