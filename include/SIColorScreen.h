#ifdef WIN32
#if !defined(AFX_SICOLORSCREEN_H__57E92C1D_E6AD_41A5_BDB2_94A55E150D06__INCLUDED_)
#define AFX_SICOLORSCREEN_H__57E92C1D_E6AD_41A5_BDB2_94A55E150D06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SIColorScreen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSIColorScreen frame

class CSIColorScreen : public CWnd
{
public:
	CSIColorScreen(CWnd *parent, int width, int height, int left=0, int top=0,
		int pct = 100, bool manageCursor = false);

		// protected constructor used by dynamic creation
	virtual ~CSIColorScreen();

// Attributes
public:

// Operations
public:
	void SetColor (COLORREF rgb);
	COLORREF GetColor() { return m_color;}
	COLORREF m_color;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSIColorScreen)
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd * m_parent;
	CWnd * m_pWnd;
	int m_width;
	int m_height;
	int m_pct;
	bool m_manageCursor;


	// Generated message map functions
	//{{AFX_MSG(CSIColorScreen)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SICOLORSCREEN_H__57E92C1D_E6AD_41A5_BDB2_94A55E150D06__INCLUDED_)
#endif // WIN32