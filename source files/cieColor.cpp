#include "stdafx.h"
#ifndef _CIECOLOR_
#define _CIECOLOR_

//#define MK_LIB

#include "Matrix.h"
#ifdef MK_LIB
#include "math.h"
#include "cieColor.h"

typedef unsigned long DWORD; 
#define NULL  ((void *)0)
#include <malloc.h>
#else
//#include "stdafx.h"
#include "math.h"
#include "cieColor.h"
#include <string.h>
#include <stdio.h>
#ifdef WIN32
#include <conio.h>
#include <dos.h>
#include <malloc.h>
#include <TCHAR.H >
#else
#include <cstdlib> 
using namespace std;
#endif

#endif
#define  RELATIVE_PRIMARIES

#define SINGLE_POINT_TRC


double dXYZ2sRGBMatrix[]= 
{3.2410,-1.5374,-0.4986,
 -.9692,1.8760,.0416,
 .0556,-.2040,1.0570};

double d65XYZ[]= {.950455927,1.000,1.08905775076};


double x_cmf5[81] = 
{
	
	    0.0014,
		0.0022,
		0.0042,
		0.0076,
		0.0143,
		0.0232,
		0.0435,
		0.0776,
		0.1344,
		0.2148,
		0.2839,
		0.3285,
		0.3483,
		0.3481,
		0.3362,
		0.3187,
		0.2908,
		0.2511,
		0.1954,
		0.1421,
		0.0956,
		0.058,
		0.032,
		0.0147,
		0.0049,
		0.0024,
		0.0093,
		0.0291,
		0.0633,
		0.1096,
		0.1655,
		0.2257,
		0.2904,
		0.3597,
		0.4334,
		0.5121,
		0.5945,
		0.6784,
		0.7621,
		0.8425,
		0.9163,
		0.9786,
		1.0263,
		1.0567,
		1.0622,
		1.0456,
		1.0026,
		0.9384,
		0.8544,
		0.7514,
		0.6424,
		0.5419,
		0.4479,
		0.3608,
		0.2835,
		0.2187,
		0.1649,
		0.1212,
		0.0874,
		0.0636,
		0.0468,
		0.0329,
		0.0227,
		0.0158,
		0.0114,
		0.0081,
		0.0058,
		0.0041,
		0.0029,
		0.002,
		0.0014,
		0.001,
		0.0007,
		0.0005,
		0.0003,
		0.0002,
		0.0002,
		0.0001,
		0.0001,
		0.0001,
		0
		
};

double y_cmf5[81] =
{
		0,
		0.0001,
		0.0001,
		0.0002,
		0.0004,
		0.0006,
		0.0012,
		0.0022,
		0.004,
		0.0073,
		0.0116,
		0.0168,
		0.023,
		0.0298,
		0.038,
		0.048,
		0.06,
		0.0739,
		0.091,
		0.1126,
		0.139,
		0.1693,
		0.208,
		0.2586,
		0.323,
		0.4073,
		0.503,
		0.6082,
		0.71,
		0.7932,
		0.862,
		0.9149,
		0.954,
		0.9803,
		0.995,
		1,
		0.995,
		0.9786,
		0.952,
		0.9154,
		0.87,
		0.8163,
		0.757,
		0.6949,
		0.631,
		0.5668,
		0.503,
		0.4412,
		0.381,
		0.321,
		0.265,
		0.217,
		0.175,
		0.1382,
		0.107,
		0.0816,
		0.061,
		0.0446,
		0.032,
		0.0232,
		0.017,
		0.0119,
		0.0082,
		0.0057,
		0.0041,
		0.0029,
		0.0021,
		0.0015,
		0.001,
		0.0007,
		0.0005,
		0.0004,
		0.0002,
		0.0002,
		0.0001,
		0.0001,
		0.0001,
		0,
		0,
		0,
		0
};

double z_cmf5[81] =
{
	    0.0065,
		0.0105,
		0.0201,
		0.0362,
		0.0679,
		0.1102,
		0.2074,
		0.3713,
		0.6456,
		1.0391,
		1.3856,
		1.623,
		1.7471,
		1.7826,
		1.7721,
		1.7441,
		1.6692,
		1.5281,
		1.2876,
		1.0419,
		0.813,
		0.6162,
		0.4652,
		0.3533,
		0.272,
		0.2123,
		0.1582,
		0.1117,
		0.0782,
		0.0573,
		0.0432,
		0.0298,
		0.0203,
		0.0134,
		0.0087,
		0.0057,
		0.0039,
		0.0027,
		0.0021,
		0.0018,
		0.0017,
		0.0014,
		0.0011,
		0.001,
		0.0008,
		0.0006,
		0.0003,
		0.0002,
		0.0002,
		0.0001,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		
};

