#ifndef CPDDDCCONTROLLER_H_DEFINED
#define CPDDDCCONTROLLER_H_DEFINED

#include "CDigitalController.h"

#ifdef NEWPDISTUFF
extern BOOLEAN Loadi2c(void);
#else
extern HMODULE Loadi2c( void );
#endif
extern void Freei2c ();

#define PD_MAX_CARDS 2
#define PD_MAX_MONS_PER_CARD 4

typedef struct
{
	int portToUse;
	unsigned char EDID[256];
} PD_DDC_DATA;

extern int GetEDIDsViaDDC(PD_DDC_DATA *edids);

class CPDDDCController : public CDigitalController
{
public:
	CPDDDCController(CVesaMonitor *mon = NULL) {m_monitor = mon;}
	
	virtual char *GetControllerType () {return "Soft DDC Interface";}

	virtual bool OpenDevice (VESAMonitorContext *vmc, short port);
	virtual bool CloseDevice (VESAMonitorContext *vmc, short port);

	virtual short SetVCPFeature(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short GetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent, short *sStatus);

	virtual short GetEDIDBlock (VESAMonitorContext device, unsigned char ucOffset, unsigned char *ucBlockData );
	virtual short GetCapabilities(VESAMonitorContext device, unsigned char *ucBuf, short *sLength);

	short LoGetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent,short *sStatus);
	short LoGetVCPFeatureUtil (VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent,short *sStatus);
	virtual DDC_CONTROLLER_STATUS SupportsDDC(VESAMonitorContext device);
	virtual bool IsSoftwareDDC() { return true;}

	virtual bool SaveMonitorSettings(VESAMonitorContext cp);
	virtual bool EnableOnScreenControls(VESAMonitorContext cp, bool enable);
	virtual bool IsDigitallyEnabled() {return true;}
};
#endif
