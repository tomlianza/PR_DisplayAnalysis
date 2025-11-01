//#include "stdafx.h"
#ifndef COLORSTATS_H_INCLUDED
#define COLORSTATS_H_INCLUDED

#include "cieColor.h"
#define NPTS_DATA_MAX 128
#define COLORSTATS_DELTAE 2.0

typedef struct _ColorStatData
{
	short    nPts;
	bool     bUseReference;  // if true the Reference is used for calculations of LAB and the delta measures are based on that measure
	dYxy     Reference;  // if false, the Referecne is assumed to be the reference array. 
	dYxy     ref[NPTS_DATA_MAX];
	dYxy     test[NPTS_DATA_MAX];

	LABColor     refLab[NPTS_DATA_MAX];
	LABColor     testLab[NPTS_DATA_MAX];

	dYxy     deltaWhiteYxy[NPTS_DATA_MAX];

	double   Lstar[NPTS_DATA_MAX];
	
	
	double   deltaE[NPTS_DATA_MAX];
	double   deltaL[NPTS_DATA_MAX];
	double   deltaC[NPTS_DATA_MAX];

	double   AverageDeltaE;
	double   AverageDeltaC;
	double   AverageDeltaL;

	double   PeakDeltaE;
	double   PeakDeltaC;
	double   PeakDeltaL;

	bool     bPeakWhiteLuminanceValid;
	double   PeakWhiteLuminance;

}ColorStatData;

// Use this structure for getting statistics from a repeat measurement data set. 
typedef struct _YxyMeasurementSet
{
	short nPts;
	dYxy  YxyData[NPTS_DATA_MAX];
	dYxy  YxyReference; // used for delta E calculations;
	double dYmean;
	double dxmean;
	double dymean;
	double dYstdev;
	double dxstdev;
	double dystdev;
	double PeakDelta_x;
	double PeakDelta_y;
	double PeakDeltaE;
	double AverageDeltaE;

}YxyMeasurementSet;

typedef struct _MeasurementSetCompStats

{


	double dTYval;
	double dTxval;
	double dTyval;

	double dFYval;
	double dFyval;
	double dFxval;



}MeasurementSetCompStats;


// fill the member structure with the Yxy data, reference info and number points and go for it!
class CColorStats 
{
public:
	
	CColorStats();
	virtual ~CColorStats();
		ColorStatData m_ColorStatData;// public data
	bool   CalcStats(int startIndex=0);

	bool   MeasurementsAreDifferent(
				YxyMeasurementSet *data1,		// The input data set 1
				YxyMeasurementSet *data2,		// The input data set 1
				MeasurementSetCompStats *comp, // a pointer to the comparison structure that is declared in the function that call this 
				short dacLevel,
				double dTvalue,					// The value from the T-test table based upon the variables of the experiment
				double dFvalue,					// The value from the T-test table 
				bool *tFlag, 
				bool *fFlag); // if(tflag == TRUE) means are statistically different

	void   CalcMeasurementStats(YxyMeasurementSet *data);

	double TValue(double dMean1, double dMean2, double dStd1, double dStd2,short nPts1, short nPts2); 
	double FValue(double dStd1, double dStd2);
		
	// these will be made private at a later date 
private:
	void ComputeTValue(YxyMeasurementSet *data1,YxyMeasurementSet *data2,MeasurementSetCompStats *comp);
	void ComputeFValue(YxyMeasurementSet *data1,YxyMeasurementSet *data2,MeasurementSetCompStats *comp);
};
#endif
