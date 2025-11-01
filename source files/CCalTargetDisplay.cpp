#include "stdafx.h"
#include "CCalTargetDisplay.h"
#include "math.h"
 
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define CUBED(x)       (x*x*x)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static bool lookedForFile = false;
static bool fullScreenPatch = false;

CCalTargetDisplay::CCalTargetDisplay()
{
		lSettleTime = 250;
#ifdef WIN32
		m_FillBlack = false;

	// For testing use, we support a full-screen patch if "c:\DRGFSP.txt"
	// is found on the disk. We'll look for that file once and if found, 
	// set a flag to indicate that fact.
	
	if (!lookedForFile)
	{
		FILE *fp = fopen("C:\\drgfsp.txt", "r");
		if (fp)
		{
			fclose(fp);
			fullScreenPatch = true;
		}
		lookedForFile = true;
	}
#endif
}

CCalTargetDisplay::~CCalTargetDisplay()
{
	
}

#ifdef WIN32
void CCalTargetDisplay::SetDimensions (int l, int r, int t, int b)
{
	SetMyWindowFromHandle();
	myCWnd->SetWindowPos(&wndNoTopMost, 100, t, 100, 100, 0);
}
#endif

void CCalTargetDisplay::DisplayPatchColor(bool resetCWnd)
{
#ifdef WIN32
	CDC *pDC;
	RECT wRect,tRect;
	CBrush nBrush,*oBrush;
	CPen  nPen, *oPen;
	short ccx,ccy,Width,Height;   
	
	if (resetCWnd)
		SetMyWindowFromHandle();

	pDC = myCWnd->GetDC();
	myCWnd->GetClientRect(&wRect);
	
		
	// find center of box 
		ccx =(short) ((wRect.right - wRect.left)/2) ;
		ccy = (short)(wRect.bottom - wRect.top)/2 ;

        Width = (short)(ccx * 1.); //calculate relative width
		Height = (short)(ccy * 1.);
		ccx += (short)wRect.left ; // shift the center to the proper place;
		tRect.left = ccx-Width;
		tRect.top =  ccy+Height;
		tRect.right = ccx+Width;
		tRect.bottom = ccy-Height;

		nBrush.CreateSolidBrush(RGB (192,192,192));
		oBrush = pDC->SelectObject(&nBrush);
		nPen.CreatePen(PS_SOLID, 1,RGB (192,192,192));
		oPen = pDC->SelectObject(&nPen);

		pDC->SelectObject(oBrush)->DeleteObject();
		pDC->SelectObject(oPen)->DeleteObject();
		nBrush.CreateSolidBrush(RGB (Red,Green,Blue));
		oBrush = pDC->SelectObject(&nBrush);
		nPen.CreatePen(PS_SOLID, 1,RGB (Red,Green,Blue));
		oPen = pDC->SelectObject(&nPen);

#ifdef ROUND_CALIB_TARGET
		if (!fullScreenPatch)
		{
			if (m_FillBlack)
				pDC->FillSolidRect(&tRect, RGB(0,0,0));

			pDC->Ellipse(&tRect);
		}
		else
#endif
        pDC->Rectangle(&tRect);

		pDC->SelectObject(oBrush)->DeleteObject();
		pDC->SelectObject(oPen)->DeleteObject();

		Sleep( lSettleTime );

#if 0
		lTics = GetTickCount();
		lTics1 = GetTickCount();
		while((lTics1 - lTics) < lSettleTime)lTics1 = GetTickCount();
#endif
#else
// MAC CODE GOES HERE
#endif // WIN32
}

void CCalTargetDisplay::DisplayBlackBackground(bool resetCWnd)
{
#ifdef WIN32
	if (resetCWnd)
		SetMyWindowFromHandle();

	CDC *pDC = myCWnd->GetDC();
	CBrush brushBlack(RGB(0, 0, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brushBlack);

	CRect rect;
	myCWnd->GetClientRect(rect);
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldBrush);

#else
// MAC CODE GOES HERE
#endif
}

void CCalTargetDisplay::BuildTargetValues(double dGamma)
{
	short i;
	double Lstar,ratio;

	for(i=0; i< 100; i++)
	{
		Lstar = (double)i;
		ratio = Lstar/903.3;
		if(ratio > .008856) // must recalc for other range
		{

			ratio = (Lstar +16)/116;
			ratio = CUBED(ratio);


		}	

		ratio = pow(ratio,1/dGamma);
		m_LstarValues[i].R = ratio;
		m_LstarValues[i].G = ratio;
		m_LstarValues[i].B = ratio;


	}
	return;
}

void CCalTargetDisplay::DisplayVisibilityTarget(bool resetCWnd)
{
#ifdef WIN32
    if (resetCWnd)
		SetMyWindowFromHandle();


	CDC *pDC;
	RECT wRect,tRect;
	
	CBrush nBrush,*oBrush;
	CPen  nPen, *oPen;
	short ccx,ccy,baseWidth,i,Width;   
	short DarkVals[4] = {27,22,16,0};

	pDC = myCWnd->GetDC();
	myCWnd->GetClientRect(&wRect);
	
	nPen.CreatePen(PS_SOLID, 1,RGB (192,192,192));
	nBrush.CreateSolidBrush(RGB (192,192,192));
	
	oBrush = pDC->SelectObject(&nBrush);
	oPen = pDC->SelectObject(&nPen);

	pDC->Rectangle(&wRect);
		
	pDC->SelectObject(oBrush)->DeleteObject();
	pDC->SelectObject(oPen)->DeleteObject();
	
	// find center of box 
		ccx = (short)((wRect.right - wRect.left)/2) ;
		ccy = (short)(wRect.bottom - wRect.top)/2 ;
		if(ccy < ccx) 
			Width = ccy;
		else
			Width = (short)(ccx ); //calculate relative width

		baseWidth =(short)((Width)*1); // calculate width of circles 
		
		for(i=0; i<4; i++)
		{
			nBrush.CreateSolidBrush(RGB (DarkVals[i],DarkVals[i],DarkVals[i]));
		 	oBrush = pDC->SelectObject(&nBrush);
			nPen.CreatePen(PS_SOLID, 1,RGB (DarkVals[i],DarkVals[i],DarkVals[i]));
			oPen = pDC->SelectObject(&nPen);
			Width = (4-i)*baseWidth/4;
			tRect.left = ccx-Width;
			tRect.top =  ccy+Width;
			tRect.right = ccx+Width;
			tRect.bottom = ccy-Width;
			/* draw a pie shaped figure
			pStart.x = (tRect.right - tRect.left)/2+tRect.left;
			pStart.y = tRect.top;
			pEnd.x = (tRect.right - tRect.left)/2+tRect.left;
			pEnd.y = tRect.bottom;
			pDC->Pie(&tRect,pStart,pEnd);
			*/
			pDC->Ellipse(&tRect);
			
			pDC->SelectObject(oBrush)->DeleteObject();
			pDC->SelectObject(oPen)->DeleteObject();
		}
#endif
}