// theoretical sensitivity of the Chroma products...

double r_sens[81] = {
	0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		2.164771578,
		4.230388588,
		18.99409037,
		32.8388176,
		45.90068089,
		58.94288897,
		60.19399047,
		59.63554772,
		55.51121906,
		52.74617998,
		48.3625059,
		45.07254794,
		41.875408,
		36.5922068,
		31.37488973,
		27.08731529,
		23.32924754,
		19.99077521,
		16.19026698,
		13.44882857,
		10.89443187,
		9.055926989,
		7.141805954,
		5.896454855,
		4.770719429,
		3.752304039,
		2.890707571,
		2.324069843,
		1.905059386,
		2.101995768,
		1.836408604,
		1.207916075,
		1.793143037,
		3.889383058,
		1.607944462,
		2.274547071,
		4.060493917,
		4.672948286,
		4.914676548,
		3.466243136,
		3.209510846,
		5.303783064,
		3.411076517,
};

double g_sens[81]=
{
	0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0.165252149,
		0.731739098,
		1.055120722,
		2.457417148,
		3.966627137,
		9.162376243,
		14.83102404,
		23.90668921,
		33.82747134,
		40.8672525,
		48.04385594,
		49.97806277,
		50.9092741,
		48.37616926,
		46.1243172,
		42.05102891,
		37.95396002,
		32.98887782,
		27.8,
		22.57076446,
		16.98463308,
		12.56043289,
		8.367801603,
		5.653003087,
		3.081390392,
		2.125031522,
		1.222881514,
		0.738815129,
		0.294940586,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0.02202349,
		0.080030664,
		0.128686038,
		0.158227524,
		0.232779155,
		0.366061516,
		0.347794219,
		0.675159062,
		1.714257428,
		0.783494533,
		1.234250349,
		2.428202342,
		3.265371393,
		3.700974588,
		2.802167762,
		2.77233495,
		4.698811131,
		2.946444832
};

double b_sens[81] =
{
	
	1.027874876,
		1.027874876,
		2.06691697,
		2.71030316,
		4.02362631,
		6.532023235,
		10.11076312,
		14.83695142,
		18.27819555,
		22.24064972,
		26.08597688,
		28.20345237,
		29.96170344,
		30.43044016,
		31.47172969,
		30.59022851,
		29.80611025,
		27.71839998,
		25.65000744,
		22.68391205,
		20.72012431,
		17.4397346,
		14.73318651,
		11.60844049,
		8.54669182,
		5.923781397,
		3.748920792,
		2.694544121,
		1.104456458,
		0.566858935,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0.014665087,
		0.042707177,
		0.048156123,
		0.099288097,
		0.271352306,
		0.178066939,
		0.352642957,
		0.809400781,
		1.299421168,
		1.7416351,
		1.49704853,
		1.634966765,
		2.936756957
};

static dXYZ m_MediaWhitePoint;
#ifdef WIN32
static _TCHAR *CopyRight = _T( "Copyright 2000 Sequel Imaging Inc." );
#else
const char *CopyRight = "Copyright 2000 Sequel Imaging Inc.";
#endif
/*  To do ;
E_STAR DE2000(LABColor *in1,LABColor *in2);

*/

E_STAR DE76(LABColor *in1,LABColor *in2)
{

	double dE ;
	dE = SQUARE((in1->L-in2->L));
	dE += SQUARE((in1->A-in2->A));
	dE += SQUARE((in1->B-in2->B));
	dE = sqrt(dE);
	return (dE)
		;

}

double dCalcCStar(LABColor *in1)
{
	return(SQR_ROOT(SQUARE(in1->A)+SQUARE(in1->B)));
}
double dCalcH(LABColor *in1)
{
	double dAngle = atan2(in1->B,in1->A);
	dAngle *= _DEGREES_PER_RAD_ ;
	if(dAngle < 0) dAngle += 360.0;
	return dAngle;
}
E_STAR DE94(LABColor *in1,LABColor *in2)
{
	double dDeltaE,dDeltaC,dDeltaH,dDeltaL ;
	double dC1,dC2,dSL,dSC,dSH,da,db;
	double dKL,dKC,dKH,dk1,dk2;

	dC1 = sqrt(in1->A*in1->A+in1->B*in1->B);
	dC2 = sqrt(in2->A*in2->A+in2->B*in2->B);
	dDeltaC = dC1-dC2;
	
	da = in1->A -in2->A;
	db = in1->B -in2->B;

	dDeltaH = sqrt((da*da)+(db*db) - (dDeltaC*dDeltaC));

	dDeltaL = in1->L - in2->L;

	dk1 = .0045;
	dk2 = .0015;
	dKL = 1;
	dKH = 1;
	dKC = 1;
	dSL = 1;
	dSC = 1+dk1*dC1;
	dSH = 1+dk2*dC1;

	dDeltaE = (dDeltaL*dDeltaL)/(dKL*dSL);
	dDeltaE += (dDeltaC*dDeltaC)/(dKC*dSC);
	dDeltaE += (dDeltaH*dDeltaH)/(dKH*dSH);
	dDeltaE = sqrt(dDeltaE);
	return(dDeltaE);


}

