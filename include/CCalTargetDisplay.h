#if !defined(AFX_CCALTARGETDISPLAY_H__230CBCA2_DD04_11D1_865F_444553540000__INCLUDED_)
#define AFX_CCALTARGETDISPLAY_H__230CBCA2_DD04_11D1_865F_444553540000__INCLUDED_
#include <afxwin.h>
#include "CCalTargetDisplayBase.h"
#ifdef WIN32
class CCalTargetDisplay : public CCalTargetDisplayBase, public CWnd
#else
class CCalTargetDisplay : public CCalTargetDisplayBase
#endif
{
public:
	CCalTargetDisplay();
	virtual ~CCalTargetDisplay();

	virtual void DisplayPatchColor(bool resetCWnd = true);
	virtual void DisplayBlackBackground(bool resetCWnd = true);		
	virtual void BuildTargetValues(double dGamma);
	virtual void DisplayVisibilityTarget(bool resetCWnd = true);
	

#ifdef WIN32
	CWnd * myCWnd;
	CWnd * rCwnd;// used for lut plotting;
	CWnd * gCwnd;// used for lut plotting;
	CWnd * bCwnd;// used for lut plotting;

	HWND m_patchWindowHandle;
	bool m_FillBlack;
	
	inline void SetWindow(CWnd *me) {myCWnd = me;}
	inline void SetPatchWindowHandle(HWND patchWindowHandle) {m_patchWindowHandle = patchWindowHandle;} 
	inline void SetMyWindowFromHandle() { myCWnd = CWnd::FromHandle(m_patchWindowHandle);}
	inline void SetBlackBackgroundFill(bool fill=true) {m_FillBlack = fill;}
	 void SetDimensions (int l, int r, int t, int b);
	 void xySpecDisplay();
	 void DisplayLuts(unsigned char * pRlut, unsigned char *pGlut, unsigned char *pBlut);
	 void PlotColorTempData(double x, double y);
	 void DisplayBackGroundTestTarget1();
	 void DrawVisibilityPatch(CDC * pDC, RECT *outsideRect,short innerValue, short outerValue);
	void DisplayArbitraryBitMapStretch(LPCTSTR lpszResourceName);
	void DisplayArbitraryBitMapStretch(UINT intResource);
	void DisplayArbitraryBitMap(UINT intResource );
	void DisplayArbitraryBitMap(LPCTSTR lpszResourceName );
	void DisplayArbitraryBitMapFit(LPCTSTR lpszResourceName);
	void DisplaySplitVisabilityTarget();
	//void DisplayBackGroundTestTarget1();
//	void DrawVisibilityPatch(CDC * pDC, RECT *outsideRect,short innerValue, short outerValue);
	void DisplayWhiteVisabilityTarget();
	void DisplayVisabilityRampTarget();
	void DisplayPatchColor();
	void DisplayPuckImage();
	void ColorTempLocusImage();
	void DisplayTargetHelpImage();
	
	//void DisplayLuts(unsigned char * pRlut, unsigned char *pGlut, unsigned char *pBlut);
//	void PlotColorTempData(double x, double y);
	void PlotColorCIEData(double x, double y, CWnd *CIEC_Wnd);
	void PlotColorCIEData(double x, double y, CWnd *CIEC_Wnd, short R, short G, short B); //gamut outline R,G,B color

	int  DisplayWindowResource;//Application should initialize these variables before use
	
	short Red;
	short Green;
	short Blue;
	long  lSettleTime; // in millisecs
	xy_SpecDisplay		SpecData; // data for xy target adjustment apps.
	dxy_CTDisplay       CTdata;   // data for color temperature plot 
#endif
};
#endif
