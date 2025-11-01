#ifndef DSDB_H_INCLUDED
#define DSDB_H_INCLUDED

#include "CPresetBase.h"
#include "dmc.h"
#include "MonitorControls.h"
#include "CalibrationInfo.h"
#include "DisplayTechnology.h"
#include "MeasurementSet.h"

#define DSDB_VERSION_NUMBER 15
/*
Version 4 - Added m_MeasurementSet for tracking calibration stats
Version 5 - Added m_OverrideDefaultMDFGains, m_OverrideDefaultMDFBiases 
              for mons that bloom at our defaults
Version 6 - Added 
Version 7 - Added m_bCanAdjustDigitalColorTemp for setting colortemps in strange LCDs
Version 8 - Added m_preferredMonitorPreset
Version 9 - Added floats for holding LUT computation vals for mons that store
				LUTs in their hardware
Version 10- Added displayable name override.
Version 11- Added last Ambient Lux value.
Version 12- Added boolean to determine if we should use last ambient Lux value
Version 13- update to dmc, and MCCS spec
Version 14- more dmc structure updates
Version 15- added calibration warning parameters
*/

#define DSDB_LUTDOUBLE_SIZE 18
#define DSDB_USER_NAME_MAX_SIZE 256

typedef struct DisplaySystemDescriptorBlock
{
	ULONG						ulSize;			// the current size of this structure;
	ULONG						ulNumber;		// a coded value describing which monitor is present.
	short						sVersionID;		// Used to check software revs.					`	
	sicmWorkSpaceDescriptor		sicmWSD;		// describes the Monitor Work space
	CSIGammaRamp				grData;			// the ramps to use to set the calibration:VesaMonitor.h
	MonitorControls				mcData;			// the data used to configure the monitor:VesaMonitor.h
	MonitorDefaults             mdData;			// data used in CIECOLOR .h

	BYTE						btEDID[256];	// the raw data from the display EDID 

	CalibrationInfo				CalInfo;		// includes date of last cal and reminder info

	WHICH_APP					DSDBcreator;	// describes which app created this structure
	bool						bDigitallyEnabled;		// DSDB was created when monitor had Enable Cable attached

	DISPLAY_TECHNOLOGY			m_DisplayTechnology;

	bool						m_bBiasesReversed;
	bool						m_bLiesAboutVCPFeatureSupport;

	// Special settings that come from user-created Monitor Descriptor Files (MDFs):
	// These are used to control calibration of non-digital monitors, allowing the
	// code to determine which adjustments the user is prompted to make.
	bool m_bCanAdjustBrightness;
	bool m_bCanAdjustContrast;
	bool m_bCanAdjustColorTemp;
	bool m_bCanAdjustGains;

	// Data members to track the MDF.
	long m_MDFDefinitionVersion;	// minimum code version needed to understand the MDF.
	long m_MDFFileVersion;			// revision level of the MDF to determine which is newer/older
	char m_MDFSource[256];			// Who/what program generated the MDF
	bool m_MDFIsForNDMonitor;		// MDF was generated for a non-digital monitor only.

    // Track the measurement set for gamma calculations later
    sicmMeasurementSet m_MeasurementSet;

	// Overridden name for display purposes.
	char m_DisplayableName[256];

	int m_InternalLUTDepth;
	int m_InternalLUTChannels;
	
	//for mons that bloom at our default gains, biases
	bool m_OverrideDefaultMDFGains;
	bool m_OverrideDefaultMDFBiases; //for expansion 
	short m_OverriddenMaxGainRed, m_OverriddenMaxGainGreen, m_OverriddenMaxGainBlue;
	short m_OverriddenMaxBiasRed, m_OverriddenMaxBiasGreen, m_OverriddenMaxBiasBlue;

	bool m_bCanAdjustDigitalColorTemp;

	short m_preferredMonitorPreset;

	bool lutDoubleValsSet;
	double RLutVals[DSDB_LUTDOUBLE_SIZE];
	double GLutVals[DSDB_LUTDOUBLE_SIZE];
	double BLutVals[DSDB_LUTDOUBLE_SIZE];


	//store ambient values, and verify we should use them.
	double m_lastAmbientLux;
	bool   m_shouldUseLastAmbientLux;

	time_t timeLastWarnedAsInvalid;
	UINT calExpirationTime;
	UINT calWarningInterval;
	
	char m_UserName[DSDB_USER_NAME_MAX_SIZE];

}DisplaySystemDescriptorBlock;

typedef DisplaySystemDescriptorBlock DSDB;

typedef enum 
{
	diff_NoDiff = 0,
	diff_Size,
	diff_Number,
	diff_WorkSpace,
	diff_GammaRamp,
	diff_MonitorControls

}DSDB_Differences;
#endif