void SwapLongWords(char *abuf,short sCount)
{
	short j,i;
	char cComp[4];
	
	for(j=0;j<sCount; j=j+4)
	{
		for(i=0; i<4; i++)
		{
			cComp[i] = abuf[j+i]; // Fill the buffer with a 4 byte word
			
		}
		for(i=0; i<4; i++)
		{
			abuf[j+i] = cComp[3-i] ;// Swap the four bytes for Intel format
			
		}
		
		
	}// buffer swapped
};

void SwapShortWords(char *abuf,short sCount)
{
	
	short j,i;
	char cComp[2];
	
	for(j=0;j<sCount; j=j+2)
	{
		for(i=0; i<2; i++)
		{
			cComp[i] = abuf[j+i]; // Fill the buffer with a 2 byte word
			
		}
		for(i=0; i<2; i++)
		{
			abuf[j+i] = cComp[1-i] ;// Swap the two bytes for Intel format
			
		}
		
		
	}// buffer swapped
}

short sToBigEndian(short inVal)
{
	
	short outval;
	outval = inVal;
	SwapShortWords((char *)&outval,1);
	
	
	return(outval);
}

long lToBigEndian(long lVal)
{
	
	long loutval;
	char tempVal[4], *cptr;
	
	cptr = (char *)&lVal;
	
	tempVal[0] = cptr[3];
	tempVal[1] = cptr[2];
	tempVal[2] = cptr[1];
	tempVal[3] = cptr[0];
	
	memcpy((char*)&loutval,tempVal,4);
	
	return(loutval);
}

long MakeMod4(long lSize)
{
	
	
		long   lInc ;

	if(lSize <= 4) lInc = 4; // if the size is less than or equal to 4 set it to 4
	
	if((lSize/4.0)-(lSize >>2) > 1) // if the size is greater than an integer multiple of four round it to an integer mult of 4
		lInc = ((lSize >> 2) +1) * 4;
	else
	lInc = lSize;
	
	return (lInc);
	
	
	
}

void MakeICCXYZRelativeData(dXYZ *XYZdata)
{
	
	//Normalize data as per the ICC specification..........
	
	XYZdata->X *= d50X/m_MediaWhitePoint.X;
	XYZdata->Y *= d50Y/m_MediaWhitePoint.Y;
	XYZdata->Z *= d50Z/m_MediaWhitePoint.Z;
}

void MakeICCXYZ_PCSRelativeData(dXYZ *XYZdata)
{
	
	//Normalize data as per the ICC specification..........
	
	XYZdata->X /= d50X;
	XYZdata->Y /= d50Y;
	XYZdata->Z /= d50Z;
}
void MakeICCXYZRelativeFromYxy(icS15Fixed16Number *icX,
							   icS15Fixed16Number *icY,
							   icS15Fixed16Number *icZ,
							   dYxy data,dYxy white)
{
	dXYZ tempXYZ;
	
	tempXYZ.Y = data.Y/white.Y;
	tempXYZ.X = (data.Y * data.x/data.y)/white.Y ;
	tempXYZ.Z = ((1-data.x -data.y)*data.Y/data.y)/white.Y;
	
	MakeICCXYZRelativeData(&tempXYZ);
	
	*icX = (long)(65536 * tempXYZ.X);
	*icY = (long)(65536 * tempXYZ.Y);
	*icZ = (long)(65536 * tempXYZ.Z);
	
}

void MakeICCXYZFromYxy(icS15Fixed16Number *icX,
					   icS15Fixed16Number *icY,
					   icS15Fixed16Number *icZ,
					   dYxy data)
{
	dXYZ tempXYZ;
	
	tempXYZ.Y = data.Y;
	tempXYZ.X = (data.Y * data.x/data.y) ;
	tempXYZ.Z = (data.Y*(1-data.x -data.y)/data.y);
	
#ifdef RELATIVE_PRIMARIES
	MakeICCXYZRelativeData(&tempXYZ);
#endif
	*icX = (long)(65536 * tempXYZ.X);
	*icY = (long)(65536 * tempXYZ.Y);
	*icZ = (long)(65536 * tempXYZ.Z);
	
}
void ICCCalcMediaWhiteXYZ(icS15Fixed16Number *icX,
						  icS15Fixed16Number *icY,
						  icS15Fixed16Number *icZ,
						  MonitorDefaults *md)
						  