#define ALL_CAL_TARGET_CODE	1

#ifdef ALL_CAL_TARGET_CODE
void CCalTargetDisplay::DisplayArbitraryBitMapStretch(LPCTSTR lpszResourceName)
{
     CDC *myCDC,dummyCDC;
	 CBitmap bmImage,*OldbmImage;
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 BITMAP myBitmap;
	 short err;
	
	 err = bmImage.LoadBitmap(lpszResourceName);
	 bmImage.GetBitmap(&myBitmap);
	 myCDC = myCWnd->GetDC();
	 myCWnd->GetClientRect(&myRect);
	 myRectSize = myRect.Size();
	 dummyCDC.CreateCompatibleDC(NULL);
	 OldbmImage = dummyCDC.SelectObject(&bmImage);
	 myCDC->Rectangle(&myRect);
	 myCDC->StretchBlt(
		 0,
		 0,
		 myRect.right - myRect.left,
		 myRect.bottom - myRect.top,
		 &dummyCDC,
		 0,
		 0,
		 myBitmap.bmWidth,
		 myBitmap.bmHeight,
		 SRCCOPY
		 );

	 dummyCDC.DeleteDC();
	 myCDC->DeleteDC();

}

void CCalTargetDisplay::DisplayArbitraryBitMapStretch(UINT intResource)
{

     CDC *myCDC,dummyCDC;
	 CBitmap bmImage,*OldbmImage;
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 BITMAP myBitmap;
	 short err;
	
	 err = bmImage.LoadBitmap(intResource);
	 bmImage.GetBitmap(&myBitmap);
	 myCDC = myCWnd->GetDC();
	 myCWnd->GetClientRect(&myRect);
	 myRectSize = myRect.Size();
	 dummyCDC.CreateCompatibleDC(NULL);
	 OldbmImage = dummyCDC.SelectObject(&bmImage);
	 myCDC->Rectangle(&myRect);
	 myCDC->StretchBlt(
		 0,
		 0,
		 myRect.right - myRect.left,
		 myRect.bottom - myRect.top,
		 &dummyCDC,
		 0,
		 0,
		 myBitmap.bmWidth,
		 myBitmap.bmHeight,
		 SRCCOPY
		 );

	 dummyCDC.DeleteDC();
	 myCDC->DeleteDC();

}
void CCalTargetDisplay::DisplayArbitraryBitMap(UINT intResource )
{
     CDC *myCDC,dummyCDC;
	 CBitmap bmImage,*OldbmImage;
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 BITMAP myBitmap;
	 short err;
	
	 err = bmImage.LoadBitmap( intResource );
	 bmImage.GetBitmap(&myBitmap);
	 myCDC = myCWnd->GetDC();
	 myCWnd->GetClientRect(&myRect);
	 myRectSize = myRect.Size();
	 dummyCDC.CreateCompatibleDC(NULL);
	 OldbmImage = dummyCDC.SelectObject(&bmImage);
	 myCDC->Rectangle(&myRect);
	 myCDC->BitBlt((myRectSize.cx - myBitmap.bmWidth)/2,
		 (myRectSize.cy - myBitmap.bmHeight)/2,
		 myBitmap.bmWidth,
		 myBitmap.bmHeight,
		 &dummyCDC,
		 0,
		 0,
		 SRCCOPY);

	 dummyCDC.DeleteDC();
	 myCDC->DeleteDC();

}

void CCalTargetDisplay::DisplayArbitraryBitMap(LPCTSTR lpszResourceName )
{
     CDC *myCDC,dummyCDC;
	 CBitmap bmImage,*OldbmImage;
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 BITMAP myBitmap;
	 short err;
	
	 err = bmImage.LoadBitmap( lpszResourceName );
	 bmImage.GetBitmap(&myBitmap);
	 myCDC = myCWnd->GetDC();
	 myCWnd->GetClientRect(&myRect);
	 myRectSize = myRect.Size();
	 dummyCDC.CreateCompatibleDC(NULL);
	 OldbmImage = dummyCDC.SelectObject(&bmImage);
	 myCDC->Rectangle(&myRect);
	 myCDC->BitBlt((myRectSize.cx - myBitmap.bmWidth)/2,
		 (myRectSize.cy - myBitmap.bmHeight)/2,
		 myBitmap.bmWidth,
		 myBitmap.bmHeight,
		 &dummyCDC,
		 0,
		 0,
		 SRCCOPY);

	 dummyCDC.DeleteDC();
	 myCDC->DeleteDC();

}

void CCalTargetDisplay::DisplayArbitraryBitMapFit(LPCTSTR lpszResourceName)
{
     CDC *myCDC,dummyCDC;
	 CBitmap bmImage,*OldbmImage;
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 BITMAP myBitmap;
	 short err;
	 double dOratio, dMagnification;
	 short sx,sy,sWidth,sHeight;
	
	 err = bmImage.LoadBitmap(lpszResourceName);
	 bmImage.GetBitmap(&myBitmap);
	 myCDC = myCWnd->GetDC();
	 myCWnd->GetClientRect(&myRect);
	 myRectSize = myRect.Size();
	 dummyCDC.CreateCompatibleDC(NULL);
	 OldbmImage = dummyCDC.SelectObject(&bmImage);
	 myCDC->Rectangle(&myRect);

	 dOratio = (double)myBitmap.bmWidth/(double)myBitmap.bmHeight;

	 if(dOratio < 1.0) // Portrait
	 {

		dMagnification = (double)(myRect.bottom - myRect.top)/(double)myBitmap.bmHeight;
		sy = 0;
		sx = (short)((myRect.right - myRect.left) - (short)(dMagnification * myBitmap.bmWidth))/2;
		

	 }

	 if (dOratio >= 1.0) // Landscape
	 {

		dMagnification = (double)(myRect.right - myRect.left)/(double)myBitmap.bmWidth;
		sx = 0;
		sy = (short)((myRect.bottom - myRect.top) - (short)(dMagnification * myBitmap.bmHeight))/2;


	 }

		sHeight = (short)(dMagnification * myBitmap.bmHeight);
		sWidth = (short)(dMagnification * myBitmap.bmWidth);

	 myCDC->StretchBlt(
		 sx,
		 sy,
		 sWidth,
		 sHeight,
		 &dummyCDC,
		 0,
		 0,
		 myBitmap.bmWidth,
		 myBitmap.bmHeight,
		 SRCCOPY
		 );

	 dummyCDC.DeleteDC();
	 myCDC->DeleteDC();

}





