#ifndef FILE_UTILS
#define FILE_UTILS

// //////////////////////////////////////////////////////////////////////////////
//  NAME:        RealFileClass 
//  DESCRIPTION: this class manages one real file. real file is a file that is 
//               actually placed on a disk. the class is almost a simple cover of
//               the WIN32 HANDLE of a file. from the moment that the method Open
//               succeeds, this object is related to that file. 
//          
//               all the functions return VgBool which can be used to know if the
//               operation was successful or not. for more details, you can check
//               the inner status after each operation. this status contain more
//               details about what happened. 
//
//               all the method that gets as a parameter CreationDisposition 
//               value. the meaning of it is exactly as in WIN32. for help, you 
//               seek the same value, without the CD_ initial : CD_OPEN_EXISTING
//               is the same as OPEN_EXISTING of WIN32 (search "OpenFile")
// 
//               this object holds the name file handled as the inner name. this
//               is done for giving the possibilty for working with a file, and 
//               then manipulate it (Copy it to another name, Move it, Delete 
//               it).             
//   
//  INHERITS:    bTypesBasicClass::VgBasicClass
// //////////////////////////////////////////////////////////////////////////////
class RealFileClass : public BaseFilesClass
{
public:

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        empty constructor
  //  DESCRIPTION: 
  // ////////////////////////////////////////////////////////////////////////////
  RealFileClass();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Open
  //  DESCRIPTION: opens the wanted file with the desired access. the third 
  //               parameter define the policy of when to open a file in 
  //               different cases. if you open file for reading and the file
  //               does not exist, or if you want to open a file for writing 
  //               and the file already exist...
  //
  //               on failure that status may hold these error codes:
  //                 
  //               o EC_FILE_ALREADY_OPENED - the method Open was called already,
  //                    another file should be opened through another instance or
  //                    after using the Close method
  //               o EC_FILE_NOT_FOUND - the desired file was to be exist, but was
  //                    not found
  //               o EC_PATH_NOT_FOUND - the path given, does not exist
  //               o EC_FILE_EXISTS - you wanted to create a file while the file
  //                    already exist. this can be done only by using 
  //                    CD_CREATE_ALWAYS. if not, this error occurs
  //               o EC_SHARING_VIOLATION - this happens when someone already 
  //                    opened the file and you want to use it in an unpermitted
  //                    way (the only permitted way is for reading)
  //               o EC_CANNOT_OPEN_FILE - other problem
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  void SetError(VgUInt errCode, VgChar* text);