{
	
	dXYZ tempXYZ;
	// Calculated the sum RGB sum of white
	tempXYZ.Y = md->RedYxy.Y;
	tempXYZ.X =md->RedYxy.Y *md->RedYxy.x/md->RedYxy.y ;
	tempXYZ.Z = (1-md->RedYxy.x -md->RedYxy.y)*md->RedYxy.Y/md->RedYxy.y;
	
	tempXYZ.Y +=md->GreenYxy.Y;
	tempXYZ.X +=md->GreenYxy.Y *md->GreenYxy.x/md->GreenYxy.y ;
	tempXYZ.Z += (1-md->GreenYxy.x -md->GreenYxy.y)*md->GreenYxy.Y/md->GreenYxy.y;
	
	tempXYZ.Y +=md->BlueYxy.Y;
	tempXYZ.X +=md->BlueYxy.Y *md->BlueYxy.x/md->BlueYxy.y ;
	tempXYZ.Z += (1-md->BlueYxy.x -md->BlueYxy.y)*md->BlueYxy.Y/md->BlueYxy.y;
	//Normalize this result by the absolute Y
	tempXYZ.X /= tempXYZ.Y;
	tempXYZ.Z /= tempXYZ.Y;
	tempXYZ.Y /= tempXYZ.Y;
	
	m_MediaWhitePoint = tempXYZ;
	
	*icX = (long)(65536 * tempXYZ.X);
	*icY = (long)(65536 * tempXYZ.Y);
	*icZ = (long)(65536 * tempXYZ.Z);
	
	
	
}

short Spec5_2ChromaRGB(double *spectrum, dRGBColor *rgb)
{
	short i;
	
	rgb->R = 0;
	rgb->G = 0;
	rgb->B = 0;
	
	for(i= 0; i<81; i++)
	{
		rgb->R += spectrum[i] * r_sens[i];
		rgb->G += spectrum[i] * g_sens[i];
		rgb->B += spectrum[i] * b_sens[i];
		
		
	}
	
	return (0);
}




short Spec5_2XYZ(double *spectrum, XYZColor *XYZ)
{
	
	short i;
	
	XYZ->X = 0;
	XYZ->Y = 0;
	XYZ->Z = 0;
	
	for(i= 0; i<81; i++)
	{
		XYZ->X += spectrum[i] * x_cmf5[i];
		XYZ->Y += spectrum[i] * y_cmf5[i];
		XYZ->Z += spectrum[i] * z_cmf5[i];
		
		
	}
	
	return (0);
}

//-------------------------------------------------------------------------------
// Lab2sRGB
//-------------------------------------------------------------------------------
void Lab2sRGB(LABColor *in , dRGBColor *out)
{
	XYZColor TempXYZ;


	LAB2XYZ(in, &TempXYZ,(XYZColor *)d65XYZ);


	XYZ2RGB(&TempXYZ, out);

}


//-------------------------------------------------------------------------------
// XYZ2RGB
//-------------------------------------------------------------------------------
void XYZ2RGB(XYZColor *in , dRGBColor *out)
{
	MatMult(dXYZ2sRGBMatrix,3,3,(double *)in,3,1,(double *)out);

	// check for negatives!

	if (out->R > 0) {
		out->R = pow(out->R, 0.45);
	} else {
		out->R = 0;
	}
	if (out->G > 0) {
		out->G = pow(out->G, 0.45);
	} else {
		out->G = 0;
	}
	if (out->B > 0) {
		out->B = pow(out->B, 0.45);
	} else {
		out->B = 0;
	}

	if (out->R > 1) {
		out->R = 1;
	}
	if (out->G > 1) {
		out->G = 1;
	}
	if (out->B > 1) {
		out->B = 1;
	}
}