void CCalTargetDisplay::DisplaySplitVisabilityTarget()
{


	CDC *pDC;
	RECT wRect,tRect;
	POINT pStart,pEnd;
	CBrush nBrush,*oBrush;
	CPen  nPen, *oPen;
	short ccx,ccy,baseWidth,i,Width;   
	short DarkVals[4] = {12,20,25,29};
	short LightVals[4] = {255,249,243,237};

	pDC = myCWnd->GetDC();
	myCWnd->GetClientRect(&wRect);
	
	nPen.CreatePen(PS_SOLID, 1,RGB (192,192,192));
	nBrush.CreateSolidBrush(RGB (192,192,192));
	
	oBrush = pDC->SelectObject(&nBrush);
	oPen = pDC->SelectObject(&nPen);

	pDC->Rectangle(&wRect);
		
	pDC->SelectObject(oBrush)->DeleteObject();
	pDC->SelectObject(oPen)->DeleteObject();
	
	// find center of box 
		ccx = (short)((wRect.right - wRect.left)/2) ;
		ccy = (short)(wRect.bottom - wRect.top)/2 ;
		if(ccy < ccx) 
			Width = ccy;
		else
			Width = (short)(ccx ); //calculate relative width

		baseWidth =(short)((Width)*1); // calculate width of circles 
		
		for(i=0; i<4; i++)
		{
			nBrush.CreateSolidBrush(RGB (DarkVals[i],DarkVals[i],DarkVals[i]));
		 	oBrush = pDC->SelectObject(&nBrush);
			nPen.CreatePen(PS_SOLID, 1,RGB (DarkVals[i],DarkVals[i],DarkVals[i]));
			oPen = pDC->SelectObject(&nPen);
			Width = (4-i)*baseWidth/4;
			tRect.left = ccx-Width;
			tRect.top =  ccy-Width;
			tRect.right = ccx+Width;
			tRect.bottom = ccy+Width;
		// draw a pie shaped figure
			pStart.x =  tRect.left;
			pStart.y = tRect.bottom ;
			pEnd.x = tRect.right;
			pEnd.y =  tRect.top;;
			pDC->Pie(&tRect,pStart,pEnd);
			
		//	pDC->Ellipse(&tRect);
			
			pDC->SelectObject(oBrush)->DeleteObject();
			pDC->SelectObject(oPen)->DeleteObject();
		}
		for(i=0; i<4; i++)
		{
			nBrush.CreateSolidBrush(RGB (LightVals[i],LightVals[i],LightVals[i]));
		 	oBrush = pDC->SelectObject(&nBrush);
			nPen.CreatePen(PS_SOLID, 1,RGB (LightVals[i],LightVals[i],LightVals[i]));
			oPen = pDC->SelectObject(&nPen);
			Width = (4-i)*baseWidth/4;
			tRect.left = ccx-Width;
			tRect.top =  ccy-Width;
			tRect.right = ccx+Width;
			tRect.bottom = ccy+Width;
		// draw a pie shaped figure
			pStart.x = tRect.right;
			pStart.y =  tRect.top;
			pEnd.x = tRect.left;
			pEnd.y = tRect.bottom ;
			pDC->Pie(&tRect,pStart,pEnd);
			
		//	pDC->Ellipse(&tRect);
			
			pDC->SelectObject(oBrush)->DeleteObject();
			pDC->SelectObject(oPen)->DeleteObject();
		}
}
void CCalTargetDisplay::DisplayVisabilityRampTarget()
{


	CDC *pDC;
	RECT wRect,tRect;
	CBrush nBrush,*oBrush;
	CPen  nPen, *oPen;
	short ccx,ccy,baseWidth,i,Width,Length,baseLength;   
	short DarkVals[4] = {12,24,36,48};

	pDC = myCWnd->GetDC();
	myCWnd->GetClientRect(&wRect);
	
		pDC->Rectangle(&wRect);
	
	// find center of box 
		ccx = (short)((wRect.right - wRect.left)/2) ;
		ccy = (short)(wRect.bottom - wRect.top)/2 ;

        Width = (short)(ccx * 1.0); //calculate relative width
		Length = (short)(ccy * 1.0);
		ccx += (short)wRect.left ; // shift the center to the proper place;
		tRect.left = ccx-Width;
		tRect.top =  ccy+Length;
		tRect.right = ccx+Width;
		tRect.bottom = ccy-Length;

		nBrush.CreateSolidBrush(RGB (0,0,0));
		oBrush = pDC->SelectObject(&nBrush);
		nPen.CreatePen(PS_SOLID, 1,RGB (0,0,0));
		oPen = pDC->SelectObject(&nPen);
		pDC->Rectangle(&tRect);
		pDC->SelectObject(oBrush)->DeleteObject();
		pDC->SelectObject(oPen)->DeleteObject();
		

	

		baseWidth =(short)((ccx -wRect.left)*1); // calculate width of circles 
		baseLength = (short)((ccy -wRect.top)*1);
		for(i=0; i<4; i++)
		{
			nBrush.CreateSolidBrush(RGB (DarkVals[i],DarkVals[i],DarkVals[i]));
		 	oBrush = pDC->SelectObject(&nBrush);
			nPen.CreatePen(PS_SOLID, 1,RGB (DarkVals[i],DarkVals[i],DarkVals[i]));
			oPen = pDC->SelectObject(&nPen);
			Width = (4-i)*baseWidth/4;
			Length = (4-i)*baseLength/4;
			tRect.left = ccx-Width;
			tRect.top =  ccy+Length;
			tRect.right = ccx+Width;
			tRect.bottom = ccy-Length;

			pDC->Ellipse(&tRect);
			pDC->SelectObject(oBrush)->DeleteObject();
			pDC->SelectObject(oPen)->DeleteObject();
		}

}
void CCalTargetDisplay::DisplayWhiteVisabilityTarget()
{


	CDC *pDC;
	RECT wRect,tRect;
	CBrush nBrush,*oBrush;
	CPen  nPen, *oPen;
	short ccx,ccy,baseWidth,i,Width;   
	short DarkVals[4] = {246,249,252,255};

	pDC = myCWnd->GetDC();
	myCWnd->GetClientRect(&wRect);
	
	
	// find center of box 
		ccx = (short)((wRect.right - wRect.left)/2) ;
		ccy = (short)(wRect.bottom - wRect.top)/2 ;
		if(ccy < ccx) 
			Width = ccy;
		else
			Width = (short)(ccx ); //calculate relative width

		

		nBrush.CreateSolidBrush(RGB (192,192,192));
		oBrush = pDC->SelectObject(&nBrush);
		nPen.CreatePen(PS_SOLID, 1,RGB (192,192,192));
		oPen = pDC->SelectObject(&nPen);
		pDC->Rectangle(&wRect);
		pDC->SelectObject(oBrush)->DeleteObject();
		pDC->SelectObject(oPen)->DeleteObject();
		

	

		baseWidth =(short)(Width); // calculate width of circles 
		
		for(i=0; i<4; i++)
		{
			nBrush.CreateSolidBrush(RGB (DarkVals[i],DarkVals[i],DarkVals[i]));
		 	oBrush = pDC->SelectObject(&nBrush);
			nPen.CreatePen(PS_SOLID, 1,RGB (DarkVals[i],DarkVals[i],DarkVals[i]));
			oPen = pDC->SelectObject(&nPen);
			Width = (4-i)*baseWidth/4;
			tRect.left = ccx-Width;
			tRect.top =  ccy+Width;
			tRect.right = ccx+Width;
			tRect.bottom = ccy-Width;

			pDC->Ellipse(&tRect);
			pDC->SelectObject(oBrush)->DeleteObject();
			pDC->SelectObject(oPen)->DeleteObject();
		}

}

