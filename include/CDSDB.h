#ifndef CDSDB_H_INCLUDED
#define CDSDB_H_INCLUDED

#include "DSDB.h"

typedef enum {
	DSDB_STATUS_OK,
	DSDB_STATUS_WRITE_ERROR,
	DSDB_STATUS_READ_ERROR,
	DSDB_STATUS_NUM_STATES
} DSDB_STATUS;

class CDSDB
{
public:
	CDSDB();
	virtual ~CDSDB();

protected:
	DSDB m_DSDB;
	bool rDoubleSet,gDoubleSet,bDoubleSet;

public:
	inline short GetVersion() {return m_DSDB.sVersionID;}
	inline void SetVersion(short version) {m_DSDB.sVersionID = version;}

	inline DISPLAY_TECHNOLOGY GetTechnology() {return m_DSDB.m_DisplayTechnology;}
	inline void SetTechnology(DISPLAY_TECHNOLOGY tech) { m_DSDB.m_DisplayTechnology = tech;}

	inline bool GetBiasReverseFlag() {return m_DSDB.m_bBiasesReversed;}
	inline void SetBiasReverseFlag(bool flag) {m_DSDB.m_bBiasesReversed = flag;}

	inline void SetCanAdjustBrightness(bool can) {m_DSDB.m_bCanAdjustBrightness = can;}
	inline bool GetCanAdjustBrightness() {return m_DSDB.m_bCanAdjustBrightness;}
	
	inline void SetCanAdjustContrast(bool can) {m_DSDB.m_bCanAdjustContrast = can;}
	inline bool GetCanAdjustContrast() {return m_DSDB.m_bCanAdjustContrast;}
	
	inline void SetCanAdjustManualColorTemp(bool can) {m_DSDB.m_bCanAdjustColorTemp = can;}
	inline bool GetCanAdjustManualColorTemp() {return m_DSDB.m_bCanAdjustColorTemp;}

	inline void SetCanAdjustDigitalColorTemp(bool can) {
		//#ifdef SUPPORT_DIGITAL_COLORTEMP
		#if 1
		m_DSDB.m_bCanAdjustDigitalColorTemp = can;
		#endif
		}
	inline bool GetCanAdjustDigitalColorTemp() {
		//#ifdef SUPPORT_DIGITAL_COLORTEMP
		#if 1
		return m_DSDB.m_bCanAdjustDigitalColorTemp;
		#else
		return false;
		#endif
	}
	

	inline void SetCanAdjustGains(bool can) {m_DSDB.m_bCanAdjustGains = can;}
	inline bool GetCanAdjustGains() {return m_DSDB.m_bCanAdjustGains;}

	inline void SetMDFDefinitionVersion(long ver) {m_DSDB.m_MDFDefinitionVersion = ver;}
	inline long GetMDFDefinitionVersion() {return m_DSDB.m_MDFDefinitionVersion;}

	inline void SetMDFFileVersion(long ver) {m_DSDB.m_MDFFileVersion = ver;}
	inline long GetMDFFileVersion() {return m_DSDB.m_MDFFileVersion;}

	inline void SetMDFSource(char *src) {strcpy(m_DSDB.m_MDFSource, src);}
	inline char *GetMDFSource() {return m_DSDB.m_MDFSource;}

	inline void SetDisplayableName(char *src) {strcpy(m_DSDB.m_DisplayableName, src);}
	inline char *GetDisplayableName() {return m_DSDB.m_DisplayableName;}

	inline void SetInternalLUTDepth(int depth) {m_DSDB.m_InternalLUTDepth = depth;}
	inline int GetInternalLUTDepth() {return m_DSDB.m_InternalLUTDepth;}

	inline void SetInternalLUTChannels(int Channels) {m_DSDB.m_InternalLUTChannels = Channels;}
	inline int GetInternalLUTChannels() {return m_DSDB.m_InternalLUTChannels;}

	inline void SetMDFNonDigital(bool nd) {m_DSDB.m_MDFIsForNDMonitor = nd;}
	inline bool GetMDFNonDigital() {return m_DSDB.m_MDFIsForNDMonitor;}

	inline void SetPreferredMonitorPreset(int p) {m_DSDB.m_preferredMonitorPreset = p;}
	inline int GetPreferredMonitorPreset() {return m_DSDB.m_preferredMonitorPreset;}

	inline DSDB *GetDSDB() {return &m_DSDB;}

	inline MonitorControls *GetMonitorControls() {return &m_DSDB.mcData;}
	inline MonitorDefaults *GetMonitorDefaults() {return &m_DSDB.mdData;}
	inline CSIGammaRamp *GetGammaRamp() {return &m_DSDB.grData;}
	inline BYTE *GetRawEDID() {return &m_DSDB.btEDID[0];}

	inline sicmWorkSpaceDescriptor* GetWSD() {return &m_DSDB.sicmWSD;}

	inline void SetDigitallyEnabled(bool enabled) {m_DSDB.bDigitallyEnabled = enabled;}
	inline bool DigitallyEnabled() {return m_DSDB.bDigitallyEnabled;}

	inline CalibrationInfo* GetCalInfo() {return &m_DSDB.CalInfo;}


    inline sicmMeasurementSet* GetMeasurementSet() { return &m_DSDB.m_MeasurementSet; }
	
	bool GetOverriddenGains(short *red, short *green, short *blue);
	void SetOverriddenGains(short red, short green, short blue);

	bool GetOverriddenBiases(short *red, short *green, short *blue);
	void SetOverriddenBiases(short red, short green, short blue);

	
	bool GetLutDoubleVals(double *r, double *g, double *b);
	
	void SetLutDoubleVals(double *r, double *g, double *b);
	void SetLutDoubleRed(double *r);
	void SetLutDoubleGreen(double *g);
	void SetLutDoubleBlue(double *b);

	inline double GetLastAmbientLuxValue(){return m_DSDB.m_lastAmbientLux;}
	inline void SetLastAmbientLux(double dIn){ m_DSDB.m_lastAmbientLux = dIn; }
	inline bool GetShouldUseLastAmbientLux(){return m_DSDB.m_shouldUseLastAmbientLux; }
	inline void SetShouldUseLastAmbientLux(bool use){m_DSDB.m_shouldUseLastAmbientLux=use; }
	
	FILE *m_dumpFP;
	bool InitDumpFile (char *fname);
	bool Dump();
	bool Dump(char *fname);
	bool Dump(FILE *fp);
	void CloseDumpFile();
};

#endif
