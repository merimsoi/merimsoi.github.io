#include "stdafx.h"
#include "fileUtils.h"

// //////////////////////////////////////////////////////////////////////////
// RealFileClass methods implementations
// //////////////////////////////////////////////////////////////////////////
RealFileClass::RealFileClass()
{
  m_fileHandle = INVALID_HANDLE_VALUE;
  m_fileName = "";

  m_status.SetOK ();
}

void RealFileClass::SetError(VgUInt errCode, VgChar* text)
{
  SET_AND_HANDLE (m_status, errCode, VgWarning, CSU_ID, text);
}

VgBool RealFileClass::Open (
  const FileNameClass& fileName, 
  VgFileAccessEnum desiredAccess,
  VgCreationDispositionEnum creationDisposition,
  VgShareModeEnum fileShareMode)
{
  VgBool success;

  m_status.SetOK();

  if (m_fileHandle == INVALID_HANDLE_VALUE)
  {
    m_fileHandle = CreateFile (
      fileName.GetFullName(),
      DesiredAccessEnumToMask (desiredAccess),
      ShareModeEnumToMask(fileShareMode),
      NULL, // security params
      CreationDispositionEnumToMask (creationDisposition),
      FILE_ATTRIBUTE_NORMAL,
      NULL);

    if (m_fileHandle != INVALID_HANDLE_VALUE)
    {
      m_fileName = fileName.GetFullName();
      success = VgTrue;
    }
    else
    {
      GetOpenError(fileName);

      success = VgFalse;
    }
  }
  else
  {
    SetError(EC_FILE_ALREADY_OPENED, "attempt to open a file which is already opened");

    success = VgFalse;
  }

  return success;
}

VgBool RealFileClass::Close ()
{
  BOOL  success;

  m_status.SetOK();

  if (m_fileHandle != INVALID_HANDLE_VALUE)
  {
    success = CloseHandle (m_fileHandle);

    if (!success)
      GetCloseError();

  }
  else
  {
    SetError(EC_FILE_ALREADY_CLOSED, "attempt to close a file which is already closed");

    success = VgFalse;
  }
  // E.R 
  m_fileHandle = INVALID_HANDLE_VALUE;

  return success;
}

VgBool RealFileClass::Read (
  VgUByte* buffer, 
  VgUInt   noOfBytesToRead,
  VgUInt&  noOfBytesRead)
{
  DWORD bytesRead;
  BOOL  success;

  m_status.SetOK();

  if (m_fileHandle != INVALID_HANDLE_VALUE)
  {
    success = ReadFile (
      m_fileHandle,
      buffer,
      noOfBytesToRead,
      &bytesRead,
      NULL);

    noOfBytesRead = bytesRead;

    if (!success)
      GetReadError();

    else if (success && noOfBytesToRead != bytesRead)
    {
//      SetError(EC_NOT_ALL_DATA_READ, "not all requested data was read");
    }
  }
  else
  {
    SetError(EC_NO_FILE_IS_OPENED, "operation failed, no file is opened");

    success = VgFalse;
    noOfBytesRead = 0;
  }

  return success;
}

VgBool RealFileClass::Write (
  const VgUByte* buffer, 
  VgUInt noOfBytesToWrite,
  VgUInt& noOfBytesWriten)
{
  DWORD bytesWriten;
  BOOL  success;

  if (m_fileHandle != INVALID_HANDLE_VALUE)
  {
    success = WriteFile (
      m_fileHandle,
      buffer,
      noOfBytesToWrite,
      &bytesWriten,
      NULL);
    noOfBytesWriten = bytesWriten;

    if (!success)
      GetWriteError();

    else if (noOfBytesToWrite != bytesWriten)
    {
      SetError(EC_NOT_ALL_DATA_WRITEN, "not all data was writen");

      success = VgFalse;
    }
  }
  else
  {
    SetError(EC_NO_FILE_IS_OPENED, "operation failed, no file is opened");

    success = VgFalse;
    noOfBytesWriten = 0;
  }

  return success;
}

VgBool RealFileClass::Copy (
  const FileNameClass& destinationFileName,
  VgCreationDispositionEnum creationDisposition)
{
  VgBool success = VgFalse;

  if (m_fileHandle == INVALID_HANDLE_VALUE && 
      !m_fileName.IsEmpty() )
  {
    success = bOsShellFileUtils::Copy (
      FileNameClass (m_fileName), 
      destinationFileName, 
      creationDisposition);
  }

  return success;
}