//-------------------------------------------------------------------------------
// Yxy2LAB
//-------------------------------------------------------------------------------
LABColor * Yxy2LAB(YxyColor *in, YxyColor *ref, LABColor *out)
{
	XYZColor theColor, theWhite;
	double	dXratio, dYratio, dZratio;
	double	fX, fY, fZ;
	
	Yxy2XYZ(in,&theColor);
	Yxy2XYZ(ref,&theWhite);
	
	if(theWhite.Y == 0.0)
	{
		out->L = -1;
		out->A = -1;
		out->B = -1;
		return(out);
	}
	
	// calculate XYZ ratios to White
	dXratio = theColor.X / theWhite.X;
	dYratio = theColor.Y / theWhite.Y;
	dZratio = theColor.Z / theWhite.Z;
	
	// calculate L*
	if(dYratio <= 0.008856)
		out->L = 903.3 * dYratio;
	else
		out->L = CUBE_ROOT(dYratio) * 116.0 - 16.0;
	
	// calculate intermediate values: fX, fY, fZ
	if(dXratio <= 0.008856)
		fX = (7.787 * dXratio) + (16.0 / 116.0);
	else
		fX = CUBE_ROOT(dXratio);
	
	if(dYratio <= 0.008856)
		fY = (7.787 * dYratio) + (16.0 / 116.0);
	else
		fY = CUBE_ROOT(dYratio);
	
	if(dZratio <= 0.008856)
		fZ = (7.787 * dZratio) + (16.0 / 116.0);
	else
		fZ = CUBE_ROOT(dZratio);
	
	// calculate a*
	out->A = 500 * (fX - fY);
	
	// calculate b*
	out->B = 200 * (fY - fZ);
	
	return(out);
};

LUVColor * Yxy2LUV(YxyColor *in, YxyColor *ref, LUVColor *out)
{
	double up,vp,upN,vpN ;

	up=( 4*in->x)/(-2*in->x + 12*in->y + 3);
	upN = ( 4*ref->x)/(-2*ref->x + 12*ref->y + 3);
	vp=( 9*in->y)/(-2*in->x + 12*in->y + 3);
	vpN = ( 9*ref->y)/(-2*ref->x + 12*ref->y + 3);

	out->L = 116*pow((in->Y/ref->Y),1/3.)-16.;
	out->U = 13*out->L*(up-upN);
	out->V = 13*out->L*(vp-vpN);


	return(out);
}

void Yxy2XYZ(YxyColor *in, XYZColor *out)
{
	out->X = in->x*in->Y/in->y;
	out->Y = in->Y;
	out->Z = (1.0 - in->x - in->y) * (in->Y / in->y);
	//	out->Z = in->z*in->Y/in->y;
};




YxyColor * XYZ2Yxy(XYZColor  *in, YxyColor *out){
	
	double dSUM;
	
	dSUM = in->X + in->Y +in->Z;
	
	out->Y = in->Y;
	out->x = in->X / dSUM;
	out->y = in->Y / dSUM;
	out->z = in->Z / dSUM;
	
	return(out);
};


E_STAR CalcDeltaE(YxyColor *c1, YxyColor *c2, YxyColor *Ref)
{
	LABColor cLab1,cLab2;
	E_STAR	out;
	
	Yxy2LAB( c1,Ref,&cLab1);
	Yxy2LAB( c2,Ref,&cLab2);
	
	out = SQR_ROOT((SQUARE((cLab1.A-cLab2.A))+SQUARE((cLab1.B-cLab2.B))+SQUARE((cLab1.L-cLab2.L))));
	
	return(out);
}

C_STAR CalcDeltaC(YxyColor *c1, YxyColor *c2, YxyColor *Ref)
{
	LABColor cLab1,cLab2;
	C_STAR	out;
	
	Yxy2LAB( c1,Ref,&cLab1);
	Yxy2LAB( c2,Ref,&cLab2);
	
	out = SQR_ROOT((SQUARE((cLab1.A-cLab2.A))+SQUARE((cLab1.B-cLab2.B))));
	
	return(out);
}



LHCColor * CalcLHC(LABColor *in, LHCColor *out)
{
	
	
	out->L =in->L;
	out->H = atan2(in->B,in->A);
	out->C = SQR_ROOT(SQUARE(in->B)+SQUARE(in->A));
	return(out);
}

XYZColor * LHC2XYZ(LHCColor *in, XYZColor *out,XYZColor *ref)
{
	
	LABColor temp;
	
	temp.L = in->L;
	temp.A = in->C*cos(in->H);
	temp.B = in->C*sin(in->H);
	
	LAB2XYZ(&temp,out,ref);
	
	return(out);
	
	
}

