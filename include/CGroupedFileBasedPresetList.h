#ifndef CGROUPEDFILEBASEDPRESETLIST_H_INCLUDED
#define CGROUPEDFILEBASEDPRESETLIST_H_INCLUDED

#include "CFileBasedPresetList.h"
#include "DataPersistance.h"


typedef list<std::string*> STRINGLIST;

#ifdef USE_ORIGINAL_PRESET_ARCH

/**
\brief CGroupedFileBasedPresetList is a preset list that can be initialized from a folder.

CGroupedFileBasedPresetList is a preset list that can be initialized from a set of  file system based presets
which must all be stored in one folder. In this folder there are two files:
<ul> 
<li><b>"PresetGroupList"</b> - contains a list of the names of the available groups, separated by an EOL
<li><b>"DefaultPresetGroup"</b> - contains the name of the default group, terminated with an EOL
</ul>

This folder must also have a folder for each group mentioned in the PresetGroupList file. 
See the documentation for CFileBasePresetList for a description of that folder.

The files are EOL platform neutral, they can end in CR, LF, or CRLF.

**/

class CGroupedFileBasedPresetList : public CFileBasedPresetList
{
public:
	CGroupedFileBasedPresetList();
	virtual ~CGroupedFileBasedPresetList();

//////////////////////////////////////////////////////////////////// 
/// \brief Inits the preset list
///
/// This method is called when an application has no presets loaded and wishes to
/// initialize a CGroupedFileBasedPresetList from a group of presets stored on the file system.	
/// You should only call this method on an empty CGroupedFileBasedPresetList. If you do not
/// want to use groups you should use CFileBasedPresetList, if you just want to accept the
/// compiled in defaults, you should use CPresetList.
///
///\param defaultFolder is used as the source for the list of available preset groups. 
/// It should be a delimeter terminated full pathname that points to the folder on disk 
/// that contains the preset groups.
///
///\param defaultGroup is used as the group that is selected from the available groups. If this is NULL, then the "Default Group" file is used. This should be NULL in normal use.
/// \sa CFileBasedPresetList
/// \sa CPresetList
///
///
//////////////////////////////////////////////////////////////////// 
	virtual bool InitDefaultList (char *defaultFolder, char *defaultGroup);
//////////////////////////////////////////////////////////////////// 
/// \brief Accessor for the GroupList
//////////////////////////////////////////////////////////////////// 
	inline STRINGLIST& GetGroupList() {return m_GroupList;}
//////////////////////////////////////////////////////////////////// 
/// \brief Delete all presets
///
/// This method deletes
///
	virtual bool CGroupedFileBasedPresetList::DeleteAll(bool readOnlyToo);
	
	virtual void SetDefaultGroup(char *g);
	virtual char * GetDefaultGroup();
	
	// the preset source is GLOBAL to the application, not to the instance of the object
	// this is very different from SetDefaultGroup (above).  That routine sets the m_CurrentGroup
	// member, which could be used by an application that displays the list of groups, for example.
	// These routine manipulate the group's static global in the DataPersistance module.
	// calling SetDefaultGroup SHOULD trigger a call in InitDefaultList with the proper source
	// and the new group name.
	virtual void SetPresetGroup(char *g);
	virtual char * GetPresetGroup();
	
	virtual bool Load();
	virtual bool Save();
protected:
		STRINGLIST m_GroupList;
	std::string *m_CurrentGroup;
	
private:
	virtual bool InitPrefsFromFolder(char *sourceFolder, char *groupFolder);
	void DeleteCurrentGroup();
};

#else
	// grouped based presets are not part of the new preset architecture
	// making a bogus class eliminates MOST of the compile errors.  You
	// will still have to #ifdef Group related calls, but at least the #import
	// and new calls are fine

class CGroupedFileBasedPresetList : public CFileBasedPresetList
{
public:
	CGroupedFileBasedPresetList();
	virtual ~CGroupedFileBasedPresetList();	
};
#endif

#endif