void CCalTargetDisplay::DisplayPuckImage()
{
    CDC *myCDC,dummyCDC;
	 CBitmap bmImage,*OldbmImage;
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 CRgn   myRgn;
	 BITMAP myBitmap;
	 short err;
	
	 err = bmImage.LoadBitmap( _T( "PUCKIMAGE" ) );
	 bmImage.GetBitmap(&myBitmap);
	 myCDC = myCWnd->GetDC();
	 myCWnd->GetClientRect(&myRect);
	 myRgn.CreateRectRgn(myRect.left,myRect.top,myRect.right,myRect.bottom);
	 myRectSize = myRect.Size();
	 dummyCDC.CreateCompatibleDC(NULL);
	 OldbmImage = dummyCDC.SelectObject(&bmImage);
	 myCDC->SelectClipRgn(&myRgn);
	 myCDC->Rectangle(&myRect);
	 myCDC->BitBlt((myRectSize.cx - myBitmap.bmWidth)/2,
		 (myRectSize.cy - myBitmap.bmHeight)/2,
		 myBitmap.bmWidth,
		 myBitmap.bmHeight,
		 &dummyCDC,
		 0,
	-20,
		 SRCCOPY);
	 DeleteObject(&myRgn);
	 DeleteObject(&myBitmap);
	 dummyCDC.DeleteDC();
	 myCDC->DeleteDC();

}
void CCalTargetDisplay::ColorTempLocusImage()
{

	
		
	 DisplayArbitraryBitMapStretch(_T( "CT_LOCUS" ) );


}

void CCalTargetDisplay::DisplayTargetHelpImage()
{
CDC *myCDC,dummyCDC;
	 CBitmap bmImage,*OldbmImage;
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 CRgn   myRgn;
	 BITMAP myBitmap;
	 short err;
	
	 err = bmImage.LoadBitmap( _T( "TARGET_HELP" ) );
	 bmImage.GetBitmap(&myBitmap);
	 myCDC = myCWnd->GetDC();
	 myCWnd->GetClientRect(&myRect);
	 myRgn.CreateRectRgn(myRect.left,myRect.top,myRect.right,myRect.bottom);
	 myRectSize = myRect.Size();
	 dummyCDC.CreateCompatibleDC(NULL);
	 OldbmImage = dummyCDC.SelectObject(&bmImage);
	 myCDC->SelectClipRgn(&myRgn);
	 myCDC->Rectangle(&myRect);
	 myCDC->BitBlt((myRectSize.cx - myBitmap.bmWidth)/2,
		 (myRectSize.cy - myBitmap.bmHeight)/2,
		 myBitmap.bmWidth,
		 myBitmap.bmHeight,
		 &dummyCDC,
		-130,
		-80,
		 SRCCOPY);
	 DeleteObject(&myRgn);
	 DeleteObject(&myBitmap);
	 dummyCDC.DeleteDC();
	 myCDC->DeleteDC();

}

#endif


#ifdef WIN32

