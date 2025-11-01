#ifndef MEASUREMENTSET_H_INCLUDED
#define MEASUREMENTSET_H_INCLUDED

#include "cieColor.h"

typedef enum _sicmMeasurementSetDescriptor 
{
		smsd_ColorPlus18, // WRGB + 18 gray
		smsd_ExtendedDark, //45 data points, from 0 to 44
		smsd_NdataSets // the number of defined data sets
		
}SMSD;

typedef struct _sicmRGB {
	short sR;
	short sG;
	short sB;
}sicmRGB;


typedef struct _sicmMeasurementSet
{
	
	bool bMeasurementSetComplete;
	short nMeasurements;
	bool bRelativeLuminance; // relative or absolute; 
	SMSD smsdDescriptor; // format of data in the data set
	dRGB dRGBData[256]; // scaled command rgb 0->1.0
	
	dYxy dYxyData[256]; // absolute Measured Data;
	
	dYxy dYxyDesired[256]; // relative Luminance true: Data 0->1.0;
	
	sicmRGB sRGB[256]; // the setting of the display to achieve the desired point;
	
	double dAmbient; // a measured ambient value;
	double dMonitorGamma;
	
}sicmMeasurementSet;
#endif
