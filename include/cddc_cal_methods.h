#include "cdisplayddcdescriptor.h"



#define PROGRAMED_DDC_DELAY		200
#define CONVERGENCE_LIMIT		.008


class CDDC_CalMethods
{
public:
// Required Inputs to the function;	
	DISPLAY_DDC_DESCRIPTOR   *mp_ddc_descriptor;
	CWnd				     *mp_PatchWindow;
	CCalTargetDisplay		 *mp_CalTargetDisplay; 
	CGenericCalibrator		 *mp_Calibrator;
	CVesaMonitor			 *mp_Display;
	
	double dWhite_x, dWhite_y, dLuminance, dBlackLuminance;
	
	bool    m_bIgnoreLumiance_RGBGains;  // this means that we will set for maximum luminance when adjusting rgb gains; 

	//Calculated values;	
	
	double m_MaximumLumianceAtWhite;  

	bool    DoCalibration();
	bool 	SetWhitePointRGBGains();
	bool    SetWhitePointNearestPreset();
	bool    SetAbsoluteLuminance();
	bool    SetBlackPoint();
	bool    SetSaturationValue();
	bool    SetPresetUser1();
private:
	WaitMillisec(DWORD dwMillisecs);

};