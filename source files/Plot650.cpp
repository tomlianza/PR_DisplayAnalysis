// Plot650.cpp : implementation file
//

////#include "pr650 test.h"
#include "stdafx.h"
#include "Plot650.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static short mp_r[NSPECTRALPOINTS * 2], mp_g[NSPECTRALPOINTS * 2], mp_b[NSPECTRALPOINTS * 2];
static double mp_Height[NSPECTRALPOINTS];

/////////////////////////////////////////////////////////////////////////////
// CPlot650

CPlot650::CPlot650()
{

		//GetBoxColors ();
}

CPlot650::~CPlot650()
{
}


BEGIN_MESSAGE_MAP(CPlot650, CWnd)
	//{{AFX_MSG_MAP(CPlot650)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPlot650 message handlers
void CPlot650::PlotData()
{

	double dMax,dTest;
	short i;
	dMax = -1.0;
	dTest = 0;
	for (i = 0; i < m_SpectralData.sNpts-1; i++)
	{
		dTest = m_SpectralData.dSpecData[i];
		if (dTest >= dMax)
			dMax = dTest;
	}
	// normalize the data based upon the maximum value found
	for(i=0; i<m_SpectralData.sNpts; i++)
	{
			
		mp_Height[i] = m_SpectralData.dSpecData[i]/dMax;
	}
	GetBoxColors();

	PaintData();

}





/****************************************************************************

    FUNCTION: void PaintWindow ()

    PURPOSE:  paints a window 

    MESSAGES:

	

****************************************************************************/
void CPlot650::PaintData() 

{

CBrush myBrush,*oldBrush,BrushArray[NSPECTRALPOINTS];
CPen blackPen,*oldPen;
CDC  *cDC;
CRect cRect;
short i;
short xDelta,xCurrent;



	cDC = m_CWnd->GetDC();
	m_CWnd->GetClientRect( &cRect);
	xCurrent = (short)cRect.left;
	xDelta = (short)( cRect.right - cRect.left)/m_SpectralData.sNpts;
	myBrush.CreateSolidBrush (RGB(128,128,128));
	oldBrush = (CBrush *)cDC->SelectObject(myBrush);
	cDC->Rectangle(cRect.left,cRect.top,cRect.right,cRect.bottom);
	
	
	//grid lines	
	blackPen.CreatePen(PS_DOT,2,RGB(255,255,255));
	oldPen = (CPen *)cDC->SelectObject(blackPen);
	cDC->MoveTo(cRect.left,cRect.bottom);
	cDC->LineTo(cRect.left,cRect.top);
	cDC->MoveTo(cRect.right/4,cRect.bottom);
	cDC->LineTo(cRect.right/4,cRect.top);
	cDC->MoveTo(cRect.right/2,cRect.bottom);
	cDC->LineTo(cRect.right/2,cRect.top);
	cDC->MoveTo(3*cRect.right/4,cRect.bottom);
	cDC->LineTo(3*cRect.right/4,cRect.top);
	cDC->MoveTo(cRect.right,cRect.bottom);
	cDC->LineTo(cRect.right,cRect.top);
	
	cDC->MoveTo(cRect.left,cRect.bottom);
	cDC->LineTo(cRect.right,cRect.bottom);
	cDC->MoveTo(cRect.left,cRect.bottom/4);
	cDC->LineTo(cRect.right,cRect.bottom/4);
	cDC->MoveTo(cRect.left,cRect.bottom/2);
	cDC->LineTo(cRect.right,cRect.bottom/2);
	cDC->MoveTo(cRect.left,3*cRect.bottom/4);
	cDC->LineTo(cRect.right,3*cRect.bottom/4);
	cDC->MoveTo(cRect.left,cRect.top);
	cDC->LineTo(cRect.right,cRect.top);
	cDC = m_CWnd->GetDC();
	//DeleteObject(cDC->SelectObject(oldPen));
	//return;
	cDC->SelectObject(GetStockObject(NULL_PEN));
	/* note that a height will be given for each bar and passed in an array */
	int left, top, right, bottom;
	int red, green, blue;;

	// where does the wavelength 780 .0 fall in the array
	// 780.0 - 380.0 = 400.0	
	// 400.0/5 = 80.0
	// 780.0 - 380.0 = 400.0

	
	for (i=0; i< m_SpectralData.sNpts; i++)
	   {
		red = mp_r[i] ;	
		green = mp_g[i];
		blue = mp_b[i];
	    BrushArray[i].CreateSolidBrush (RGB(red,green,blue));
		
		cDC->SelectObject(&BrushArray[i]);
		left = xCurrent;
		top = cRect.bottom - (int)(cRect.bottom*mp_Height[i]);	
		//right = xCurrent+((cRect.right-cRect.left)/ m_SpectralData.sNpts);
		right = xCurrent +2;
		bottom = cRect.bottom;
		cDC->Rectangle(left,top,right,bottom);
		//cDC->Rectangle(xCurrent,cRect.bottom - (int)(cRect.bottom*mp_Height[i]),((i * (long)(cRect.right))/m_SpectralData.sNpts),cRect.bottom);
		xCurrent = (i * (cRect.right)) / m_SpectralData.sNpts;
		//DeleteObject(cDC->SelectObject(myBrush));
		} 

	//Sleep(100);
	
	//blackPen.CreatePen(PS_DOT,1,RGB(0,0,0));
	//cDC->SelectObject(blackPen);
	cDC->MoveTo(cRect.left,cRect.bottom);
	cDC->LineTo(cRect.left,cRect.top);
	cDC->MoveTo(cRect.right/4,cRect.bottom);
	cDC->LineTo(cRect.right/4,cRect.top);
	cDC->MoveTo(cRect.right/2,cRect.bottom);
	cDC->LineTo(cRect.right/2,cRect.top);
	cDC->MoveTo(3*cRect.right/4,cRect.bottom);
	cDC->LineTo(3*cRect.right/4,cRect.top);
	cDC->MoveTo(cRect.right,cRect.bottom);
	cDC->LineTo(cRect.right,cRect.top);
	
	cDC->MoveTo(cRect.left,cRect.bottom);
	cDC->LineTo(cRect.right,cRect.bottom);
	cDC->MoveTo(cRect.left,cRect.bottom/4);
	cDC->LineTo(cRect.right,cRect.bottom/4);
	cDC->MoveTo(cRect.left,cRect.bottom/2);
	cDC->LineTo(cRect.right,cRect.bottom/2);
	cDC->MoveTo(cRect.left,3*cRect.bottom/4);
	cDC->LineTo(cRect.right,3*cRect.bottom/4);
	cDC->MoveTo(cRect.left,cRect.top);
	cDC->LineTo(cRect.right,cRect.top);
	//DeleteObject(cDC->SelectObject(oldPen));
	//m_CWnd->ReleaseDC(cDC);
	
	


}



