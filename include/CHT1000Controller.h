#ifndef CHT1000CONTROLLER_H_DEFINED
#define CHT1000CONTROLLER_H_DEFINED

#include "CDigitalController.h"
#include "NECProjectorInterface.h"

class CHT1000Controller : public CDigitalController
{
public:
	CHT1000Controller(CVesaMonitor *mon = NULL) {m_monitor = mon;}
	virtual char *GetControllerType () {return "HT1000 Interface";}
	CNECProjectorInterface m_com;
	int m_port;
	virtual bool OpenDevice (VESAMonitorContext *vmc, short port);
	virtual bool CloseDevice (VESAMonitorContext *vmc, short port);
	virtual short SetVCPFeature(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short GetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent, short *sStatus);
	
	virtual bool FindPhotometry(VESAMonitorContext cp, DM_PHOTOMETRYSETUP *Photometry);
	virtual short GetEDIDBlock (VESAMonitorContext device, unsigned char ucOffset, unsigned char *ucBlockData );
	void SetCommPort (short port);
};
#endif