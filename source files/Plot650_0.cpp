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

	// basic guards
	if (m_SpectralData.sNpts <= 0 || m_SpectralData.dSpecData == nullptr)
		return;

	int npts = (int)m_SpectralData.sNpts;
	// cap to storage size
	if (npts > NSPECTRALPOINTS) npts = NSPECTRALPOINTS;

	double dMax = -1.0;
	for (int i = 0; i < npts; ++i)
	{
		double v = m_SpectralData.dSpecData[i];
		if (v > dMax) dMax = v;
	}

	// avoid divide-by-zero / invalid normalization
	if (!(dMax > 0.0))
	{
		// nothing meaningful to plot
		for (int i = 0; i < npts; ++i) mp_Height[i] = 0.0;
	}
	else
	{
		for (int i = 0; i < npts; ++i)
			mp_Height[i] = m_SpectralData.dSpecData[i] / dMax;
	}

	GetBoxColors();
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
	if (m_CWnd == nullptr) return; // guard

	CDC* cDC = m_CWnd->GetDC();
	if (cDC == nullptr) return;

	CRect cRect;
	m_CWnd->GetClientRect(&cRect);

	int npts = (int)m_SpectralData.sNpts;
	if (npts <= 0)
	{
		m_CWnd->ReleaseDC(cDC);
		return;
	}
	// cap to arrays' capacity
	if (npts > NSPECTRALPOINTS) npts = NSPECTRALPOINTS;

	double dMagnification = double(cRect.right - cRect.left) / (double)m_SpectralData.sNpts;
	std::unique_ptr<short[]> s_xAxis(new short[npts]);
	for (int i = 0; i < npts; ++i)
		s_xAxis[i] = static_cast<short>(i * dMagnification);

	double dxDelta = double(cRect.right - cRect.left) / (double)m_SpectralData.sNpts;

	// paint background + grid (existing code kept)
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(128, 128, 128));
	CBrush* oldBrush = (CBrush*)cDC->SelectObject(&myBrush);
	cDC->Rectangle(cRect.left, cRect.top, cRect.right, cRect.bottom);
	// ... grid lines same as before ...
	cDC->SelectObject(GetStockObject(NULL_PEN));

	// create brushes dynamically sized to npts (avoid fixed BrushArray overflow)
	std::vector<CBrush> brushes;
	brushes.resize(npts);
	for (int i = 0; i < npts; ++i)
	{
		int red = mp_r[i];
		int green = mp_g[i];
		int blue = mp_b[i];
		brushes[i].CreateSolidBrush(RGB(red, green, blue));
		cDC->SelectObject(&brushes[i]);

		int left = s_xAxis[i];
		int top = cRect.bottom - static_cast<int>(cRect.bottom * mp_Height[i]);
		int right = left + static_cast<int>(dxDelta);
		int bottom = cRect.bottom;
		cDC->Rectangle(left, top, right, bottom);
	}

	// draw grid lines again if needed...
	m_CWnd->ReleaseDC(cDC);
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

  
  // ...
  r = &mp_r[0];
  g = &mp_g[0];
  b = &mp_b[0];
  // zero full arrays (use sizeof to get bytes)
  memset(r, 0, sizeof(mp_r));
  memset(g, 0, sizeof(mp_g));
  memset(b, 0, sizeof(mp_b));
  // ...
  // only plot the visible spectrum in color
    nBars = m_SpectralData.sNpts;
	dWLRange = m_SpectralData.dEndLamda - m_SpectralData.dStartLamda;
	dEndVisible = 780;

    deltaWL = m_SpectralData.dDeltaLambda;
	int iVisibleEnd = (int)((dEndVisible - m_SpectralData.dStartLamda) / deltaWL);


	for (i = 0; i < iVisibleEnd; i++)
	{

		CWL = 380 + i*(short)deltaWL ;

		if (CWL < 450.0)

		{
			r[i] = 0;
			g[i] = 0;
			b[i] = 255;
			;
		}
		if ((CWL >= 450.) && (CWL < 550.))

		{
			r[i] = 0;
			g[i] = ((CWL-450))* 2.55;
			//g[i] = 255;
			b[i] = 255 -(((CWL-450))*2.55);
		}


		if ((CWL >= 550.) && (CWL < 650.))

		{
			r[i] = 255;
			g[i] = 255 - (((CWL-550)) * 2.55);
			b[i] = 0;
		}

		if (CWL >= 650)

		{
			r[i] = 255;
			g[i] = 0;
			b[i] = 0;

		}

	}
 
  return nBars;
}