XYZColor * LAB2XYZ(LABColor *in, XYZColor *out,XYZColor *ref)
{
	
	double ratio, xRatio,zRatio;
	
	
	ratio = (in->L)/903.3;
	
	if(ratio > .008856) // must recalc for other range
		
	{
		
		ratio = (in->L +16)/116;
		ratio = CUBED(ratio);
		
		
	}
	
	// Y/Yref is now calculated;
	
	xRatio  = ( (in->A/500.) + CUBE_ROOT(ratio) );
	zRatio =  (CUBE_ROOT(ratio) - (in->B/200.) ); 
	
	xRatio = CUBED(xRatio);
	zRatio = CUBED(zRatio);
	
	out->X = xRatio * ref->X;
	out->Y = ratio * ref->Y;
	out->Z = zRatio * ref->Z;
	
	return(out);
	
	
	
}

void CalcMonitorXYZfromYxyDefaults(MonitorDefaults *md)
{
	md->BlueYxy.z = 1-md->BlueYxy.x-md->BlueYxy.y;
	md->GreenYxy.z = 1-md->GreenYxy.x-md->GreenYxy.y;
	md->RedYxy.z = 1-md->RedYxy.x-md->RedYxy.y;
	
	md->Blue.Y = md->BlueYxy.Y;
	
	md->Green.Y = md->GreenYxy.Y;
	
	md->Red.Y = md->RedYxy.Y;
	
	
	// The luminances are calculated!! 
	
	// Now calc XYZ values....
	
	md->Blue.X = md->Blue.Y * md->BlueYxy.x/md->BlueYxy.y ;
	md->Blue.Z = md->Blue.Y * md->BlueYxy.z/md->BlueYxy.y ;
	
	md->Green.X = md->Green.Y * md->GreenYxy.x/md->GreenYxy.y ;
	md->Green.Z = md->Green.Y * md->GreenYxy.z/md->GreenYxy.y ;
	
	md->Red.X = md->Red.Y  * md->RedYxy.x/md->RedYxy.y ;
	md->Red.Z = md->Red.Y  * md->RedYxy.z/md->RedYxy.y ;
	
	md->SynthesizedWhite.X = md->Blue.X + md->Green.X + md->Red.X;
	md->SynthesizedWhite.Y = md->Blue.Y + md->Green.Y + md->Red.Y;
	md->SynthesizedWhite.Z = md->Blue.Z + md->Green.Z + md->Red.Z;
	
	/*****************************************************************\
	Note: At this stage the Synthetic white and the White values
	should be identical.  Whenmd start getting made, things
	will change
	\*****************************************************************/
	
	md->dColorTemp = Pxy2Kelvin(md->WhiteYxy.x,md->WhiteYxy.y);
	
}

void FindMonitorXYZFromDefaults(MonitorDefaults *md){
	
	double dMatrix[9], dWhite[3],dLuminance[3];
	
	// This routine calculates the XYZ values for the monitor given only the chromaticities.....
	// first we make sure we've calculated a z value...
	md->BlueYxy.z = 1-md->BlueYxy.x-md->BlueYxy.y;
	md->GreenYxy.z = 1-md->GreenYxy.x-md->GreenYxy.y;
	md->RedYxy.z = 1-md->RedYxy.x-md->RedYxy.y;
	md->WhiteYxy.z = 1-md->WhiteYxy.x-md->WhiteYxy.y;
	// Now we are going to do some tricky matrix math....
	
	
	
	dMatrix[0] = md->BlueYxy.x/md->BlueYxy.y ;		// partial X Blue
	dMatrix[1] = md->GreenYxy.x/md->GreenYxy.y ;	// partial X Green
	dMatrix[2] = md->RedYxy.x/md->RedYxy.y ;		// partial X Red
	
	dMatrix[3] = 1.0;
	dMatrix[4] = 1.0;
	dMatrix[5] = 1.0;
	
	dMatrix[6] = md->BlueYxy.z/md->BlueYxy.y ;		// partial Z Blue
	dMatrix[7] = md->GreenYxy.z/md->GreenYxy.y ;	// partial Z Green
	dMatrix[8] = md->RedYxy.z/md->RedYxy.y ;		// partial Z Red
	
	dWhite[0] = md->WhiteYxy.x/md->WhiteYxy.y;     // White X for luminance = 1.0;
	md->White.X = dWhite[0];
	md->WhiteYxy.Y = 1.0;
	md->White.Y = 1.0;
	dWhite [1] = 1.0;								// White Y 
	dWhite[2] = md->WhiteYxy.z/md->WhiteYxy.y;     // White Z
	md->White.Z = dWhite[2];
	
	
	Invert(dMatrix,3); // invert the matrix
	
	MatMult(dMatrix,3,3,dWhite,3,1,dLuminance); // now multiply this matrix times the white XYZ 
	
	md->Blue.Y = dLuminance[0];
	md->BlueYxy.Y = dLuminance[0];
	
	md->Green.Y = dLuminance[1];
	md->GreenYxy.Y = dLuminance[1];
	
	
	md->Red.Y = dLuminance[2];
	md->RedYxy.Y = dLuminance[2];
	
	// The luminances are calculated!! 
	
	// Now calc XYZ values....
	
	md->Blue.X = dLuminance[0] * md->BlueYxy.x/md->BlueYxy.y ;
	md->Blue.Z = dLuminance[0] * md->BlueYxy.z/md->BlueYxy.y ;
	
	md->Green.X = dLuminance[1] * md->GreenYxy.x/md->GreenYxy.y ;
	md->Green.Z = dLuminance[1] * md->GreenYxy.z/md->GreenYxy.y ;
	
	md->Red.X = dLuminance[2] * md->RedYxy.x/md->RedYxy.y ;
	md->Red.Z = dLuminance[2] * md->RedYxy.z/md->RedYxy.y ;
	
	md->SynthesizedWhite.X = md->Blue.X + md->Green.X + md->Red.X;
	md->SynthesizedWhite.Y = md->Blue.Y + md->Green.Y + md->Red.Y;
	md->SynthesizedWhite.Z = md->Blue.Z + md->Green.Z + md->Red.Z;
	
	/*****************************************************************\
	Note: At this stage the Synthetic white and the White values
	should be identical.  Whenmd start getting made, things
	will change
	\*****************************************************************/
	
	md->dColorTemp = Pxy2Kelvin(md->WhiteYxy.x,md->WhiteYxy.y);
	
	
	
}

