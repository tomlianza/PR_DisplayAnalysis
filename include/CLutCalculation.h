/**CLutCalculation.h**/
#ifndef CLUTCALCULATION_H_INCLUDED
#define CLUTCALCULATION_H_INCLUDED



#include "GammaRamp.h"
#include "MeasurementSet.h"
#include "interpolator.h"

#define  CSILUT_MAX_DATA	255

class CLutCalculation
{
public:

	CLutCalculation();
	virtual ~CLutCalculation();
	bool CalcLuts();
	bool CalcLuts(double gamma, int colorTemp, CSIGammaRamp *gr, sicmMeasurementSet *mset);
	bool CalcLuts(double gamma, double x_WhiteDesired, double y_WhiteDesired, CSIGammaRamp *gr, sicmMeasurementSet *mset);

	CSIGammaRamp						*m_CRamp;
	double								m_dColorTemp; //Note if set to ZERO calibrate to gamma only, no grey correction. 
	double								m_dGamma;
	sicmMeasurementSet					*m_MeasurementSet;

private:

	void ScaleDataByMinWhite(dRGB *data);
	void BaseReduceData(dRGB *data);
	//void Yxy2XYZ(dYxy *in, dXYZ *out);
	void Normalize_dRGBArray(dRGB *dat);

	dYxy							m_dYxyMeasured[CSILUT_MAX_DATA];
	dYxy							m_dYxyDesired[CSILUT_MAX_DATA];
	dRGB							m_dRGBMeasured[CSILUT_MAX_DATA];
	dRGB							m_dRGBDesired[CSILUT_MAX_DATA];

	
};
#endif