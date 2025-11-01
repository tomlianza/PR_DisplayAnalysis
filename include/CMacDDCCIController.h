/*
 *  CMacDDCCIController.h
 *  BlueEye.XCode
 *
 *  Created by Ben Guthro on Mon Jan 26 2004.
 *  Copyright (c) 2004 SequelImaging. All rights reserved.
 *
 */

#ifndef CMacDDCCICONTROLLER_H_DEFINED
#define CMacDDCCICONTROLLER_H_DEFINED

#include "CMCCSController.h"
#include "mccsEnums.h"
#include "FakeMacTypes.h"

#ifdef OS9_DRIVER
#error This file should only be used in Mac 10.3 and above
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <ApplicationServices/ApplicationServices.h>
#include <IOKit/i2c/IOI2CInterface.h>
#ifdef __cplusplus
}
#endif

class CMacDDCCIController : public CMCCSController
{
protected:
	io_service_t	service;
	io_service_t	interface;
	IOI2CConnectRef	connect;
	unsigned char responseBuf[128];
	short rBufSize;
	CGDirectDisplayID theDisplayID;
	bool deviceOpen;
public:
	
	CMacDDCCIController(CVesaMonitor *mon = NULL) {m_monitor = mon;deviceOpen=false;}
	virtual ~CMacDDCCIController();
	
	virtual char *GetControllerType () {return "Mac DDC/CI Interface";}

	short SendI2CMessage(VESAMonitorContext *device,unsigned char *cBuf, int sendBytes);
	short GetAB_I2CMessage(VESAMonitorContext *device, BYTE *inBuf, short &sInLength);

	//virtual char *GetControllerType () {return "Macintosh OSX DDCci Interface";}

	virtual bool OpenDevice (VESAMonitorContext vmc=NULL, short port=0);
	virtual bool CloseDevice (VESAMonitorContext vmc=NULL, short port=0);
	virtual short SetVCPFeature(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short SetVCPFeatureUtil(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short GetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent, short *sStatus);
	
	virtual short LoGetVCPFeatureUtil (VESAMonitorContext *device, DMC_CONTROL VCP, short *sMax, short *sCurrent,short *sStatus, int usToWait);
	virtual short LoGetVCPFeatureEx(VESAMonitorContext *device, DMC_CONTROL VCP, short *sMax, short *sCurrent,short *sStatus, int usToWait);
	
	virtual short GetEDIDBlock (VESAMonitorContext device, unsigned char ucOffset, unsigned char *ucBlockData );
	virtual short GetCapabilities(VESAMonitorContext device, unsigned char *ucBuf, short *sLength);

	inline void SetServiceID(io_service_t dID) {service = dID;}
	inline io_service_t GetServiceID() {return service;}
	
	CGDirectDisplayID GetDisplayID (void);
	void SetDisplayID (CGDirectDisplayID dID);
	
	virtual bool IsDigitallyEnabled() {return true;}
	virtual CDigitalController::DDC_CONTROLLER_STATUS CMacDDCCIController::SupportsDDC(VESAMonitorContext device);
	virtual bool IsSoftwareDDC() { return true;}
	
	virtual bool SaveMonitorSettings(VESAMonitorContext device);
	virtual bool EnableOnScreenControls(VESAMonitorContext device, bool enable);
};

#endif