void CCalTargetDisplay::xySpecDisplay()
{	
	CDC *pDC;
	RECT wRect,tRect;
	CBrush nBrush,*oBrush,RedBrush,GreenBrush,BlueBrush,WhiteBrush;
	CPen  nPen, *oPen, WhitePen;
	short ccx,ccy,baseWidth,i,Width,Length,baseLength;   
	short TargetVals[3] = {64,128,215};
	double dxyScale;

	pDC = myCWnd->GetDC();
	myCWnd->GetClientRect(&wRect);
	dxyScale =  (wRect.bottom - wRect.top)/(10*SpecData.dxySpec);

	RedBrush.CreateSolidBrush(RGB(255,0,0));
	GreenBrush.CreateSolidBrush(RGB(0,255,0));
	BlueBrush.CreateSolidBrush(RGB(0,0,255));
	WhiteBrush.CreateSolidBrush(RGB(255,255,255));

	WhitePen.CreatePen(PS_COSMETIC,1,(RGB(255,255,255)));


//Display Bullseye target	
	// find center of box 
		ccx = (short)((wRect.right - wRect.left)/2) ;
		ccy = (short)(wRect.bottom - wRect.top)/2 ;

        Width = (short)(ccx ); //calculate relative width
		Length = (short)(ccy );
		ccx += (short)wRect.left ; // shift the center to the proper place;
		tRect.left = ccx-Width;
		tRect.top =  ccy+Length;
		tRect.right = ccx+Width;
		tRect.bottom = ccy-Length;

		nBrush.CreateSolidBrush(RGB (192,192,192));
		oBrush = pDC->SelectObject(&nBrush);
		nPen.CreatePen(PS_SOLID, 1,RGB (0,0,0));
		oPen = pDC->SelectObject(&nPen);
		pDC->Rectangle(&tRect);
		pDC->SelectObject(oBrush)->DeleteObject();
		pDC->SelectObject(oPen)->DeleteObject();
		

	

		baseWidth =(short)((ccx -wRect.left)*1); // calculate width of circles 
		baseLength = (short)((ccy -wRect.top)*1);
		for(i=0; i<3; i++)
		{
			nBrush.CreateSolidBrush(RGB (TargetVals[i],TargetVals[i],TargetVals[i]));
		 	oBrush = pDC->SelectObject(&nBrush);
			nPen.CreatePen(PS_SOLID, 1,RGB (TargetVals[i],TargetVals[i],TargetVals[i]));
			oPen = pDC->SelectObject(&nPen);
			Width = (3-i)*baseWidth/5;
			Length = (3-i)*baseLength/5;
			tRect.left = ccx-Length;
			tRect.top =  ccy+Length;
			tRect.right = ccx+Length;
			tRect.bottom = ccy-Length;

			pDC->Ellipse(&tRect);
			pDC->SelectObject(oBrush)->DeleteObject();
			pDC->SelectObject(oPen)->DeleteObject();
		}

    baseWidth =(short)((wRect.right-wRect.left)); // calculate width of circles 
	baseLength = (short)(( wRect.bottom -wRect.top));
	pDC->MoveTo(baseWidth/2,0);
	pDC->LineTo(baseWidth/2,baseLength);
	pDC->MoveTo(0,baseLength/2);
	pDC->LineTo(baseWidth,baseLength/2);

	// Now plot a measured point;
	
	pDC->MoveTo(baseWidth/2,baseLength/2);
	double dccx,dccy,doffset ;
	short  coffset;
	bool   bIncrease;
	CBrush *cbColor;
	cbColor = NULL;

	dccx = SpecData.ReferenceAbsolute->x-SpecData.MeasuredAbsolute->x ;
	dccy = SpecData.ReferenceAbsolute->y-SpecData.MeasuredAbsolute->y;
	doffset = sqrt(dccx*dccx +dccy*dccy);

	if((dccx >= 0) && (dccy >= 0))
	{
		bIncrease = false;
		cbColor = &BlueBrush;
	}

	if((dccx < 0) && (dccy < 0))
	{
		bIncrease = true;
		cbColor = &BlueBrush;
	}
	
	if((dccx <= 0) && (dccy >= 0))
	{
		bIncrease = false;
		cbColor = &RedBrush;
	}

	if((dccx >= 0) && (dccy <= 0))
	{
		bIncrease = true;
		cbColor = &RedBrush;
	}

	if (doffset <= SpecData.dxySpec)
		cbColor = &WhiteBrush;

	ccx = (short)(dxyScale * dccx);
	ccy = (short)(dxyScale * dccy);
	ccx = baseWidth/2+ccx;
	ccy = baseLength/2-ccy;
	coffset = (short)(dxyScale * SpecData.dxySpec/2);
	bool bPlotError = false;
	if((ccx <= wRect.left+coffset)||(ccx >= wRect.right-coffset))
		bPlotError = true;
	if((ccy <= wRect.top+coffset)||(ccy >= wRect.bottom-coffset))
		bPlotError = true;

	pDC->MoveTo(ccx,ccy);

	if(bPlotError == false)
	{
		oBrush = pDC->SelectObject(cbColor);
		oPen   = pDC->SelectObject(&WhitePen);
		pDC->Ellipse(ccx - coffset,
			ccy + coffset,
			ccx + coffset,
			ccy - coffset);
		pDC->MoveTo(ccx-coffset,ccy);  // move to center

		pDC->LineTo(ccx+coffset,ccy);

		pDC->MoveTo(ccx, ccy - coffset);

		if (bIncrease)
			pDC->LineTo(ccx,ccy+coffset);
		pDC->SelectObject(oBrush);
		pDC->SelectObject(oPen);
	}

	else
	{
		ccx = (short)((wRect.right - wRect.left)/2) ;
		ccy = (short)(wRect.bottom - wRect.top)/2 ;

		oBrush = pDC->SelectObject(cbColor);
			oPen   = pDC->SelectObject(&WhitePen);
		Width = baseWidth/5;
		Length = baseLength/5;
		tRect.left = ccx-Length;
		tRect.top =  ccy+Length;
		tRect.right = ccx+Length;
		tRect.bottom = ccy-Length;

		pDC->Ellipse(&tRect);

		pDC->MoveTo(ccx-Length,ccy);  // move to center

		pDC->LineTo(ccx+Length,ccy);

		pDC->MoveTo(ccx, ccy - Length);

		if (bIncrease)
			pDC->LineTo(ccx,ccy+Length);

		pDC->SelectObject(oBrush);
		pDC->SelectObject(oPen);

	}



	


}

#endif

#ifdef WIN32

