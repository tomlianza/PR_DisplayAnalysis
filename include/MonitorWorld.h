/*
 * Copyright 1998, Sequel Imaging, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Sequel Imaging, Inc.,
 * 25 Nashua Rd, Londonderry, NH 03053.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SEQUEL IMAGING, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SEQUEL IMAGING, INC.
 */
// MonitorWorld.h: interface for the CMonitorWorld class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITORWORLD_H__5C5EC501_DC89_11D1_865F_444553540000__INCLUDED_)
#define AFX_MONITORWORLD_H__5C5EC501_DC89_11D1_865F_444553540000__INCLUDED_

#if _MSC_VER >= 1000

#pragma once
#endif // _MSC_VER >= 1000


#include "icc.h"
#include "MonitorMeasurements.h"

#define nMaxMonitors		  8
#define N_MAX_PROFILES		300
// White values that represent the ICC color space definition

 #define d50X  0.9642
 #define d50Y  1.0000
 #define d50Z  0.8249

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

typedef struct MonitorDescription
{
	WORD	sMonIndex;
	BOOL	bGammaSupported;
	BOOL	bElectronicChassisSupported;
	WORD	GammaRamp[768];
}MONITORDESCRIPTION;

typedef struct MonitorWorld
{
	WORD nMonitors;
	MONITORDESCRIPTION Monitor[nMaxMonitors];

}MONITORWORLD;

class CMonitorWorld  
{
public:
	CMonitorWorld();
	virtual ~CMonitorWorld();
	void CleanUp();
	//Variables
	MONITORWORLD	AttachedMonitors;

	

	// Make sure that the following pointer is initialized before construction.
	CMonitorMeasurements *syntheticMonitor; //a synthesized set of measurements from an ICC profile;
	BOOL syntheticMeasurementsValid;
	bool m_bProfileComputed;
	 

	icHeader		ICCHeader;
	CStringList		MonitorProfileName;
	CStringList		ProfileDescription; 
	short sProfileCount;
	dXYZ			m_MediaWhitePoint;
	unsigned char 	ICCProfile[32768]; // image of profile
	
	// Hardware and display card functions 
	BuildMonitorList(CDC* mypCDC);

	
// ICC profile functions 

	
	// The synthetic Measurement is found in syntheticMonitor.currentMeasurements;
	
	bool BuildSyntheticMeasurementFromProfile(CString *name);// builds a measurement structure from profile information 
	bool BuildSyntheticMeasurementFromProfile(CString *name,MONITORMEASUREMENTS* whichMeasurement);
	bool BuildSyntheticCurrentMeasurementFromProfile(CString *name); // Builds the current measurement structure only;

	long BuildICCProfile(CString *name, MONITORMEASUREMENTS *data);
//Routines to manipulate the Measurement Struct 
	double GetGammaFromMeasurement(CMonitorMeasurements *measurement);
	double GetColorTempFromMeasurement(CMonitorMeasurements *measurement);
	double GetColorTempPlankianFromMeasurerment(CMonitorMeasurements *measurement);
	

//Routines to get data from profiles
	
	GetICCMonitorProfileNames();// Scans the color directory to get a maximum of N_MAX_PROFILES
	GetICCMonitorProfilePath(CString *path);
	BOOL GetProfileDescription(CString *name,CStringList *description);;
	BOOL CheckIfMonitorProfile(CString *name);
	double GetICCColorTemp(CString *ProfileName);
	double GetICCColorTempPlankian(CString *name);
	
	GetICCMediaWhite(CString *ProfileName);
	
	
	GetICCRedYxy(CString *ProfileName,dYxy *Yxydata);
	GetICCGreenYxy(CString *ProfileName,dYxy *Yxydata);
	GetICCBlueYxy(CString *ProfileName,dYxy *Yxydata);
	GetICCWhiteYxy(CString *ProfileName,dYxy *Yxydata);
	GetICCBlackYxy(CString *ProfileName,dYxy *Yxydata);
	icUInt16Number * GetICCRedTRC(CString *ProfileName, short *count);
	icUInt16Number * GetICCGreenTRC(CString *ProfileName, short *count);
	icUInt16Number * GetICCBlueTRC(CString *ProfileName, short *count);


private:
	icHeader		currentICCHeader;
	icTagTable		currentICCTagTable;


	BOOL ReadICCHeader(icHeader * header,CString * FileName);
	BOOL ReadICCTagTable(icTagTable *tagTable,CString *FileName);
	BOOL ReadICCDescriptionData(icUInt32Number offset, icUInt32Number size,CString *name,CStringList *description);
	BOOL ReadICCXYZdata(icUInt32Number offset, icUInt32Number size,CString *name,dXYZ *XYZdata);	
	BOOL ReadICCTRCdata(icUInt32Number offset, icUInt32Number size,CString *name, char *buffer, long *nEntries);

	void MakeICCXYZRelativeData(dXYZ *XYZdata);
	void MakeICCXYZRelativeFromYxy(icS15Fixed16Number *icX,
											  icS15Fixed16Number *icY,
											  icS15Fixed16Number *icZ,
											  dYxy data,dYxy white);
	void ICCCalcMediaWhiteXYZ(icS15Fixed16Number *icX,
					 icS15Fixed16Number *icY,
					 icS15Fixed16Number *icZ,
					 MONITORMEASUREMENTS *measurements);
	void  GetICCXYZAbsoluteData(dXYZ *XYZdata);
	void SwapLongWords(char *buf, short sCount);
	void SwapShortWords(char *abuf,short sCount);
	short sToBigEndian(short inVal);
	long  lToBigEndian(long inVal);
	void Yxy2XYZ(dYxy *YxyData,dXYZ *XYZdata);
	long  MakeMod4(long lSize);

};

#endif // !defined(AFX_MONITORWORLD_H__5C5EC501_DC89_11D1_865F_444553540000__INCLUDED_)
