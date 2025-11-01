/*
 *  CMacEizoController.h
 *  BlueEye.XCode
 *
 *  Created by Ben Guthro on Mon Jan 26 2004.
 *  Copyright (c) 2004 SequelImaging. All rights reserved.
 *
 */

#ifndef CEizoCONTROLLER_H_DEFINED
#define CEizoCONTROLLER_H_DEFINED

#include "CDigitalController.h"

class CEizoController : public CDigitalController
{
private:
	bool deviceOpen;
	
	HANDLE eizMonPtr;
public:
	
	CEizoController(CVesaMonitor *mon = NULL) {m_monitor = mon;deviceOpen=false;eizMonPtr=NULL;}
	virtual ~CEizoController();
	
	virtual char *GetControllerType () {return "Eizo USB Interface";}

	//virtual char *GetControllerType () {return "Macintosh OSX Eizo Interface";}

	virtual bool OpenDevice (VESAMonitorContext vmc=NULL, short port=0);
	virtual bool CloseDevice (VESAMonitorContext vmc=NULL, short port=0);
	virtual short SetVCPFeature(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short GetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent, short *sStatus);
	
	virtual short GetEDIDBlock (VESAMonitorContext device, unsigned char ucOffset, unsigned char *ucBlockData );
	virtual short GetCapabilities(VESAMonitorContext device, unsigned char *ucBuf, short *sLength);
	
	virtual bool IsDigitallyEnabled() {return true;}
	virtual CDigitalController::DDC_CONTROLLER_STATUS CMacEizoController::SupportsDDC(VESAMonitorContext device);
	
	virtual bool IsSoftwareDDC() { return true;}
	
	virtual bool SaveMonitorSettings(VESAMonitorContext device);
	virtual bool EnableOnScreenControls(VESAMonitorContext device, bool enable);
	
	void SetEizMonHandle(HANDLE h){ eizMonPtr = h; }
	HANDLE GetEizMonHandle() {return eizMonPtr; }
	
	int VCP2Eizo(DMC_CONTROL DMC);
	DMC_CONTROL Eizo2VCP(int eiz);
	
	//Support for storing LUTs in the display
	//these will always be represented in float format 0.0-1.0
	//until we get to the storage in the hardware
	virtual bool SupportsDisplayHardwareLUT();
	virtual bool GetDisplayHardwareLUT(float *r, float *g, float *b, int inarrsize);
	virtual bool SetDisplayHardwareLUT(float *r, float *g, float *b, int inarrsize);
};

#endif
