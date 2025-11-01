#if !defined(AFX_PLOT650_H__F3855763_0184_11D4_A856_0010B508B447__INCLUDED_)
#define AFX_PLOT650_H__F3855763_0184_11D4_A856_0010B508B447__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Plot650.h : header file
//
//#include "Pr650.h"
#include <afxwin.h>
#define NSPECTRALPOINTS	400
typedef struct PR650_SpectralData
{
	short  sNpts;
	double dDeltaLambda;
	double dLamda[NSPECTRALPOINTS];
	double dSpecData[NSPECTRALPOINTS];
	double dStartLamda;
	double dEndLamda;


}PR650_SPECTRALDATA;
/////////////////////////////////////////////////////////////////////////////
// CPlot650 window

class CPlot650 : public CWnd
{
// Construction
public:
	CPlot650();
	CWnd *     m_CWnd;
	PR650_SPECTRALDATA  m_SpectralData;
	short *r, *g, *b;

// Attributes
public:

// Operations
public:
	void PlotData();
	void PaintData() ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlot650)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPlot650();



private:

short GetBoxColors ();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlot650)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOT650_H__F3855763_0184_11D4_A856_0010B508B447__INCLUDED_)
