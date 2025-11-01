// SmartBiasCtrl.h: interface for the CSmartBiasCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMARTBIASCTRL_H__73AE4040_FD32_11D6_A857_0010B508B447__INCLUDED_)
#define AFX_SMARTBIASCTRL_H__73AE4040_FD32_11D6_A857_0010B508B447__INCLUDED_

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

typedef struct _brtMaxMinData 
{
	double dMaxLum;
	double dMinLum;
	short  sBrightness;

}brtMaxMinData;

typedef struct _brtSlopeBiasData
{
	double dSlope;
	double dOffset;


}brtSlopeBiasData; 

typedef struct _brtMaxMinDataSet
{
	short nBiasVals;

	brtMaxMinData			dMM[256];
	brtSlopeBiasData		dSBH[256]; //High luminance set;
	brtSlopeBiasData        dSBL[256]; // Low luminance;


}brtMaxMinDataSet;
class CSmartBiasCtrl  
{
public:
	CSmartBiasCtrl();
	virtual ~CSmartBiasCtrl();
	short						m_Index;
	brtMaxMinDataSet			m_MMData;
	short                       m_FOMPeakIndex;

	double			m_dContrastRatio[256];
	double          m_dFOM[256];
	double          m_dLowLuminance[256];
	double          m_dHighLuminance[256];

// the following routines must be called prior to calling CalcDisplayMetrics;

	// data is expected to be filled in Low to high order of brightness setting....

	void SetNumBrightnessLevels(short sBrightnessLevels, int* indices);
	void SetHighLowData(short sBrightnessControlValue, double HighLuminance, double LowLuminance);
// This calcs all the supplementary data needed 	
	bool CalcDisplayMetrics(); // called after filling the HighLow data and setting the number of values;

	short GetPeakCRsetting();
	short GetBrightnessSettingForLuminance(double dLuminace);

	bool  DarkLumInRange(double dLuminance);
	bool  HighLumInRange(double dLuminance); 



	
	


};

#endif // !defined(AFX_SMARTBIASCTRL_H__73AE4040_FD32_11D6_A857_0010B508B447__INCLUDED_)
