#if !defined(AFX_SEQUELCALIBRATORLIST_H__230CBCA1_DD04_11D1_865F_444553540000__INCLUDED_)
#define AFX_SEQUELCALIBRATORLIST_H__230CBCA1_DD04_11D1_865F_444553540000__INCLUDED_

#ifdef WIN32
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#endif

#ifdef WIN32
#pragma warning (disable:4786)
#endif

#include "CSequelCalibrator.h"
#include <list>
using namespace std;

class CSequelCalibratorList
{
public:
	CSequelCalibratorList();
	virtual ~CSequelCalibratorList();

	list <CSequelCalibrator*> m_List;
	inline int GetNCalibrators() {return m_List.size();}
	
	virtual bool Init();	// Do whatever is necessary on initialization
	virtual void Cleanup(); // call at end to ripple through and delete all entries
};

#endif // !defined(AFX_SEQUELCALIBRATORLIST_H__230CBCA1_DD04_11D1_865F_444553540000__INCLUDED_)
