#ifndef CPRESETLISTBASE_H_INCLUDED
#define CPRESETLISTBASE_H_INCLUDED

#ifdef DONT_INCLUDE_LIST
#else
	#include <list>
#endif

using namespace std;
#include "CPreset.h"

class CPresetListBase
{
public:
	CPresetListBase();
	virtual ~CPresetListBase();
	inline CPRESETLIST& GetList() {return m_List;}
	inline int GetNumPresets() {return m_List.size();}
	virtual bool Load() = 0;
	virtual bool Save() = 0;
	virtual bool DeleteAll(bool readOnlyToo = false);
	virtual void Erase();
	virtual bool Add(CPreset *p) {m_List.push_back(p); return true;}
	CPreset* GetFromName(char *name);
	virtual bool SetDefaultPreset (char *name) = 0;
	CPreset* GetDefaultPreset();
	virtual bool Delete(CPreset *p);
	virtual bool InitDefaultList();
	virtual bool HasExpertPreset();

#ifdef USE_ORIGINAL_PRESET_ARCH
#else
	virtual CPreset *CreateElement();
#endif
    
protected:
	CPRESETLIST m_List;
	CPreset *m_CurrentPreset;
};

#endif //CPRESETLISTBASE_H_INCLUDED
