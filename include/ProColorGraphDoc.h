#if !defined(AFX_PROCOLORGRAPHDOC_H__E712377F_C676_40A0_9BEB_401DD76BD31D__INCLUDED_)
#define AFX_PROCOLORGRAPHDOC_H__E712377F_C676_40A0_9BEB_401DD76BD31D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProColorGraph;

class CProColorGraphDoc : public CDocument
{
public:
	CProColorGraphDoc();
	DECLARE_DYNCREATE(CProColorGraphDoc)

// Attributes
public:
//	bool MakeTheGraph();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProColorGraphDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProColorGraphDoc();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProColorGraphDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif

