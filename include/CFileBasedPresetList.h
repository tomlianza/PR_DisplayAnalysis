#ifndef CFILEBASEDPRESETLIST_H_INCLUDED
#define CFILEBASEDPRESETLIST_H_INCLUDED

#include "CPresetList.h"
#include "DataPersistance.h"

class CFileBasedPresetList : public CPresetList
{
public:
	virtual bool InitDefaultList ();
	virtual bool InitDefaultList (char *name);
	virtual bool InitPrefsFromFolder(char *sourceFolder);
	
	// the preset source is GLOBAL to the application, not to the instance of the object
	virtual void SetPresetSource(char *g);
	virtual char * GetPresetSource();

private:
};
#endif