void FindControlXYZ2ControlMatrix(MonitorDefaults *md)
{
	
	double dMat1[9], dMat2[9], XYZ[12],RGB[12];
	short i;
	
	XYZ[0] = md->White.X;
	XYZ[1] = md->Red.X;
	XYZ[2] = md->Green.X;
	XYZ[3] = md->Blue.X;
	
	
	XYZ[4] = md->White.Y;
	XYZ[5] = md->Red.Y;
	XYZ[6] = md->Green.Y;
	XYZ[7] = md->Blue.Y;
	
	XYZ[8] = md->White.Z;
	XYZ[9]	= md->Red.Z;
	XYZ[10]	= md->Green.Z;
	XYZ[11] = md->Blue.Z;
	
	
	RGB[0] = 1.0;
	RGB[1] = 1.0;
	RGB[2] = 0;
	RGB[3] = 0;
	
	RGB[4] = 1.;
	RGB[5] = 0;
	RGB[6] = 1;
	RGB[7] = 0.;
	
	RGB[8] = 1.;
	RGB[9] = 0;
	RGB[10] = 0;
	RGB[11] = 1.0;
	
	
	A_solve(XYZ,3,4,RGB,3,4,dMat1);
	for(i=0; i<9; i++)
		dMat2[i] = dMat1[i];
	
	Invert(dMat2,3);
	
	for(i=0; i<9; i++)
	{
		md->dXYZ2RGBmatrix[i] = dMat2[i];
		md->dRGB2XYZmatrix[i] = dMat1[i];
		
	}
	
}

short Kelvin2xy(double ColorTemp,double *x, double *y)
{
	double T1,T2,T3,xd,yd;
	short err;
	err = 0;
	T1 = ColorTemp;
	T2 = T1*T1;
	T3 = T2*T1;
	
	if (T1 < 4000.0)
		return(-1);
	
	if ((T1 >= 4000) && (T1 < 7000))
    {
		xd = -4607000000./T3;
		xd += 2967800./T2;
		xd += 99.11/T1;
		xd += 0.244063;
		err = find_yd(xd,&yd);
    }
	if ((T1 >=7000) && (T1 < 25000))
    {
		xd = -2006400000./T3;
		xd += 1901800./T2;
		xd += 247.48/T1;
		xd += 0.237040;
		err =find_yd(xd,&yd);
    }
    *x = xd;
    *y = yd;
	return(err);
	
}