/****************************************************************************

    FUNCTION: short GetBoxColors (cRect *, short * ,short* ,short*)

    PURPOSE:  calculates the rainbow colors and sets the number of interger cRects 

    MESSAGES:

	

****************************************************************************/
 short CPlot650::GetBoxColors ()
 {
 
  short nBars ;
  long i;
  double CWL, deltaWL,dWLRange,dEndVisible;

  
  r = &mp_r[0];
  g = &mp_g[0];
  b = &mp_b[0];
  memset(r, 0, NSPECTRALPOINTS);
  memset(g, 0, NSPECTRALPOINTS);
  memset(b, 0, NSPECTRALPOINTS);
  // only plot the visible spectrum in color
    nBars = m_SpectralData.sNpts;
	dWLRange = m_SpectralData.dEndLamda - m_SpectralData.dStartLamda;
	dEndVisible = 780;

    deltaWL = m_SpectralData.dDeltaLambda;
	int iVisibleEnd = (int)((dEndVisible - m_SpectralData.dStartLamda) / deltaWL);


	for (i = 0; i < iVisibleEnd; i++)
	{

		CWL = 380 + i ;

		if (CWL < 480.0)

		{
			r[i] = 0;
			g[i] = 0;
			b[i] = 255;
			;
		}
		if ((CWL >= 480.) && (CWL < 580.))

		{
			r[i] = 0;
			g[i] = (100-i)*2.5;
			b[i] = 255 -(100-i)*2.5;
		}


		if ((CWL >= 580.) && (CWL < 680.))

		{
			r[i] = (200-i)*2.5;
			g[i] = 255 - (200 - i) * 2.5;
			b[i] = 0;
		}

		if (CWL >= 680)

		{
			r[i] = 255;
			g[i] = 0;
			b[i] = 0;

		}

	}
 
  return nBars;
}