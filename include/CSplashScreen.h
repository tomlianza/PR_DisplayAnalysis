#ifdef WIN32
#if !defined(AFX_SPLASHSCREEN_H__57E92C1D_E6AD_41A5_BDB2_94A55E150D06__INCLUDED_)
#define AFX_SPLASHSCREEN_H__57E92C1D_E6AD_41A5_BDB2_94A55E150D06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSplashScreen : public CDialog
{
public:
	CSplashScreen(CWnd *parent);
		// protected constructor used by dynamic creation
	virtual ~CSplashScreen();

// Attributes
public:

// Operations
public:
	void SetColor (COLORREF rgb);
	COLORREF m_color;
	void SetStatusText(char *text, bool onTop = true);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashScreen)
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd * m_parent;
	CWnd * m_pWnd;
	CBitmap m_bmpSplash;
	char* m_text;
	char m_lastText[256];
	bool m_bIsOnTop;

	// Generated message map functions
	//{{AFX_MSG(CSplashScreen)
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
#endif // WIN32
