#ifndef CPRESETLIST_H_INCLUDED
#define CPRESETLIST_H_INCLUDED

#include "CPresetListBase.h"

class CPresetList : public CPresetListBase
{
public:
	virtual bool SetDefaultPreset (char *name);
	virtual bool Load();
	virtual bool Save();
};

typedef list<CPreset*> CPRESETLIST;


#endif // CPRESETLIST_H_INCLUDED
