#ifdef WIN32
#if !defined(CGRAPH_H__57E92C1D_E6AD_41A5_BDB2_94A55E150D06__INCLUDED_)
#define CGRAPH_H__57E92C1D_E6AD_41A5_BDB2_94A55E150D06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;



#define TICKLENGTH 5 // Length of tick mark in pixels
#define MAX_POINTS 256
#define MAX_PLOTS 5


typedef enum {GRAPHMODE_INT, GRAPHMODE_FLOAT} GRAPHMODE;
typedef enum {TICKMODE_MANUAL, TICKMODE_AUTO, TICKMODE_TEXT} TICKMODE;
typedef enum {TICKTYPE_STRING, TICKTYPE_NUMERIC} TICKTYPE;
typedef enum {MAXMODE_AUTO, MAXMODE_SPECIFIED} MAXMODE;
typedef enum {MINMODE_ZERO, MINMODE_SPECIFIED, MINMODE_FLOOR} MINMODE;

class _TickMarkEntry
{
public:
	_TickMarkEntry(double val, bool showValue) { m_type = TICKTYPE_NUMERIC; m_val=val; m_showValue = showValue;}
	_TickMarkEntry(int pos, CString label) {m_type = TICKTYPE_STRING; m_showValue = true; m_tickLabel = label; m_val = pos;}

	TICKTYPE m_type;
	CString m_tickLabel;	// String value to be displayed at tick position
	double m_val;			// Value at which to place the tick mark
	bool m_showValue;		// Whether or not to show the value (otherwise just tick mark)
	double GetVal() {return m_val;}
	bool GetShow() { return m_showValue;}
};
typedef list <_TickMarkEntry*> TICKMARKLIST;

class CGraph : public CView
{
protected:
	DECLARE_DYNCREATE(CGraph)
	CGraph();
public:

	CGraph(CWnd *parent, int left=0, int top=0, int wwidth=400, int wheight=300, 
			   int gPct=20, COLORREF wColor = RGB(255,255,255), COLORREF gColor= RGB(230,230,230), int maxPoints = 256);
		// protected constructor used by dynamic creation
	virtual ~CGraph();

	void Initialize(CWnd *parent, int left=0, int top=0, int wwidth=400, int wheight=300, 
			   int gPct=20, COLORREF wColor = RGB(255,255,255), COLORREF gColor= RGB(230,230,230), int maxPoints = 256);

// Attributes
public:
	virtual void AddXTick(double val, bool labelIt = true);
	virtual void AddYTick(double val, bool labelIt = true);
	virtual void AddXTick(CString label, int position);
	virtual void AddYTick(CString label, int position);
	virtual void EmptyTickList(TICKMARKLIST *tml);
	virtual void SetColors(COLORREF windowColor, COLORREF graphColor);
	virtual void SetDimensions(int left, int top, int wwidth, int wheight, int pct);
	virtual void AddDataPoint (double x, double y);
	virtual void StartPlot();
	virtual void EndGraph();
	virtual void ConvertRawDataToDisplayable(int whichPlot);
	virtual void ConvertRawDataToDisplayable();
	virtual CGraph* GetDocument();
	virtual void OnFilePrint();
	virtual void OnFilePrintPreview();
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView );
	virtual void SetPlotColor(COLORREF color);
	virtual void SetPlotType(int style);
	virtual void SetPlotLabel(CString label);
	virtual void SetPlotLabel(int id);
	virtual void SetPlotMaxMode(MAXMODE xmode, MAXMODE ymode);
	virtual void SetPlotMinMode(MINMODE xmode, MINMODE ymode);
	virtual void SetPlotSizeIncrements (double xFull, double xFraction,
		double yFull, double yFraction);
	virtual void SetPlotNumberType(GRAPHMODE xType, GRAPHMODE yType);
	virtual void SetPlotMinValue(double xMin, double yMin);
	virtual void SetPlotMaxValue(double xMax, double yMax);
	virtual void SetPlotTickType(TICKMODE xMode, TICKMODE yMode);
	virtual void SetPlotRoundingIncrement(double xVal, double yVal);
	virtual void SetGraphTitles(CString graphTitle, CString XTitle, CString YTitle);
	virtual void SetGraphTitles(int graphTitleID, int XTitleID, int YTitleID);
	virtual void GetDimensions (int *left, int *top, int *width, int *height, int *pct);
	virtual void AllocatePointMemory();
	virtual void SetMaxPoints(int maxPoints);
	virtual void SetPlotWidth(int width);


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraph)
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
		virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
		virtual void OnBeginPrinting(CDC* pDC, CPrintInfo *pInfo);
		virtual void OnEndPrinting(CDC* pDC, CPrintInfo *pInfo);
		virtual void OnPrepareDC (CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd * m_parent;
	COLORREF m_WindowBackgroundColor;
	COLORREF m_GraphBackgroundColor;
	int m_WindowTop;
	int m_WindowLeft;
	int m_WindowWidth;
	int m_WindowHeight;
	int m_gPct; // Width and height of graph as (100* pct) of window dimensions
	int m_BorderSize;
	int m_MaxPoints;

	int m_GraphWidth;
	int m_GraphHeight;
	int m_GraphTop;
	int m_GraphLeft;

	double m_GraphXMax;
	double m_GraphYMax;

	double m_GraphXMin;
	double m_GraphYMin;

	double m_XTickIncrement;
	double m_YTickIncrement;

	TICKMARKLIST XTix;
	TICKMARKLIST YTix;

	GRAPHMODE m_NumberModeX;
	GRAPHMODE m_NumberModeY;

	MAXMODE m_MaxModeX;
	MAXMODE m_MaxModeY;

	MINMODE m_MinModeX;
	MINMODE m_MinModeY;

	CString m_TitleText;
	CString m_AxisLabelX;
	CString m_AxisLabelY;

	CFont *m_Font;

	int m_NumPlots;
	COLORREF m_PlotColor[MAX_PLOTS];
	int m_PlotStyle[MAX_PLOTS];
	int m_PlotWidth[MAX_PLOTS];

	double *m_RawDataX[MAX_PLOTS];
	double *m_RawDataY[MAX_PLOTS];
	POINT *m_Points[MAX_PLOTS];

	int m_NumPoints[MAX_PLOTS];
	CString m_PlotLabel[MAX_PLOTS];
	TICKMODE m_TickModeX;
	TICKMODE m_TickModeY;

	double m_PlotIncrementFullX;
	double m_PlotIncrementFullY;
	double m_PlotIncrementFractionX;
	double m_PlotIncrementFractionY;

	double m_RoundIncrementX;
	double m_RoundIncrementY;
	
	CWnd * m_pWnd;

	// Generated message map functions
	//{{AFX_MSG(CGraph)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#endif
#endif // WIN32
