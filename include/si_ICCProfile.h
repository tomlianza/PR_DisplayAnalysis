
#include "cieColor.h"
#include "icc.h"

#define MAX_PROFILE_TSL	2048

typedef enum {
	si_ICC_WrongVonKreis = 0,
	si_ICC_BradfordCIECAM97s,
	si_ICC_VonKreis,
	si_ICC_NONE,
	si_ICC_NUM_ADAPTATIONS
}si_AdaptationMethod;

#if defined(WIN32) || defined(LINUX) 
// not needed on OS X Macintosh, definedin CMICCProfile.h in the ColorSync framework.
// might need to define this with CodeWarrior, check later
typedef enum _CustomTag{

	cmVideoCardGammaTag = 'vcgt'

}CustomTag;
#else
//#ifdef QT_KIT
#if 0
//I don't quite understand why this is not necessary in xcode, since it uses gcc also...but
// it isn't.
#include <CMICCProfile.h>
#endif
#endif

// XYZ data formed as a final big endian value for the profile;
typedef struct _icS15_16_XYZ
{
	icS15Fixed16Number X;
	icS15Fixed16Number Y;
	icS15Fixed16Number Z;

}icS15_16_XYZ; 

typedef struct _si_ICCInputData {

//******************************* Data input before calling any routines***************************************
	long					lSize; // the size of this structure must be set before calling methods;
	long                    lProfileSize;  // this size get's initalized to 0 and it is incremented with each function that uses this structure

	// All Yxy Values are based on Y white = 1.0;  The data is the actual display space prior to adaptation.
	dYxy					White;
	dYxy					Red;
	dYxy					Green;
	dYxy					Blue;
	dYxy					Black;

	// All gamma ramps are 1.0000 based;

	double					dRedGammaRamp[256];
	double                  dGreenGammaRamp[256];
	double                  dBlueGammaRamp[256];
// Look up table data scaled 0-1.0
	double					dRedGammaLutRamp[256];
	double                  dGreenGammaLutRamp[256];
	double                  dBlueGammaLutRamp[256];

	
	long					lMaximumProfileTextStringLength; // = MAX_PROFILE_TSL
	char					cCopyRightString[MAX_PROFILE_TSL];
	char                    cProfileDescription[MAX_PROFILE_TSL];
	char                    cProfileName[MAX_PROFILE_TSL];
	
	si_AdaptationMethod		si_AdptWhichAdaptation;
// These values are not used in the current implementation it should be equal to zero  
	double                  dAmbientIllumiance;
	dYxy					dAdaptingLuminanceNits;  // used for chromatic and level adaptation models.
	char					cMonitorName[256];
	char					cMonitorSN[256];
	
	
//**************************************************** End required data for input Methods*********************/

// Data calculated during the process...Internal to functions, but available for debug 

	dXYZ					WhiteXYZ;
	dXYZ					RedXYZ;
	dXYZ					GreenXYZ;
	dXYZ					BlueXYZ;
	dXYZ					BlackXYZ;

	icS15_16_XYZ		icS15WhiteXYZ;
	icS15_16_XYZ		icS15RedXYZ;
	icS15_16_XYZ		icS15GreenXYZ;
	icS15_16_XYZ		icS15BlueXYZ;
	icS15_16_XYZ		icS15BlackXYZ;


// 3X3 matrix stored in row column order...r11,r12,r13,r21,r22......
	// these are two intermediate matrices available for use and debug
	double					dAdaptMat1[9];
	double                  dAdaptMat1Inv[9];
	double                  dAdaptMat2[9];
	//this is the final adaptation matrix 
	double                  dAdaptMat[9];  

// Lut data scaled 0-65535...calculated from above 
	unsigned short          usRedLut[256];
	unsigned short          usGreenLut[256];
	unsigned short          usBlueLut[256];

}si_ICCInputData ;