short find_yd(double x,double *yd)
{
/* This function uses a quadradic solution to solve for the y term
of the color temperture function.  it is an equation of the form
	y = 2.87x - 3x^2 -.2750*/
	
	double a,b,c;
	
	a = -3.00 *x * x;
	b = 2.870* x;
	c= -.275;
	
	*yd = a + b + c;
	return(0);
}
double Pxy2Kelvin(double x, double y	)
{
/* This function calculates the correlated color temperature of 
an xy point measurement. The method is described in Color Science
Concepts and Mehods, Quantitative Data and Formulae,  Wyszecki and Stiles

	*/
	CTPoint sgColorTempData[31]= 
	{
		{0,0.0,100000000.0,.18006,.2635,-.24341},
		{1,10.,100000.0,.18066,.26589,-.25479},
		{2,20.,50000.0,.18133,.26846,-.26876},
		{3,30.,33333.0,.18208,.27119,-.28539},
		{4,40.,25000.0,.18293,.27407,-.30740},
		{5,50.,20000.0,.18388,.27709,-.32675},
		{6,60.,16667.0,.18494,.28021,-.35156},
		{7,70.,14286.0,.18611,.28342,-.37915},
		{8,80.,12500.0,.18740,.28668,-.40955},
		{9,90.,11111.0,.18880,.28997,-.44278},
		{10,100.,10000.0,.19032,.29326,-.47888},
		{11,125.,8000.0,.19462,.30141,-.58204},
		{12,150.,6667.0,.19962,.30921,-.70471},
		{13,175.,5714.0,.20525,.31647,-.84901},
		{14,200.,5000.0,.21142,.32312,-1.0182},
		{15,225.,4444.0,.21807,.32909,-1.2168},
		{16,250.,4000.0,.22511,.33439,-1.4512},
		{17,275.,3636.0,.23247,.33904,-1.7298},
		{18,300.,3333.0,.24010,.34308,-2.0637},
		{19,325.,3077.0,.24702,.34655,-2.4681},
		{20,350.,2857.0,.25591,.34951,-2.9641},
		{21,375.,2677.0,.26400,.35200,-3.5814},
		{22,400.,2500.0,.27218,.35407,-4.3633},
		{23,425.,2353.0,.28039,.35577,-5.3762},
		{24,450.,2222.0,.28863,.35714,-6.7262},
		{25,475.,2105.0,.29685,.35823,-8.5955},
		{26,500.,2000.0,.30505,.35907,-11.324},
		{27,525.,1905.0,.31320,.35968,-15.628},
		{28,550.,1818.0,.32129,.36011,-23.325},
		{29,575.,1739.0,.32931,.36038,-40.770},
		{30,600.,1667.0,.33724,.36051,-116.45}
	};
	double u,v,Temp,d0,d1 ;
	short i;
	double TempInKelvin;
	
	u = (2.*x)/(-x+6.*y+1.5);
	v = (3.*y)/(-x+6.*y+1.5);	// convert data to uv space
	
	
	for(i=0; i<30; i++)
	{
		
		d0 = (v - sgColorTempData[i].dv)- (sgColorTempData[i].dslope*(u - sgColorTempData[i].du));
		d0 = d0/(sqrt(1+ sgColorTempData[i].dslope*sgColorTempData[i].dslope));
		
		d1 = (v - sgColorTempData[i+1].dv)- (sgColorTempData[i+1].dslope*(u - sgColorTempData[i+1].du));
		d1 = d1/(sqrt(1+ sgColorTempData[i+1].dslope*sgColorTempData[i+1].dslope));
		
		if(d1 == 0) break; //point is on a locus;
		
		if(d0/d1 <= 0)  break;	// point is on the locus or between two points
		
	}
	
	if(i==30)
	{
		TempInKelvin= 0.00;
		return (TempInKelvin);
	}
	
	Temp = (1.0/ sgColorTempData[i].dTemp +((d0/(d0-d1)*( 1.0/ sgColorTempData[i+1].dTemp-1.0/ sgColorTempData[i].dTemp))));
	Temp = 1/Temp;
	
	TempInKelvin = Temp;
	
	// trim to nearest 5 degrees for noise purposes....
	
	short sDiv = (short)TempInKelvin/5;
	Temp = sDiv*5.0;
	/*if((TempInKelvin - Temp) > 2.5)
	TempInKelvin = Temp+ 5.0;
	else
	*/
	TempInKelvin = Temp;
	
	return (TempInKelvin);
}

//-------------------------------------------------------------------------------
// XYZ2RGBNoScale(&tempXYZ, RGBData)
// we use this when we want to take luminance into account as well
// such as detecting saturation in contrast
//-------------------------------------------------------------------------------
void XYZ2RGBNoScale(XYZColor *in , dRGBColor *out){
	MatMult(dXYZ2sRGBMatrix,3,3,(double *)in,3,1,(double *)out);

	// check for negatives!
	if (out->R > 0) {
		out->R = pow(out->R, 0.45);
	} else {
		out->R = 0;
	}
	if (out->G > 0) {
		out->G = pow(out->G, 0.45);
	} else {
		out->G = 0;
	}
	if (out->B > 0) {
		out->B = pow(out->B, 0.45);
	} else {
		out->B = 0;
	}

}

#endif