void CCalTargetDisplay::DisplayLuts(unsigned char * pRlut, unsigned char *pGlut, unsigned char *pBlut)
{

	CDC *pDC;
	RECT wRect;
	CBrush nBrush,*oBrush,RedBrush,GreenBrush,BlueBrush,WhiteBrush,GrayBrush;
	CPen  nPen, WhitePen;
	CRect cR;
	
	double dxScale, dyScale,dx,dy;
	short i,ix,iy,iHeight,iWidth;
	
	RedBrush.CreateSolidBrush(RGB(255,0,0));
	GreenBrush.CreateSolidBrush(RGB(0,255,0));
	BlueBrush.CreateSolidBrush(RGB(0,0,255));
	WhiteBrush.CreateSolidBrush(RGB(255,255,255));
	GrayBrush.CreateSolidBrush(RGB(128,128,128));
	WhitePen.CreatePen(PS_COSMETIC,1,(RGB(255,255,255)));

	//blue lut ...

	pDC = bCwnd->GetDC();
	bCwnd->GetClientRect(&wRect);
	cR = wRect;
	iHeight = (short)(wRect.bottom -wRect.top);
	iWidth  = (short)(wRect.right-wRect.left);
	oBrush = pDC->SelectObject(&GrayBrush);
	pDC->Rectangle(&cR);
	pDC->SelectObject(&BlueBrush);
	pDC->MoveTo(0,iHeight);
	pDC->BeginPath();
	dxScale = iWidth;
	dyScale = iHeight;

	{

		for(i=0; i< 256; i++)
		{

			dx = (double)i/255;
			dy = pBlut[i]/255.;
			ix = (int)(dx*dxScale);
			iy = iHeight - (int)(dyScale*dy);
			pDC->LineTo(ix,iy);

		}
		pDC->LineTo(ix,iHeight);
		pDC->LineTo(0,iHeight);
	}

	pDC->EndPath();
	pDC->StrokeAndFillPath();
	DeleteObject(pDC->SelectObject(oBrush));

	bCwnd->ReleaseDC(pDC);


		//green lut ...

	pDC = gCwnd->GetDC();
	gCwnd->GetClientRect(&wRect);
	cR = wRect;
	iHeight = (short)(wRect.bottom -wRect.top);
	iWidth  = (short)(wRect.right-wRect.left);
	oBrush = pDC->SelectObject(&GrayBrush);
	pDC->Rectangle(&cR);
	pDC->SelectObject(&GreenBrush);
	pDC->MoveTo(0,iHeight);
	pDC->BeginPath();
	dxScale = iWidth;
	dyScale = iHeight;

	{

		for(i=0; i< 256; i++)
		{

			dx = (double)i/255;
			dy = pGlut[i]/255.;
			ix = (int)(dx*dxScale);
			iy = iHeight - (int)(dyScale*dy);
			pDC->LineTo(ix,iy);

		}
		pDC->LineTo(ix,iHeight);
		pDC->LineTo(0,iHeight);
	}

	pDC->EndPath();
	pDC->StrokeAndFillPath();
	DeleteObject(pDC->SelectObject(oBrush));

	gCwnd->ReleaseDC(pDC);


			//red lut ...

	pDC = rCwnd->GetDC();
	rCwnd->GetClientRect(&wRect);
	cR = wRect;
	iHeight = (short)(wRect.bottom -wRect.top);
	iWidth  = (short)(wRect.right-wRect.left);
	oBrush = pDC->SelectObject(&GrayBrush);
	pDC->Rectangle(&cR);
	pDC->SelectObject(&RedBrush);
	pDC->MoveTo(0,iHeight);
	pDC->BeginPath();
	dxScale = iWidth;
	dyScale = iHeight;

	{

		for(i=0; i< 256; i++)
		{

			dx = (double)i/255;
			dy = pRlut[i]/255.;
			ix = (int)(dx*dxScale);
			iy = iHeight - (int)(dyScale*dy);
			pDC->LineTo(ix,iy);

		}
		pDC->LineTo(ix,iHeight);
		pDC->LineTo(0,iHeight);
	}

	pDC->EndPath();
	pDC->StrokeAndFillPath();
	DeleteObject(pDC->SelectObject(oBrush));

	rCwnd->ReleaseDC(pDC);
}

void CCalTargetDisplay::PlotColorTempData(double x, double y)
{
	 CDC *myCDC,dummyCDC;
	 CBitmap bmImage,*OldbmImage;
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 CRgn   myRgn;
	 BITMAP myBitmap;
	 short err;
	 int iHeight, iWidth;
	 double dxScale, dyScale;  
	 int ixRed,iyRed,ixGreen,iyGreen,ixBlue,iyBlue, ixWhite, iyWhite, iyOffset;

	 
	 err = bmImage.LoadBitmap( _T( "CT_LOCUS" ) );
	 bmImage.GetBitmap(&myBitmap);
	 myCDC = myCWnd->GetDC();
	 myCWnd->GetClientRect(&myRect);

	 iWidth = myRect.right - myRect.left;
	 iHeight = myRect.bottom - myRect.top;
	
	 myRgn.CreateRectRgn(myRect.left,myRect.top,myRect.right,myRect.bottom);
	 myRectSize = myRect.Size();
	 dummyCDC.CreateCompatibleDC(NULL);
	 OldbmImage = dummyCDC.SelectObject(&bmImage);
	 myCDC->SelectClipRgn(&myRgn);
	 myCDC->Rectangle(&myRect);
	 myCDC->StretchBlt(
		 0,
		 0,
		 iWidth,
		 iHeight,
		 &dummyCDC,
		 0,
		 0,
		 myBitmap.bmWidth,
		 myBitmap.bmHeight,
		 SRCCOPY);
	 DeleteObject(&myRgn);
	 DeleteObject(&myBitmap);
	 dummyCDC.DeleteDC();
	 
	 // calculate the scale factors  

	 
     dxScale = (double)iWidth /.76;  // .76 = the width of the graph
	 dyScale = (double)iHeight/ .9;  //  .9 = the lenght of the graph 

	 iyOffset = 0,
	 
	 ixRed = (int)(CTdata.dxRed * dxScale);
	 iyRed = iHeight - (int)(CTdata.dyRed * dyScale)+iyOffset;

	 ixGreen = (int)(CTdata.dxGreen * dxScale);
	 iyGreen = iHeight - (int)(CTdata.dyGreen * dyScale)+iyOffset;

	 ixBlue = (int)(CTdata.dxBlue * dxScale);
	 iyBlue = iHeight - (int)(CTdata.dyBlue * dyScale)+iyOffset;

	 ixWhite = (int)(x * dxScale);
	 iyWhite = iHeight - (int)(y * dyScale)+iyOffset;

	CBrush nBrush,RedBrush,GreenBrush,BlueBrush,WhiteBrush,GrayBrush;
	CPen  nPen, WhitePen;

	RedBrush.CreateSolidBrush(RGB(255,0,0));
	GreenBrush.CreateSolidBrush(RGB(0,255,0));
	BlueBrush.CreateSolidBrush(RGB(0,0,255));
	WhiteBrush.CreateSolidBrush(RGB(255,255,255));
	GrayBrush.CreateSolidBrush(RGB(128,128,128));
	WhitePen.CreatePen(PS_COSMETIC,1,(RGB(255,255,255)));

	myCDC->SelectObject(GrayBrush);
	myCDC->SelectObject(WhitePen);

	// draw gamut 

	myCDC->MoveTo(ixBlue,iyBlue);
	myCDC->LineTo(ixGreen,iyGreen);
	myCDC->LineTo(ixRed,iyRed);
	myCDC->LineTo(ixBlue,iyBlue);

	// Draw white ball....

	myCDC->MoveTo(ixWhite,iyWhite);
	myCDC->Ellipse(ixWhite - (int)(.01*dxScale), iyWhite - (int)(.01*dyScale),ixWhite + (int)(.01*dxScale), iyWhite + (int)(.01*dyScale));


	myCDC->DeleteDC();

	


}

