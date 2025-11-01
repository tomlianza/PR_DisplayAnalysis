#if !defined(AFX_COSDBASE_H__D3759680_2EB7_11D6_BA4D_44455354616F__INCLUDED_)
#define AFX_COSDBASE_H__D3759680_2EB7_11D6_BA4D_44455354616F__INCLUDED_

#if defined(LINUX) || defined(QT_KIT)
		#include "siLabels.h"
        #include "procolor.h"
        #define OSD_OBJ_TYPE ProColor
#endif



#include <CVesaMonitor.h>
#include "OSDStructures.h"

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// COSD dialog
class COSDBase;



#ifndef OSD_OBJ_TYPE
#define OSD_OBJ_TYPE COSD
#endif


class OSD_OBJ_TYPE;

class COSDBase
{
// Construction
public:
	enum {MAX_CONTROLS = OSD_MAX_CONTROLS};
	
	void BuildSliderControlStructures();
	void UpdateDSDB();
	bool LoadStrings();
	void ProcessSliderValueChange(int index, short newValue);
	void RefreshInitialControlValues();
	void GetInitialControlValues();
	void SetPanelType(OSD_TYPE type);
	void ProcessRestore();
	void ProcessDone();
	void ProcessReset();

	void UpdateDataFromDialog();
	void CommitDataToDialog();
	void CommitAllDataToDialog();
	void SetOSDWindowTitle(int id);
	void SetOSDResetTitle(int id);
	void SetOSDRestoreTitle(int id);
	void InitAndShowControl (int j, int minVal, int maxVal, int curVal, char *titleStr);
	void HideControl(int i);

	void OSDEpilog();
	void OSDMessageBoxAndStop (char *msg, char *title);
	bool OSDMessageBoxContinue (char *msg, char *title);
	void OSDSetBackground();
	bool OSDVerifyRestore();
	
	void InitSliders();
	OSD_TYPE m_type;
	void SetType (OSD_TYPE osdType);
	COSDBase(OSD_OBJ_TYPE *osd, CVesaMonitor *mon); 
	CVesaMonitor *m_monitor;
	
	void ResetControlsFromOriginalValues(OSD_TYPE type);
	void RepaintSliders(OSD_TYPE type);
	bool m_savedGainsAndBiases;

#ifdef SUPPORT_FRINGE_SLIDERS
	void SaveFringingResults();
	void SaveGainsAndBiases();
	void SaveBrightnessAndContrast();
	void RestoreSavedGainsAndBiases();
	void RestoreSavedBrightnessAndContrast();
	short m_savedRedVideoGain, m_savedGreenVideoGain, m_savedBlueVideoGain;
	short m_savedRedVideoBlackLevel, m_savedGreenVideoBlackLevel, m_savedBlueVideoBlackLevel;
	short m_savedBrightness, m_savedContrast;
	short m_maxBrightness, m_maxContrast;
	bool m_savedBrightnessAndContrast;
#endif

	OSD_OBJ_TYPE *m_COSD;
};
#endif

