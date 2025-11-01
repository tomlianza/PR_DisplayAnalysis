// LenscapSensorInterface.h: interface for the CLenscapSensorInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LenscapSensorInterface_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_)
#define AFX_LenscapSensorInterface_H__7F69C65A_0003_4A17_902D_44F42388A319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cieColor.h"
#include "matrix.h"
#include "LenscapSensorInterfaceBase.h"

typedef enum {TYPE_YXY = 40, TYPE_XYZ = 41, TYPE_RGB = 42, TYPE_DELTARGB = 43} MEASUREMENT_TYPE;

class CLenscapSensorInterface : public CLenscapSensorInterfaceBase
{
public:	
	bool xscp_Init();
	bool xscp_OpenComPort(short sID, bool bInit=TRUE); 
	long MeasureYxy();
	long SensorInit (char *returnedInfo);
	char SetGetLuminanceUnits (char type);
	char SetGetDeltaRGBReference (char type, double *d1=NULL, double *d2=NULL, double *d3=NULL);
	char SetGetSyncMode (char type);
	char SetGetMeasurementMode (char type);
	char SetGetCharValue (int cmd, char type);
	bool Measure(MEASUREMENT_TYPE type, double* f1, double* f2, double* f3, bool measure = 1);
	double GetIntegrationTime();
	double SetIntegrationTime(double d);
};
#endif