void CCalTargetDisplay::PlotColorCIEData(double x, double y, CWnd *CIEC_Wnd)
{
	 CDC *myCDC,dummyCDC;
	 
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 CRgn   myRgn;
	
	 
	 int iHeight, iWidth;
	 double dxScale, dyScale;  
	 int ixRed,iyRed,ixGreen,iyGreen,ixBlue,iyBlue, ixWhite, iyWhite, iyOffset;

// this routines assumes that you have cie bitmap displayed in a window. 	 
	 
	 myCDC = CIEC_Wnd->GetDC();
	 CIEC_Wnd->GetClientRect(&myRect);

	 iWidth = myRect.right - myRect.left;
	 iHeight = myRect.bottom - myRect.top;
	

	 
	 // calculate the scale factors  

	 
     dxScale = (double)iWidth /.76;  // .76 = the width of the graph
	 dyScale = (double)iHeight/ .9;  //  .9 = the lenght of the graph 

	 iyOffset = 0,
	 
	 ixRed = (int)(CTdata.dxRed * dxScale);
	 iyRed = iHeight - (int)(CTdata.dyRed * dyScale)+iyOffset;

	 ixGreen = (int)(CTdata.dxGreen * dxScale);
	 iyGreen = iHeight - (int)(CTdata.dyGreen * dyScale)+iyOffset;

	 ixBlue = (int)(CTdata.dxBlue * dxScale);
	 iyBlue = iHeight - (int)(CTdata.dyBlue * dyScale)+iyOffset;

	 ixWhite = (int)(x * dxScale);
	 iyWhite = iHeight - (int)(y * dyScale)+iyOffset;

	CBrush nBrush,RedBrush,GreenBrush,BlueBrush,WhiteBrush,GrayBrush;
	CPen  nPen, WhitePen;

	RedBrush.CreateSolidBrush(RGB(255,0,0));
	GreenBrush.CreateSolidBrush(RGB(0,255,0));
	BlueBrush.CreateSolidBrush(RGB(0,0,255));
	WhiteBrush.CreateSolidBrush(RGB(255,255,255));
	GrayBrush.CreateSolidBrush(RGB(128,128,128));
	WhitePen.CreatePen(PS_COSMETIC,1,(RGB(255,255,255)));

	myCDC->SelectObject(WhiteBrush);
	myCDC->SelectObject(WhitePen);

	// draw gamut 

	myCDC->MoveTo(ixBlue,iyBlue);
	myCDC->LineTo(ixGreen,iyGreen);
	myCDC->LineTo(ixRed,iyRed);
	myCDC->LineTo(ixBlue,iyBlue);

	// Draw white ball....

	myCDC->MoveTo(ixWhite,iyWhite);
	myCDC->Ellipse(ixWhite - (int)(.001*dxScale), iyWhite - (int)(.001*dyScale),ixWhite + (int)(.001*dxScale), iyWhite + (int)(.001*dyScale));


	myCDC->DeleteDC();

	


}

void CCalTargetDisplay::PlotColorCIEData(double x, double y, CWnd *CIEC_Wnd, short R, short G, short B)
{
	 CDC *myCDC,dummyCDC;
	 
	 CSize	bmSize,myRectSize;
	 CRect  myRect;
	 CRgn   myRgn;
	
	 
	 int iHeight, iWidth;
	 double dxScale, dyScale;  
	 int ixRed,iyRed,ixGreen,iyGreen,ixBlue,iyBlue, ixWhite, iyWhite, iyOffset;

// this routines assumes that you have cie bitmap displayed in a window. 	 
	 
	 myCDC = CIEC_Wnd->GetDC();
	 CIEC_Wnd->GetClientRect(&myRect);

	 iWidth = myRect.right - myRect.left;
	 iHeight = myRect.bottom - myRect.top;
	

	 
	 // calculate the scale factors  

	 
     dxScale = (double)iWidth /.76;  // .76 = the width of the graph
	 dyScale = (double)iHeight/ .9;  //  .9 = the lenght of the graph 

	 iyOffset = 0,
	 
	 ixRed = (int)(CTdata.dxRed * dxScale);
	 iyRed = iHeight - (int)(CTdata.dyRed * dyScale)+iyOffset;

	 ixGreen = (int)(CTdata.dxGreen * dxScale);
	 iyGreen = iHeight - (int)(CTdata.dyGreen * dyScale)+iyOffset;

	 ixBlue = (int)(CTdata.dxBlue * dxScale);
	 iyBlue = iHeight - (int)(CTdata.dyBlue * dyScale)+iyOffset;

	 ixWhite = (int)(x * dxScale);
	 iyWhite = iHeight - (int)(y * dyScale)+iyOffset;

	CBrush nBrush,RedBrush,GreenBrush,BlueBrush,WhiteBrush,GrayBrush;
	CPen  nPen, WhitePen;

	RedBrush.CreateSolidBrush(RGB(255,0,0));
	GreenBrush.CreateSolidBrush(RGB(0,255,0));
	BlueBrush.CreateSolidBrush(RGB(0,0,255));
	WhiteBrush.CreateSolidBrush(RGB(255,255,255));
	GrayBrush.CreateSolidBrush(RGB(128,128,128));
	WhitePen.CreatePen(PS_COSMETIC,1,(RGB(R,G,B)));

	myCDC->SelectObject(GrayBrush);
	myCDC->SelectObject(WhitePen);

	// draw gamut 

	myCDC->MoveTo(ixBlue,iyBlue);
	myCDC->LineTo(ixGreen,iyGreen);
	myCDC->LineTo(ixRed,iyRed);
	myCDC->LineTo(ixBlue,iyBlue);

	// Draw white ball....

	myCDC->MoveTo(ixWhite,iyWhite);
	myCDC->Ellipse(ixWhite - (int)(.01*dxScale), iyWhite - (int)(.01*dyScale),ixWhite + (int)(.01*dxScale), iyWhite + (int)(.01*dyScale));


	myCDC->DeleteDC();

	


}

