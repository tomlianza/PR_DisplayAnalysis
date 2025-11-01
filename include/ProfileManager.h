#if !defined(AFX_PROFILEMANAGER_H__897938E0_433F_11D3_B9F8_004033E05B37__INCLUDED_)
#define AFX_PROFILEMANAGER_H__897938E0_433F_11D3_B9F8_004033E05B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfileManager.h : header file
//
#include "MonitorWorld.h"
#include "MonitorMeasurements.h"
#include "RegistryTools.h"
#include "CalTargetDisplay.h"

typedef struct _MonitorData{

	dYxy	Red;
	dYxy	Green;
	dYxy	Blue;
	dYxy    White;
	double  dFreq;
}MonitorData;

/////////////////////////////////////////////////////////////////////////////
// CProfileManager dialog

class CProfileManager : public CDialog
{
// Construction
public:
	CProfileManager(CWnd* pParent = NULL);   // standard constructor
	CMonitorWorld  *m_ptrMonitorWorld;
	CCalTargetDisplay *m_ptrTargets;
	CRegistryTools    *m_ptrRegistry;
	MonitorData		 *m_ptrMonitorData; //Allocated in main....

	void GetMonitorData(CString csFname);
// Dialog Data
	//{{AFX_DATA(CProfileManager)
	enum { IDD = IDD_PROFILEMANAGER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfileManager)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	
protected:

	// Generated message map functions
	//{{AFX_MSG(CProfileManager)
	afx_msg void OnButtonOpenprofile();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPlot();
	afx_msg void OnDone();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void RefreshTextData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEMANAGER_H__897938E0_433F_11D3_B9F8_004033E05B37__INCLUDED_)
