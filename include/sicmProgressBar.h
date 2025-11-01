#error OBSOLETE



#if !defined(AFX_SICMPROGRESSBAR_H__CFF403A7_2357_11D5_A856_0010B508B447__INCLUDED_)
#define AFX_SICMPROGRESSBAR_H__CFF403A7_2357_11D5_A856_0010B508B447__INCLUDED_

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif
// sicmProgressBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CsicmProgressBar window

#ifndef WIN32
// Dummy CsicmProgressBar class to allow for ease of porting
class CsicmProgressBar
{
public:
	CsicmProgressBar() {};
	
// Attributes
public:
	//bool						m_bUseCustomControl;
	//CProgressCtrl				*m_StandardCtrl; 
	//CString						m_csDescriptiveText;
	//CString                     m_csComment;

	//HWND						m_DescriptiveTextWindowHandle;
	//HWND						m_CommentTextWindowHandle;
	
// Operations
public:
	inline bool						SetFractionalProgress(double dFraction) { return true;}
	virtual ~CsicmProgressBar() {};
};
#else
class CsicmProgressBar : public CProgressCtrl
{
// Construction
public:
	CsicmProgressBar();
	
// Attributes
public:
	bool						m_bUseCustomControl;
	CProgressCtrl				*m_StandardCtrl; 
	CString						m_csDescriptiveText;
	CString                     m_csComment;

	HWND						m_DescriptiveTextWindowHandle;
	HWND						m_CommentTextWindowHandle;
	
// Operations
public:
	bool						SetFractionalProgress(double dFraction);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CsicmProgressBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CsicmProgressBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CsicmProgressBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SICMPROGRESSBAR_H__CFF403A7_2357_11D5_A856_0010B508B447__INCLUDED_)