void CCalTargetDisplay::DisplayBackGroundTestTarget1()
{
    CDC *pDC;
	RECT wRect,tRect;
	CBrush nBrush,*oBrush;
	CPen  nPen, *oPen;
	short ccx,ccy,Width,Height;   
	short gray1;

	pDC = myCWnd->GetDC();
	myCWnd->GetClientRect(&wRect);


		
	// find center of box 
		ccx = (short)((wRect.right - wRect.left)/2) ;
		ccy = (short)(wRect.bottom - wRect.top)/2 ;

        

		//draw a rectangle at 50 L* 
		gray1 = (short)(m_LstarValues[50].G*255);
		nBrush.CreateSolidBrush(RGB (gray1,gray1,gray1));
		oBrush = pDC->SelectObject(&nBrush);
		nPen.CreatePen(PS_SOLID, 1,RGB (gray1,gray1,gray1));
		oPen = pDC->SelectObject(&nPen);	
	
		pDC->Rectangle(&wRect);
		
		pDC->SelectObject(oPen)->DeleteObject();
		pDC->SelectObject(oBrush)->DeleteObject();

		Width = (short)(ccx * .2); //calculate relative width
		Height = (short)(ccy *.2);
	
		// square target; upper left
		tRect.left = wRect.left+Width/10;
		tRect.top =  wRect.top +Width/10;
		tRect.right = tRect.left +Width;
		tRect.bottom = tRect.top + Width ;

		DrawVisibilityPatch(pDC, &tRect,1,3);

		// square target; lower right
		tRect.left = wRect.right - Width -Width/10;
		tRect.top =  wRect.bottom - Width-Width/10;
		tRect.right = tRect.left +Width;
		tRect.bottom = tRect.top + Width ;

		DrawVisibilityPatch(pDC, &tRect,1,3);

		// square target; upper right
		tRect.left = wRect.right - Width -Width/10;
		tRect.top =  wRect.top +Width/10;
		tRect.right = tRect.left +Width;
		tRect.bottom = tRect.top + Width ;

		DrawVisibilityPatch(pDC, &tRect,1,3);

			// square target; lower left
		tRect.left = wRect.left+Width/10;
		tRect.top =  wRect.bottom - Width-Width/10;
		tRect.right = tRect.left +Width;
		tRect.bottom = tRect.top + Width ;

		DrawVisibilityPatch(pDC, &tRect,1,3);

		// draw a 10 step visibility scale along the bottom line of the two corner scales

		short i, deltaX,startX,startY,nSteps;
		startY = (short)(wRect.top + 1.5*Width); // based upon the original larger size box 
		nSteps = 10;
		Width = (short)(ccx * .10); //redefine width and height
		Height = (short)(ccy * .10);
		deltaX = Width; 

		startX = ccx - nSteps*deltaX/2;

		for(i=0; i<10; i++)
		{

			tRect.left = startX + i* deltaX;
			tRect.right = tRect.left +Width;
			tRect.top = startY - Width;
			tRect.bottom = startY;

			DrawVisibilityPatch(pDC, &tRect,i*5,i*5+1);
		}

		// draw a 10 step visibility scale along the bottom line of the two corner scales
	
		startY =(short) (wRect.bottom -wRect.top - startY); // based upon the original larger size box 
		nSteps = 10;
		Width = (short)(ccx * .10); //redefine width and height
		Height = (short)(ccy * .10);
		deltaX = Width; 

		startX = ccx - nSteps*deltaX/2;

		for(i=0; i<10; i++)
		{

			tRect.left = startX + i* deltaX;
			tRect.top =  startY;
			tRect.right = tRect.left +Width;
			tRect.bottom = startY + Width ;

			DrawVisibilityPatch(pDC, &tRect,i*5 + 48,i*5+1+48);
		}
};  // visibility scales 

void CCalTargetDisplay::DrawVisibilityPatch(CDC * pDC, RECT *outsideRect,short innerValue, short outerValue)
{
    
// inner and outer values are integer values of L* 0->100
	RECT wRect,tRect;
	CBrush inBrush,outBrush,*oBrush;
	CPen  inPen,outPen, *oPen;
	short ccx,ccy,Width,Height;   
	short gray1,gray2;

	pDC = myCWnd->GetDC();
		
	wRect = *outsideRect;
	
	// find center of box 
		ccx = (short)(((wRect.right - wRect.left)/2)+ wRect.left) ;
		ccy = (short)((wRect.bottom - wRect.top)/2 + wRect.top);

        Width = (short)(((wRect.right - wRect.left)/2) / 3.); //calculate relative half width of inside box
		Height = (short)(((wRect.bottom - wRect.top)/2) / 3.);
	

		tRect.left = ccx-Width;
		tRect.top =  ccy+Width;
		tRect.right = ccx+Width;
		tRect.bottom = ccy-Width;

		gray1 = (short)(m_LstarValues[outerValue].G*255);
		gray2 = (short)(m_LstarValues[innerValue].G*255);

		inBrush.CreateSolidBrush(RGB (gray1,gray1,gray1));
		inPen.CreatePen(PS_SOLID, 1,RGB (gray1,gray1,gray1));
		
		oBrush = pDC->SelectObject(&inBrush);
		oPen = pDC->SelectObject(&inPen);	

		pDC->Rectangle(&wRect); //draw the outer rectangle

		
		outBrush.CreateSolidBrush(RGB (gray2,gray2,gray2));
		outPen.CreatePen(PS_SOLID, 1,RGB (gray2,gray2,gray1));
		
		pDC->SelectObject(&outBrush)->DeleteObject(); //delete the inPen and Brush
		pDC->SelectObject(&outPen)->DeleteObject();	
		
		pDC->Rectangle(&tRect); // draw the inner rectangle;

		pDC->SelectObject(oBrush)->DeleteObject(); //delete the outerPen and Brush 
		pDC->SelectObject(oPen)->DeleteObject();


}
#endif

