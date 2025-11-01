#ifndef CDISPLAYDDCDESCRIPTOR_H_INCLUDED
#define CDISPLAYDDCDESCRIPTOR_H_INCLUDED


#include "stdafx.h"

#include "ciecolor.h"
#include "mccsEnums.h"
#include "ab_i2c.h"
#include "CGenericCalibrator.h"
#include "CVesaMonitor.h" 
#include "CCalTargetDisplay.h"

#define  ADD_RATIO_LOW			.95
#define  ADD_RATIO_HIGH			1.05

typedef struct AdditvityRatio 
{
	double Xr;
	double Yr;
	double Zr;
}ADDITIVITY_RATIO;

typedef struct Photometry
{
	dYxy White;
	dYxy Red;
	dYxy Green;
	dYxy Blue;

	dYxy Cyan;
	dYxy Magenta;
	dYxy Yellow;

	dYxy Grey;
	dYxy Black;

	dYxy Luminance18[18];


	ADDITIVITY_RATIO	aWhite;
	ADDITIVITY_RATIO	aCyan;
	ADDITIVITY_RATIO	aMagenta;
	ADDITIVITY_RATIO	aYellow;

	bool	bWhiteAdditive;
	bool    bCyanAdditive;
	bool	bMagentaAdditive;
	bool    bYellowAdditive;

}DDC_PHOTOMETRY;

//This enumeration describes mechanism to use to get to Color temperature
typedef enum {

	DDCA_NO_CAN_DO_CTA = -1,
	DDCA_USE_RGBGAINS ,
	DDCA_USE_NEAREST_PRESET,
	DDCA_USE_CT_ADJUST,
	DDCA_USE_OBI_WAN_EXPLCIT,
	DDCA_N_CT_METHODS

}DDC_CT_METHOD;
// This enumeration describes mechanism to set Gamma 

typedef enum {

	DDCA_NO_CAN_DO_GAMMA = -1,
	DDCA_GRAPHIC_CARD_LUT,
	DDCA_ON_BOARD_GAMMA,
	DDCA_ON_BOARD_LUT,
	DDCA_MATRIX_SHAPER_LUT,
	DDCA_N_LUTMETHODS

}DDC_GAMMA_METHOD;

typedef enum {
	DDCA_NO_LUMINANCE_SATURATION = -1,
	DDCA_USE_VIDEO_CONTRAST,
	DDC_N_SATMETHODS
}DDC_LUM_SAT_METHOD;

typedef enum {
	DDCA_NO_LUMINANCE_SET_METHOD = -1,
	DDCA_LUM_USE_LUMINANCE, 
	DDCA_LUM_USE_VIDEO_CONTRAST,
	DDCA_LUM_USE_BACKLIGHT,
	DDCA_N_LUM_METHODS
}DDC_LUM_SET_METHOD;

typedef enum {
	DDCA_NO_BLACKPOINT_SET_METHOD = -1,
	DDCA_BP_USE_BRIGHTNESS,
	DDCA_N_BP_METHODS
}DDC_BLACKPOINT_SET_METHOD;

typedef struct enumerated_preset_ct 
	{
		double				dCT;
		COLOR_PRESET_TYPE	which_preset;

	}ENUMERATED_PRESET_CT;
// The control abstract contains the DDC control that is used for the abstracted control.  A 0 or -1 indicates that there is no control for this function.  

typedef struct ControlAbstract
{

	short					ddca_Luminance;
	short					ddca_Contrast;
	short					ddca_LuminanceSaturationValue;
	short					ddca_BlackPoint;
	short					ddca_nEnumeratedPresetCTs;
	ENUMERATED_PRESET_CT	ddca_dEnumeratedPresetCT[25];
	short					ddca_sColorTempIncrement;

	
}DDC_CONTROL_ABSTRACT;

typedef struct DisplayDDCDescriptor
{

// These booleans describe some basic capabilities at rather high level
	
	bool                    ddca_USERPreset1Present;
	bool					ddca_ColorResetPresent;
	bool                    ddca_FactoryResetPresent;
                   
	
	bool                    ddca_SaturationCapable;
	bool                    ddca_ExplicitWhitePointCapable; 
	bool					ddca_DisplayIsColorimetricallyAdditive;	
	bool					ddca_BlackPointAdjustmentCapable;
	bool					ddca_RGBGainsPresent;
	bool					ddca_RGBBiasPresent;
	
	bool                    ddca_ColorTempIncPresent;
	bool					ddca_DisplayGammaAdjustmentPresent;
	bool                    ddca_DisplayInternalLutPresent;
	
	
	// These are the recommended enumerated methods for setting a particular calibration function 
	
	DDC_GAMMA_METHOD				ddca_GammaMethod;
	DDC_CT_METHOD					ddca_CTMethod;		
	DDC_LUM_SAT_METHOD				ddca_LuminanceSaturationMethod;
	DDC_LUM_SET_METHOD				ddca_SetLuminanceMethod;
	DDC_BLACKPOINT_SET_METHOD		ddca_Set_BPMethod;
	
// This structure contains a number of physical ddc commands for the particular command set. 

	DDC_CONTROL_ABSTRACT	ddca_AbstractCommands;
	DDC_PHOTOMETRY			  ddc_photometry;
	// this is the parsed capability string from the EDID 
	CAPABILITIES			DisplayCapabilities;  
	// defined in ab_i2c.h and bascially copied from the CVesaMonitor after opening

}DISPLAY_DDC_DESCRIPTOR;


class CDisplayDDCDescriptor
{

public:
	
	// the structure that contains the abstractions and other data that is discovered and calculated by this Class.  
	DISPLAY_DDC_DESCRIPTOR    ddc_descriptor; 
	// this structure contains physical measurements of the display; 
	
	
	
// These pointers are set by the application 
	CWnd					 *mp_TargetDisplayWindow;
	CCalTargetDisplay		 *mp_CalTargetDisplay; 
	CGenericCalibrator		 *mp_Calibrator;
	CVesaMonitor			 *mp_Display;

	double 					m_SaturationResponse[256];
	double                  m_ContrastRatio[256];

	CDisplayDDCDescriptor();
	~CDisplayDDCDescriptor();
	
	DiscoverAll();
	PrintDescriptorReport();
private:
	//Discovery Functions 
	char m_DisplayName[2048];
	DiscoverLuminanceControl();  
	DiscoverBlackLevelControl();
	DiscoverSaturationValue();
	DiscoverRGBGains();
	DiscoverRGBBiasControls();
	DiscoverColorTemperatureAdjustMethod();
	DiscoverLuminanceSaturationControl();
	DiscoverColorAdditivity(); 
	DiscoverGammaMethod(); 
	DiscoverResetControls();  

    MeasurePhotometry(); 
	TestAdditivity();
	double MeasureContrastRatio();
	DiscoverColorTemperaturePresets();



};

#endif