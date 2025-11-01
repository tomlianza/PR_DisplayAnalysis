class CDisplayAdapter : public CDisplayAdapterBase
{
public:
	CDisplayAdapter();
	virtual ~CDisplayAdapter();

	CString m_DeviceName, m_DeviceString, m_DeviceKey, m_DeviceID;
	DWORD m_Flags;

	inline void SetDeviceName(char *str) {m_DeviceName = (CString)str;}
	inline void SetDeviceString(char *str) {m_DeviceString = (CString)str;}
	inline void SetDeviceID(char *str) {m_DeviceID = (CString)str;}
	inline void SetDeviceKey(char *str) {m_DeviceKey = (CString)str;}
	inline void SetFlags(DWORD flags) { m_Flags = flags;}

	inline char *GetDeviceName() {return m_DeviceName.GetBuffer(0);}
	inline char *GetDeviceString() {return m_DeviceString.GetBuffer(0);}
	inline char *GetDeviceID() {return m_DeviceID.GetBuffer(0);}
	inline char *GetDeviceKey() {return m_DeviceKey.GetBuffer(0);}
	inline DWORD GetFlags() {return m_Flags;}

	virtual char *GetDeviceNameForPrinting();

	virtual bool SupportsVideoOverlay();

	char m_DeviceNameForPrinting[512];
};