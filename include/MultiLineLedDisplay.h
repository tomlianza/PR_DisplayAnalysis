#if !defined(AFX_MULTILINELEDDISPLAY_H__469212A0_32A0_11D2_B9F5_004033E05B37__INCLUDED_)
#define AFX_MULTILINELEDDISPLAY_H__469212A0_32A0_11D2_B9F5_004033E05B37__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MultiLineLedDisplay.h : header file
//
	typedef struct LEDchar 
{
  char Code ;
  char BitCode[7];
}LEDCHAR;

#define N_LED_LINES_MAX    32
#define N_LED_CHARS_MAX    255
typedef struct LEDdisplay 
{
	short nLines;
	short nCharsPerLine; 
	short AspectRatio;
	short DisplayWidth;
	short DisplayHeight;
	short Red;
	short Green;
	short Blue;
	short x_offset;
	short y_offset;
	char LineStrings[N_LED_LINES_MAX][N_LED_CHARS_MAX];
	short FRAME_RESOURCE_ID;
	CWnd		*mainCWnd;
}LEDdisplay;

typedef enum BarEncoding
{
	BELinear = 0,
	BELog
}BarEncoding;

/////////////////////////////////////////////////////////////////////////////
// CMultiLineLedDisplay window
/*******************************************************************\
Typical structure setup before calling define Led Display:

    MyDisplay.whichDisplay.nLines = 4;
	MyDisplay.whichDisplay.nCharsPerLine = 8; 
	MyDisplay.whichDisplay.AspectRatio = 1;
	MyDisplay.whichDisplay.DisplayWidth = 220;
	MyDisplay.whichDisplay.DisplayHeight = 150;
	MyDisplay.whichDisplay.Red = 255;
	MyDisplay.whichDisplay.Green =192;
	MyDisplay.whichDisplay.Blue = 0;
	MyDisplay.whichDisplay.x_offset = 0;
	MyDisplay.whichDisplay.y_offset = 0;
	MyDisplay.whichDisplay.FRAME_RESOURCE_ID = IDC_METER;
	MyDisplay.whichDisplay.mainCWnd = GetDlgItem(IDC_METER);
	MyDisplay.DefineLedDisplay();

	strcpy(MyDisplay.whichDisplay.LineStrings[0]," This");
	strcpy(MyDisplay.whichDisplay.LineStrings[1],"  is");
	strcpy(MyDisplay.whichDisplay.LineStrings[2],"   a");
	strcpy(MyDisplay.whichDisplay.LineStrings[3]," Test");

\**********************************************************************/
class CMultiLineLedDisplay 
{
// Construction
public:
	CMultiLineLedDisplay();
	
	LEDdisplay whichDisplay;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiLineLedDisplay)
	//}}AFX_VIRTUAL

// Implementation

int DefineLedDisplay();
int RefreshLedDisplay();
bool SetLineString(short whichLine, char * whichString);
void DrawRGB_BarGraph(double Red, double Green, double Blue,BarEncoding whichCode);

public:
	virtual ~CMultiLineLedDisplay();
CDC			*mainCDC;
	// Generated message map functions
protected:
	//{{AFX_MSG(CMultiLineLedDisplay)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	

private:



 short sgWidth,sgHeight,sgNlines,sgNchars,sgAspect,sgX,sgY,sgLineWidth,sgBarWidth;
 short sgRed,sgGreen,sgBlue;
 char *cPtr2LineBuffs[10];

//int RefreshLedDisplayLine(HWND hwnd, LEDdisplay *whichDisplay,short whichLine);
int DrawLedChar( short x, short y, short width, short height, char WhichChar,short red,short green, short blue);
 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILINELEDDISPLAY_H__469212A0_32A0_11D2_B9F5_004033E05B37__INCLUDED_)
