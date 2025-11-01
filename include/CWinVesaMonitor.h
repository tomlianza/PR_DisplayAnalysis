class CVesaMonitor : public CVesaMonitorBase
{
public:
	
	CVesaMonitor();
	virtual ~CVesaMonitor();
		
	bool SetDeviceLUTs(CSIGammaRamp *gr);
	bool GetDeviceLUTs(CSIGammaRamp *gr);

	CString m_DeviceName, m_DeviceString, m_DeviceKey, m_DeviceID;

	DWORD m_Flags;
	HDC m_hDC;
	HMONITOR m_hm;

	inline void SetDeviceName(char *str) {m_DeviceName = str;}
	inline void SetDeviceString(char *str) {m_DeviceString = str;}
	inline void SetDeviceID(char *str) {m_DeviceID = str;}
	inline void SetDeviceKey(char *str) {m_DeviceKey = str;}
	inline void SetFlags(DWORD flags) { m_Flags = flags;}
	inline void SetHDC(HDC hDC) {m_hDC = hDC;}
	inline void SetDimensions (long l, long r, long t, long b) {m_l=l; m_r=r; m_t=t; m_b=b;}
	inline void SetHMonitor (HMONITOR hm) {m_hm = hm;}

	inline CString& GetDeviceName() {return m_DeviceName;}
	inline CString& GetDeviceString() {return m_DeviceString;}
	inline CString& GetDeviceID() {return m_DeviceID;}
	inline CString& GetDeviceKey() {return m_DeviceKey;}
	inline DWORD GetFlags() {return m_Flags;}
	CString m_firstDeviceID;
	inline void SetFirstDeviceID(char *str) {m_firstDeviceID = str;}
	inline CString& GetFirstDeviceID() {return m_firstDeviceID;}

	inline HDC GetHDC() {return m_hDC;}
	inline HMONITOR GetHMonitor() {return m_hm;}

#ifdef SUPPORT_DSDB_SUFFIX
	bool FormatDSDBFileName(char *name, char *serNo, char *fileName, char *suffix=NULL);
#else
	bool FormatDSDBFileName(char *name, char *serNo, char *fileName);
#endif

	char *GetMonitorDirectory();
	bool WriteSecondaryDSDB();
	bool FindSecondaryDSDBFiles();
	bool MakeDefaultDSDBFile(char *name);
	bool SetPrimaryDSDB(char *sourceName);
};