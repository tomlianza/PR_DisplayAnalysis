#ifndef DATAPERSISTANCE_H_INCLUDED
#define DATAPERSISTANCE_H_INCLUDED

#include "CPreset.h"

// GetBaseName returns the path to the where program data is to be stored.
// This path does not have a trailing slash or backslash.
// In order to isolate platform differences, this GetBaseName calls
// GetPlatformBaseName which currently (as of 6/13/02) returns the directory
// in which the program resides (for Windows systems) or the user's home
// directory (for Mac OS-X).
// GetPresetPath and GetDSDBPath currently return the same path with the '\'
// (They may be modified to be different at a later time.)

#ifdef OS9_DRIVER

	#include <stdio.h>

	FILE* FSOpenInSpec( const char *fname, FSSpec *parentSpec, const char *iomode);
	OSErr FSRemoveInSpec( const char* fname, FSSpec *parentSpec);
	FSSpec* getWorkingDir();
	FSSpec *GetPCPrefsFolder();

	extern void GetPlatformBaseName(FSSpec *spec);
	extern void GetBaseName (FSSpec *spec);
	extern void GetPresetGroupPath (FSSpec *spec);
	extern void GetPresetPath (FSSpec *spec);
	extern void GetDSDBPath (FSSpec *spec);
	extern void GetMonitorProfilePath (FSSpec *spec);
#else
	extern void GetPlatformBaseName(char *location);
	extern void GetBaseName (char *location);
	extern void GetPresetGroupPath(char *location);
	extern void GetPresetPath (char *location);
	extern void GetDSDBPath (char *location);

	extern void GetMonitorProfilePath (char *location);
	char* getWorkingDir();
#endif

extern void ConvertPresetNameToFileName (char* presetName, char* fileName);
extern void ConvertPresetWithGroupNameToFileName (char* presetName, char *groupName, char* fileName);
#ifdef USE_ORIGINAL_PRESET_ARCH
extern void SetPersistantPresetGroup(char *g);
extern char *GetPersistantPresetGroup();
extern void SetPersistantPresetSource(char *s);
extern char *GetPersistantPresetSource();
#endif

extern char *GetDELIM();

#ifdef MAC_KIT
bool getBundleResourcesPath(char *path, int maxlen);
bool getAppSupportFolder(char *outBuf, int outBufSz);
#endif

#endif