VgBool RealFileClass::Move (
  const FileNameClass& destinationFileName,
  VgCreationDispositionEnum creationDisposition)
{
  VgBool success = VgFalse;

  if (m_fileHandle == INVALID_HANDLE_VALUE && 
      !m_fileName.IsEmpty() )
  {
    success = bOsShellFileUtils::Move (
      FileNameClass (m_fileName), 
      destinationFileName, 
      creationDisposition);

    if (success)
      m_fileName = destinationFileName.GetFullName();
  }

  return success;
}

VgBool RealFileClass::Delete ()
{
  VgBool success = VgFalse;

  if (m_fileHandle == INVALID_HANDLE_VALUE && 
      !m_fileName.IsEmpty() )
  {
    success = DeleteFile (
      m_fileName);

    if (success)
      m_fileName.Resize(0);
  }

  return success;
}


VgBool RealFileClass::SetFilePointer (
  VgSDWord distance,
  VgMoveMethodEnum moveMethod)
{
  VgBool success = VgFalse;

  if (m_fileHandle != INVALID_HANDLE_VALUE)
  {
    DWORD newPos = ::SetFilePointer (
      m_fileHandle,
      distance,
      NULL,
      MoveMethodEnumToMask(moveMethod));

    if (newPos != 0xFFFFFFFF)
      success = VgTrue;
  }

  return success;
}

VgSDWord RealFileClass::GetFilePointer ()
{
  VgSDWord result = -1;

  if (m_fileHandle != INVALID_HANDLE_VALUE)
  {
    DWORD currentPos = ::SetFilePointer (
      m_fileHandle,
      0,
      NULL,
      FILE_CURRENT);

    if (GetLastError() == NO_ERROR)
      result = currentPos;
  }

  return result;
}

VgUInt RealFileClass::GetSize ()
{
  DWORD fileSize;

  if (m_fileHandle != INVALID_HANDLE_VALUE)
  {
    fileSize =  GetFileSize (m_fileHandle, NULL);
  }
  else
  {
    fileSize = 0;

    SetError(EC_INVALID_HANDLE, "GetSize : invalid handle was given");
  }

  return fileSize;  
}


VgBool RealFileClass::IsEof ()
{
  VgBool isEof = VgTrue;

  if (m_fileHandle != INVALID_HANDLE_VALUE)
  {
    DWORD fileSize;

    fileSize = GetFileSize (m_fileHandle, NULL);
    isEof = (GetFilePointer() == fileSize);
  }

  return isEof;
}

VgBool RealFileClass::IsBof ()
{
  VgBool isBof = VgFalse;

  if (m_fileHandle != INVALID_HANDLE_VALUE)
  {
    isBof = GetFilePointer() == 0;
  }

  return isBof;
}

DWORD RealFileClass::DesiredAccessEnumToMask (
  VgFileAccessEnum desiredAccess)
{
  DWORD result;

  const DWORD desiredAccessMaskTable[] = {
    GENERIC_READ,
    GENERIC_WRITE,
    GENERIC_READ | GENERIC_WRITE
  };

  if (desiredAccess > 2 || desiredAccess < 0)
    result = 0;

  else
    result = desiredAccessMaskTable[desiredAccess];

  return result;
}

DWORD RealFileClass::CreationDispositionEnumToMask (
  VgCreationDispositionEnum creationDisposition)
{
  DWORD result;

  const DWORD creationDispositionMaskTable[] = {
    CREATE_NEW,
    CREATE_ALWAYS,
    OPEN_EXISTING,
    OPEN_ALWAYS,
    TRUNCATE_EXISTING
  };

  if (creationDisposition > 4 || creationDisposition < 0)
    result = 0;

  else
    result = creationDispositionMaskTable[creationDisposition];

  return result;
}

DWORD RealFileClass::ShareModeEnumToMask (
  VgShareModeEnum shareMode)
{
  DWORD result;

  const DWORD shareModeMaskTable[] = {
    0,
    FILE_SHARE_READ,
    FILE_SHARE_WRITE,
    FILE_SHARE_READ | FILE_SHARE_WRITE
  };

  if (shareMode > 3 || shareMode < 0)
    result = 0;

  else
    result = shareModeMaskTable[shareMode];

  return result;
}

