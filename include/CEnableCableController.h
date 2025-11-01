#ifndef CENABLECABLECONTROLLER_H_DEFINED
#define CENABLECABLECONTROLLER_H_DEFINED

#include "CMCCSController.h"

class CEnableCableController : public CMCCSController
{
public:
	CEnableCableController(CVesaMonitor *mon = NULL) {m_monitor = mon;}
	virtual ~CEnableCableController(){};
	virtual char *GetControllerType () {return "Enable Cable Interface";}
	virtual bool OpenDevice (VESAMonitorContext *v, short arg);
	virtual bool CloseDevice (VESAMonitorContext *v, short arg);
	virtual short SetVCPFeature(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short GetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent, short *sStatus);

	virtual short GetEDIDBlock (VESAMonitorContext device, unsigned char ucOffset, unsigned char *ucBlockData );
	virtual short GetCapabilities(VESAMonitorContext device, unsigned char *ucBuf, short *sLength);
	virtual DDC_CONTROLLER_STATUS SupportsDDC(VESAMonitorContext device) { return FULL_SUPPORT;} // Assumed for enable cables.

	virtual bool SaveMonitorSettings(VESAMonitorContext cp);
	virtual bool EnableOnScreenControls(VESAMonitorContext cp, bool enable);

	virtual bool CanProbeForBrightness() {return true;}
	virtual bool CanProbeForContrast() {return true;}
};
#endif