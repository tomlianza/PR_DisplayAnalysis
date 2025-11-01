class CMonitorWorld : public CMonitorWorldBase
{
public:
	CMonitorWorld();
	virtual ~CMonitorWorld();

	bool Init();
	void InventoryMonitors();	
	CVesaMonitor* GetMonitorFromHDC();

	bool GetMonitorsOfSpecificModel (char *model, list<CVesaMonitor*>*);
	bool ResetDigitalControllerToNull(CVesaMonitor *mon, char *textToDisplay);
	
	// Return a list of CVesaMonitors with device name matching (or partially
	// matching) passed in string. These must be marked as "on desktop".
	bool GetMonitorsMatchingDeviceName (char *, list<CVesaMonitor*>*); 

protected:
	bool m_initialized;
};

bool GetCurrentMonitorInfo (DISPLAY_DEVICE *dd);
BOOL CALLBACK XMonitorInfoEnumCallback(HMONITOR hm, HDC , RECT* , LPARAM hInfo);
DWORD XGetEDIDForCurrentMonitor(char* regKey, char *edid, bool *isValid);