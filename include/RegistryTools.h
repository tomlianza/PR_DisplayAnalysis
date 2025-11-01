// RegistryTools.h: interface for the CRegistryTools class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRYTOOLS_H__1F7734A0_43F9_11D3_B9F8_004033E05B37__INCLUDED_)
#define AFX_REGISTRYTOOLS_H__1F7734A0_43F9_11D3_B9F8_004033E05B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegistryTools  
{
public:
	CRegistryTools();
	virtual ~CRegistryTools();
	long     BuildGammaRegistryKeys();
	long     BuildEnableCableRegistryKeys();
	long     CreateLocalMachineKey();
	long     SetLocalMachineKeyValueDigital(HKEY hKey,LPCSTR string,unsigned char *usBuf,long length);
	long     GetLocalMachineKeyValueDigital(HKEY hKey,LPCSTR string,unsigned char *usBuf,DWORD *length);
	long     GetGammaConfigValue();
	long     SetGammaConfigValue(DWORD dwConfig);
	long     GetGammaProfileName(char *ProfileName);
	long     SetGammaProfileName(char *ProfileName);
	long     GetGammaLut(char *lut,short *sSize);
	long     SetGammaLut(char *lut,short sSize);

	long     SetEnableCableConfiguration(char *data,short sSize);
	long     GetEnableCableConfiguration(char *data,short *sSize);
	
	long     SetEnableCableMonitor(char *data,short sSize);
	long     GetEnableCableMonitor(char *data,short *sSize);
	
	long     SetEnableCableLut(char *lut,short sSize);
	long	 GetEnableCableLut(char *lut,short *sSize);

	char     m_hkKeyName[4096];
	DWORD    m_hkWhatHappened;
	HKEY m_hkBuffer;
	HKEY m_hkGammaConfiguration ;		// 
	HKEY m_hkLut;						// HKEY_LOCAL_MACHINE\Software\Sequel\GammaCal\CurrentLut  
	HKEY m_hkWhichCalibrator;			// HKEY_LOCAL_MACHINE\Software\Sequel\GammaCal\CurrentCal 
	HKEY m_hkWhichInterface;			// HKEY_LOCAL_MACHINE\Software\Sequel\GammaCal\CurrentCalIF 
	HKEY m_hkInterCalLut;				// HKEY_LOCAL_MACHINE\Software\Sequel\InterCal\InterCalLut
	HKEY m_hkInterCalProfile;			// HKEY_LOCAL_MACHINE\Software\Sequel\InterCal\InterCalLut
	HKEY m_hkInterCalDigitalMonitor;	// HKEY_LOCAL_MACHINE\Software\Sequel\InterCal\DigitalMonitor
	HKEY m_hkGammaCalLut;				// HKEY_LOCAL_MACHINE\Software\Sequel\InterCal\InterCalLut
	HKEY m_hkGammaCalProfile;			// HKEY_LOCAL_MACHINE\Software\Sequel\InterCal\InterCalLut
	HKEY m_hkGammaCalDigitalMonitor;	// HKEY_LOCAL_MACHINE\Software\Sequel\GammaCal\DigitalMonitor
	
	HKEY m_hkEnableCableConfiguration;
	HKEY m_hkEnableCableMonitor;
	HKEY m_hkEnableCableLut;

	HKEY m_hkSICMdata;					// HKEY_LOCAL_MACHINE\Software\Sequel\SICM


};

#endif // !defined(AFX_REGISTRYTOOLS_H__1F7734A0_43F9_11D3_B9F8_004033E05B37__INCLUDED_)
