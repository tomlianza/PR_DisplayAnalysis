#ifndef __CMAC_VESAMONITOR__

#ifdef OS9_DRIVER

typedef struct {
	short				gVersion;
	short				gType;
	short				gFormulaSize;
	short				gChanCnt;
	short				gDataCnt;
	short				gDataWidth;
	unsigned char		gData[256*3];
} GammaRec, *GammaPtr, **GammaHandle;
#else

#ifdef PROJECTBUILDER
#else
    #include <CGDirectDisplay.h>
#endif

#endif

class COSDBase;
class COSDWrapper;

class CVesaMonitor : public CVesaMonitorBase
{
public:
	
	CVesaMonitor();
	virtual ~CVesaMonitor();
	
	bool SetDeviceLUTs(CSIGammaRamp *gr);
	bool GetDeviceLUTs(CSIGammaRamp *gr);

	
	#ifdef OS9_DRIVER
		DisplayIDType m_DeviceID;
	#else
		CGDirectDisplayID m_DeviceID;
	#endif

	long m_DeviceRefNum;
	OSStatus GrafInfoGetCardEDID(unsigned char* edid);
	
	#ifdef OS9_DRIVER
		inline void SetDirectDeviceID(DisplayIDType dID) {m_DeviceID = dID;}
		inline DisplayIDType GetDirectDeviceID() {return m_DeviceID;}
		GammaHandle ReadGamma ( short refnum );
		void SetGamma ( short refnum, GammaPtr thegamma );
	#else
		inline void SetDirectDeviceID(CGDirectDisplayID dID) {m_DeviceID = dID;}
		inline CGDirectDisplayID GetDirectDeviceID() {return m_DeviceID;}
    #endif

	inline void SetDeviceRefNum(long refNum) {m_DeviceRefNum = refNum;}
	inline long GetDeviceRefNum() {return m_DeviceRefNum;}

	virtual bool GetKeyNameFromEDID(char *keyName);
	virtual bool FormatDSDBFileName(char *name, char *serNo, char *fileName);

	COSDBase* 		GetOSDBase(){ return m_COSD; }
	void 				SetOSDBase( COSDBase* o) { m_COSD = o; }
	COSDWrapper*	GetOSDWrapper(){ return m_OSDWrapper; }
	void 				SetOSDWrapper(COSDWrapper *w) { m_OSDWrapper = w; } 
	
	#ifdef USE_GAMMAVAL_FILE
	bool WriteGammaFile(bool beverbose);
	#endif
	
	#ifdef USE_LUTDATA_FILE
	bool WriteLUTDataFile(bool beverbose, GammaRamp *gr, GammaRampEx *grex);
	#endif
	
	#ifdef SUPPORT_MULTIPLE_DSDBS
   	bool WriteSecondaryDSDB();
	bool FindSecondaryDSDBFiles();
	bool MakeDefaultDSDBFile(char *name);
	bool SetPrimaryDSDB(char *sourceName);
	#endif

protected:
	COSDBase	*m_COSD;
	COSDWrapper *m_OSDWrapper;
	
};
#endif