  VgBool Open (
    const FileNameClass& fileName,                 // IN
    VgFileAccessEnum desiredAccess,                // IN
    VgCreationDispositionEnum creationDisposition, // IN
    VgShareModeEnum fileShareMode = SM_FILE_SHARED_READ
  );

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Close
  //  DESCRIPTION: closes the current handled file. the only problems that might 
  //               occured, are that the file is already closed (or never been
  //               opened). corrupted handle should not happen, if so, it is not
  //               good. 
  //                 
  //               on failure that status may hold these error codes:
  //                 
  //               o EC_FILE_ALREADY_CLOSED - there is nothing to close
  //               o EC_INVALID_HANDLE - as told, should light red alert
  //               o EC_ERROR_IN_CLOSING_FILE - other problem
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  VgBool Close ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Read
  //  DESCRIPTION: reads from the file up to 'noOfBytesToRead' into 'buffer'. 
  //               the number of bytes actualy read are returned by reference
  //               through noOfBytesRead
  //                 
  //               on failure that status may hold these error codes:
  //                 
  //               o EC_NO_FILE_IS_OPENED - file must be opened if you want to 
  //                    read from a file
  //               o EC_NOT_ALL_DATA_READ - this is NOT an error, just a warning
  //                    it happens if you tried to read more than the file has
  //               o EC_INVALID_HANDLE - should not happened, red alert
  //               o EC_READ_ACCESS_DENIED - the file was opened for wrinting, 
  //                    reading from it fails
  //               o EC_CANNOT_READ_FROM_FILE - other problem
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  virtual VgBool Read (
    VgUByte* buffer,          // OUT
    VgUInt   noOfBytesToRead, // IN
    VgUInt&  noOfBytesRead    // OUT
  );
  
  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Write
  //  DESCRIPTION: write data from 'buffer' to the file. the number of bytes to
  //               write is 'noOfBytesToWrite'. the number of bytes actually
  //               writen is returned by reference through 'noOfBytesWriten'
  //                 
  //               on failure that status may hold these error codes:
  //                 
  //               o EC_NO_FILE_IS_OPENED - file must be opened if you want to 
  //                    write to a file
  //               o EC_NOT_ALL_DATA_WRITEN - this is an error, not all the 
  //                    data was writen
  //               o EC_INVALID_HANDLE - should not happened, red alert
  //               o EC_READ_ACCESS_DENIED - the file was opened for reading, 
  //                    wrinting to this file fails
  //               o EC_CANNOT_WRITE_TO_FILE - other problem
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  virtual VgBool Write (
    const VgUByte* buffer,   // IN
    VgUInt noOfBytesToWrite, // IN
    VgUInt& noOfBytesWriten  // OUT
  );

  
  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Copy
  //  DESCRIPTION: copies the recent file that was opened AND CLOSED at this
  //               instance to 'destinationFileName'. this operation should not
  //               be called if you didn't opened and closed a file (it would 
  //               always fail). if you want that the operation will succeed even
  //               when the file 'destinationFileName' already exist, 
  //               set creationDisposition to CD_CREATE_ALWAYS, otherwise the 
  //               operation would fails. the inner file name remains the same
  //               after the operation is done
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  VgBool Copy (
    const FileNameClass& destinationFileName,     // IN
    VgCreationDispositionEnum creationDisposition // IN
  );

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Move
  //  DESCRIPTION: moves the recent file that was opened AND CLOSED at this
  //               instance to 'destinationFileName'. this operation should not
  //               be called if you didn't opened and closed a file (it would 
  //               always fail). if you want that the operation will succeed even
  //               when the file 'destinationFileName' already exist, 
  //               set creationDisposition to CD_CREATE_ALWAYS, otherwise the 
  //               operation would fails. on success, the inner name is changed
  //               to be 'destinationFileName'
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  VgBool Move (
    const FileNameClass& destinationFileName,     // IN
    VgCreationDispositionEnum creationDisposition // IN
  );

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Delete
  //  DESCRIPTION: deletes the recent file that was opened AND CLOSED at this
  //               instance to 'destinationFileName'. this operation should not
  //               be called if you didn't opened and closed a file (it would 
  //               always fail). on success, the inner name is becomes empty
  //               string
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  VgBool Delete ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        SetFilePointer
  //  DESCRIPTION: this method is another name of "seek". you can use this method
  //               to move in the file. 'moveMethod' may be from-start, 
  //               from-current-pos, from-file-end. 'distance' is what it sounds
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  virtual VgBool SetFilePointer (
    VgSDWord distance,          // IN
    VgMoveMethodEnum moveMethod // IN 
  );

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        GetFilePointer
  //  DESCRIPTION: this method returns you how many bytes are you far from the 
  //               begining of the file. or -1 in case that no file is opened, or
  //               other problem occured
  //  RETURNS:     VgSDWord
  // ////////////////////////////////////////////////////////////////////////////
  virtual VgSDWord GetFilePointer ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        GetSize 
  //  DESCRIPTION: it will leave the file pointer at the same position and return
  //               the current size of the file. this method does not harm the 
  //               file pointer
  //  RETURNS:     VgUInt 
  // ////////////////////////////////////////////////////////////////////////////
  virtual VgUInt GetSize ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        IsEof
  //  DESCRIPTION: is it the end-of-file?
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  VgBool IsEof ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        IsEof
  //  DESCRIPTION: is it the begining-of-file?
  //  RETURNS:     VgBool
  // ////////////////////////////////////////////////////////////////////////////
  VgBool IsBof ();


  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        GetStatus
  //  DESCRIPTION: returns the inner status
  //  RETURNS:     const bTypesErrors::VgStatusClass&
  // ////////////////////////////////////////////////////////////////////////////
  const bTypesErrors::VgStatusClass&
    GetStatus () const;

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        GetFileName()
  //  DESCRIPTION: Returns the File name  // By Elad Rave
  //  RETURNS:     bTypesStrings::VgStringClass 
  // ////////////////////////////////////////////////////////////////////////////
  bTypesStrings::VgStringClass GetFileName();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        GetFileLastWriteTime()
  //  DESCRIPTION: function retrieves last write time for a specified file
  //  RETURNS:     VgBool return VgTrue if successed 
  // ////////////////////////////////////////////////////////////////////////////
  VgBool GetFileLastWriteTime(bOsShellFiles::FileNameClass fileName,
                              bTimeTod::TodClass& lastWriteTime);

private:

  CStdString m_fileName;
  HANDLE m_fileHandle; 

  static DWORD DesiredAccessEnumToMask (
    VgFileAccessEnum desiredAccess);
  static DWORD CreationDispositionEnumToMask (
    VgCreationDispositionEnum creationDisposition);
  static DWORD ShareModeEnumToMask (
    VgShareModeEnum shareMode);
  static DWORD MoveMethodEnumToMask (
    VgMoveMethodEnum moveMethod);

  void GetOpenError (const FileNameClass& fileName);
  void GetCloseError ();
  void GetReadError ();
  void GetWriteError ();
};

#endif