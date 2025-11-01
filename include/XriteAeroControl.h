typedef HRESULT (WINAPI *MY_SET_AERO_PROC)(UINT);
typedef HRESULT (WINAPI *MY_GET_AERO_PROC)(BOOL *);

class CXriteAeroControl
{
public:
	virtual ~CXriteAeroControl();
	CXriteAeroControl();

	bool AeroLibLoaded();
	bool AeroIsEnabled();
	bool EnableAero (bool enable);
	
	MY_SET_AERO_PROC m_AeroSetProc;
	MY_GET_AERO_PROC m_AeroGetProc;
	HINSTANCE m_hAeroLib;

	bool m_aeroWasEnabledAtStart;
	bool m_aeroTried;
};
