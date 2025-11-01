//cieColor.h

#if !defined(__CIECOLOR__) 
	#define __CIECOLOR__
#include "math.h"
#include <stdio.h>
#ifndef WIN32
#ifdef LINUX
#include "linuxTypes.h"
#else
#include "stdafx.h"
//#include "FakeMacTypes.h"
#endif
#endif

#include "icc.h"

#include "ColorStructs.h"

#define d50X	.9642028808593750
#define d50Y	1.000000000000000
#define d50Z    .8248901367187500
#define MAX_SPECTRA  100

// Digital Video and HDTV Algorithms and Interfaces
// Chapter 22, p 239, Table 22.5
#define DEFAULT_sRGBRedx 0.640
#define DEFAULT_sRGBRedy 0.330
#define DEFAULT_sRGBRedz 0.330

#define DEFAULT_sRGBGreenx 0.300
#define DEFAULT_sRGBGreeny 0.600
#define DEFAULT_sRGBGreenz 0.100

#define DEFAULT_sRGBBluex 0.150
#define DEFAULT_sRGBBluey 0.060
#define DEFAULT_sRGBBluez 0.790

#define DEFAULT_sRGBD65Whitex 0.3127
#define DEFAULT_sRGBD65Whitey 0.3290
#define DEFAULT_sRGBD65Whitez 0.3582



/* sRGB extension information handled here....

 


*/


typedef struct SPECTRUM 
{
	short  nPts;
	double inc; // increment in nanometers
	double spectrum[400]; // value in nanometers 
	double integral;  // the sum of the spectrum;

}SPECTRUM; 
#ifndef _CTData_
#define _CTData_
typedef struct CTData {
	short  sindex;
	double dRMK;
	double dTemp;
	double du;
	double dv;
	double dslope;
}CTPoint;
#endif



#if 0
#ifndef _str256_
#define _str256_
typedef struct _str256 
{

	char c[256];
	short end;
}str256;
#endif
#endif

typedef struct _MonitorDefaultInfo
{

	short   sID;   // a "slot number" for multiple monitor systems.  

	dYxy RedYxy;
	dYxy GreenYxy;
	dYxy BlueYxy;
	dYxy WhiteYxy;

	double dColorTemp; // Native from EDID
	double dGamma;		// Native from EDID;

	dXYZ Red;
	dXYZ Green;
	dXYZ Blue;
	dXYZ White;					// the white from the EDID
	dXYZ SynthesizedWhite;		// the sum of the XYZ whites 

	double dXYZ2RGBmatrix[9];
	double dRGB2XYZmatrix[9];
	
	bool    bECmonitor; // true if monitor is enable cable controlled

	

	short   sRGain;
	short   sGGain;
	short   sBGain;
	short   sRbias;
	short   sGbias;
	short   sBbias;

	short	sGainLimit;
	short	sBiasLimit;

	short   sNumMeasurements;
	dYxy    Measurements[MAX_SPECTRA]; 
	double dColorTempFinal;
	double dGammaFinal;
	
		
}MonitorDefaults;

#define CT_LOW		4000
#define CT_HIGH     10000

#define CUBE_ROOT(x)	pow(x,1./3.)
#define SQR_ROOT(x)     pow(x,.5)
#define SQUARE(x)       (x*x)
#define CUBED(x)       (x*x*x)
typedef double E_STAR;
typedef double C_STAR;
typedef double H_AngleDegrees;
#define _CIE_PI_ 3.14159265358979323846
#define _DEGREES_PER_RAD_ (180.0/_CIE_PI_)
#ifdef __cplusplus
extern "C"
{
#endif


double dCalcH(LABColor *in1);
double dCalcCStar(LABColor *in1);	
LABColor * Yxy2LAB(YxyColor *in, YxyColor *ref, LABColor *out);
LUVColor * Yxy2LUV(YxyColor *in, YxyColor *ref, LUVColor *out);
E_STAR DE94(LABColor *in1,LABColor *in2);
E_STAR DE2000(LABColor *in1,LABColor *in2);
E_STAR DE76(LABColor *in1,LABColor *in2);



void Yxy2XYZ(YxyColor *in, XYZColor *out);
void Yxy2LuvP(YxyColor *in, LuvPColor *out);
void Yxy2Luv(YxyColor *in, LuvColor *out);

YxyColor * XYZ2Yxy(XYZColor  *in, YxyColor *out);
E_STAR CalcDeltaE(YxyColor *c1, YxyColor *c2, YxyColor *Ref);
C_STAR CalcDeltaC(YxyColor *c1, YxyColor *c2, YxyColor *Ref);
LHCColor * CalcLHC(LABColor *in, LHCColor *out);
XYZColor * LHC2XYZ(LHCColor *in, XYZColor *out,XYZColor *ref);
XYZColor * LAB2XYZ(LABColor *in, XYZColor *out,XYZColor *ref);

void Lab2sRGB(LABColor *in , dRGBColor *out);
void XYZ2RGB(XYZColor *in , dRGBColor *out);
void XYZ2RGBNoScale(XYZColor *in , dRGBColor *out);


double Pxy2Kelvin(double x, double y	);
short Kelvin2xy(double ColorTemp,double *x, double *y);
short find_yd(double x,double *yd);
void MakeICCXYZRelativeFromYxy(icS15Fixed16Number *icX,
											  icS15Fixed16Number *icY,
											  icS15Fixed16Number *icZ,
											  dYxy data,dYxy white);

void MakeICCXYZRelativeData(dXYZ *XYZdata);
void MakeICCXYZ_PCSRelativeData(dXYZ *XYZdata);

void FindMonitorXYZFromDefaults(MonitorDefaults *md);
void FindControlXYZ2ControlMatrix(MonitorDefaults *md);
void CalcMonitorXYZfromYxyDefaults(MonitorDefaults *md);
void SwapLongWords(char *abuf,short sCount);
void SwapShortWords(char *abuf,short sCount);
short sToBigEndian(short inVal);
long lToBigEndian(long lVal);
long MakeMod4(long lSize);

void ICCCalcMediaWhiteXYZ(icS15Fixed16Number* icX,icS15Fixed16Number* icY,icS15Fixed16Number* icZ,MonitorDefaults *md);


void MakeICCXYZFromYxy(icS15Fixed16Number *icX,
					   icS15Fixed16Number *icY,
					   icS15Fixed16Number *icZ,
					   dYxy data);
short Spec5_2ChromaRGB(double *spectrum, dRGBColor *rgb);
short Spec5_2XYZ(double *spectrum, XYZColor *XYZ);

#ifdef __cplusplus
}
#endif
#endif