DWORD RealFileClass::MoveMethodEnumToMask (
  VgMoveMethodEnum moveMethod)
{
  DWORD result;

  const DWORD moveMathodMaskTable[] = {
    FILE_BEGIN,
    FILE_CURRENT,
    FILE_END
  };

  if (moveMethod > 2 || moveMethod < 0)
    result = 0;

  else
    result = moveMathodMaskTable[moveMethod];

  return result;
}

void RealFileClass::GetOpenError (
  const FileNameClass& fileName)
{
  VgChar textBuff [1000];
  DWORD err = GetLastError();
  switch (err)
  {
  case ERROR_FILE_NOT_FOUND:
    sprintf (textBuff, "%s <%s>", "file not found", (VgChar*)((const VgChar*)fileName.GetShortName()));
    SetError(EC_FILE_NOT_FOUND, textBuff);
    break;
  case ERROR_PATH_NOT_FOUND:
    sprintf (textBuff, "%s <%s>", "path not found", (VgChar*)((const VgChar*)fileName.GetShortName()));
    SetError(EC_PATH_NOT_FOUND, textBuff);
    break;
  case ERROR_FILE_EXISTS:
    sprintf (textBuff, "%s <%s>", "file already exists", (VgChar*)((const VgChar*)fileName.GetShortName()));
    SetError(EC_FILE_EXISTS, textBuff);
    break;
  case ERROR_SHARING_VIOLATION:
    sprintf (textBuff, "%s <%s>", "file not opened, sharing violation", (VgChar*)((const VgChar*)fileName.GetShortName()));
    SetError(EC_SHARING_VIOLATION, textBuff);
    break;
  default:
    sprintf (textBuff, "%s <%s>", "file not opened, general reason", (VgChar*)((const VgChar*)fileName.GetShortName()));
    SetError(EC_CANNOT_OPEN_FILE, textBuff);
  }
}


void RealFileClass::GetCloseError ()
{
  switch (GetLastError())
  {
  case ERROR_INVALID_HANDLE:
    SetError(EC_INVALID_HANDLE, "invalid handler, (very bad)");
    break;
  default:
    SetError(EC_ERROR_IN_CLOSING_FILE, "failed to close file");
  }
}

void RealFileClass::GetReadError ()
{
  switch (GetLastError())
  {
  case ERROR_INVALID_HANDLE:
    SetError(EC_INVALID_HANDLE, "invalid handler, (very bad)");
    break;
  case ERROR_ACCESS_DENIED:
    SetError(EC_READ_ACCESS_DENIED, "access denied, file was not opened for reading");
    break;
  default:
    SetError(EC_CANNOT_READ_FROM_FILE, "problem occured while reading from file");
  }
}

void RealFileClass::GetWriteError ()
{
  switch (GetLastError())
  {
    SetError(EC_INVALID_HANDLE, "invalid handler, (very bad)");
    break;
  case ERROR_ACCESS_DENIED:
    SetError(EC_WRITE_ACCESS_DENIED, "access denied, file was not opened for writing");
    break;
  default:
    SetError(EC_CANNOT_WRITE_TO_FILE, "problem occured while wrting to file");
  }
}

bTypesStrings::VgStringClass RealFileClass::GetFileName()
{
  return m_fileName;
}

VgBool RealFileClass::GetFileLastWriteTime(bOsShellFiles::FileNameClass fileName,
                                           bTimeTod::TodClass& lastWriteTime)
{
  BY_HANDLE_FILE_INFORMATION fileInfo;
  VgBool isSuccess;
  if (isSuccess = Open (fileName, bOsShellFiles::FA_READ,bOsShellFiles::CD_OPEN_EXISTING))
  {
    isSuccess = GetFileInformationByHandle(m_fileHandle,&fileInfo);
    if (isSuccess)
    {
      FILETIME fileLastTime = fileInfo.ftLastWriteTime;
      SYSTEMTIME sysTime;
      FileTimeToSystemTime(&fileLastTime,&sysTime);

      lastWriteTime.SetTod(sysTime.wYear,	
  		                     sysTime.wMonth,			
  		                     sysTime.wDay,				
  		                     sysTime.wHour,				
  		                     sysTime.wMinute,				
  		                     sysTime.wSecond,				
  		                     sysTime.wMilliseconds);	 
      Close();
    }
  }
  return isSuccess;
}
