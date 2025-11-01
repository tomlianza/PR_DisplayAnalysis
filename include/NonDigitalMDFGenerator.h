// NonDigitalMDFGenerator.h: interface for the CNonDigitalMDFGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NONDIGITALMDFGENERATOR_H__78F44510_6595_4B24_9BBF_FDD6674BF442__INCLUDED_)
#define AFX_NONDIGITALMDFGENERATOR_H__78F44510_6595_4B24_9BBF_FDD6674BF442__INCLUDED_

#include "DisplayTechnology.h"
#include "ManualAdjustments.h"
#ifdef LINUX
#include <string.h>
#endif
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNonDigitalMDFGenerator  
{
public:
	CNonDigitalMDFGenerator();
	virtual ~CNonDigitalMDFGenerator();

	inline void SetPath(char *path) {strcpy(m_MDFPath, path);}
	inline char *GetPath() {return m_MDFPath;}

	inline void SetName(char *name) {strcpy(m_MDFName, name);}
	inline char *GetName() {return m_MDFName;}

	inline void SetTechnology(DISPLAY_TECHNOLOGY tech) {m_technology = tech;}
	inline DISPLAY_TECHNOLOGY GetTechnology() {return m_technology;}

	inline void SetCanAdjustBrightness(bool can) {m_man.SetCanAdjustBrightness(can);}
	inline bool GetCanAdjustBrightness() {return m_man.GetCanAdjustBrightness();}
	
	inline void SetCanAdjustContrast(bool can) {m_man.SetCanAdjustContrast(can);}
	inline bool GetCanAdjustContrast() {return m_man.GetCanAdjustContrast();}
	
	inline void SetCanAdjustColorTemp(bool can) {m_man.SetCanAdjustColorTemp(can);}
	inline bool GetCanAdjustColorTemp() {return m_man.GetCanAdjustColorTemp();}
	
	inline void SetCanAdjustGains(bool can) {m_man.SetCanAdjustGains(can);}
	inline bool GetCanAdjustGains() {return m_man.GetCanAdjustGains();}

	char *GenerateMDFContents();

	bool WriteFile();
	void GetFileName(char *fname);
	bool FileExists();

	enum {MAX_GENERATED_MDF = 4096};

protected:
	char m_MDFPath[1024];
	char m_MDFName[1024];

	DISPLAY_TECHNOLOGY m_technology;
	CManualAdjustments m_man;

	char m_generatedContents[MAX_GENERATED_MDF];
};

#endif // !defined(AFX_NONDIGITALMDFGENERATOR_H__78F44510_6595_4B24_9BBF_FDD6674BF442__INCLUDED_)
