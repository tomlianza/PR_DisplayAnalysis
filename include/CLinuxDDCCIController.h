/*
 *  Copyright (c) 2004 SequelImaging. All rights reserved.
 *
 */

#ifndef CMacDDCCICONTROLLER_H_DEFINED
#define CMacDDCCICONTROLLER_H_DEFINED

#include "CDigitalController.h"

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <dirent.h>


#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

#ifdef __cplusplus
}
#endif

class CLinuxDDCCIController : public CDigitalController
{
private:
	unsigned char responseBuf[128];
	short rBufSize;
	bool deviceOpen;
	
	char *filename; // the name of the device
	int fd;
public:
	
	CLinuxDDCCIController(CVesaMonitor *mon = NULL);
	virtual ~CLinuxDDCCIController();
	
	virtual char *GetControllerType () {return "Linux DDC/CI Interface";}

	short SendI2CMessage(VESAMonitorContext device,unsigned char *cBuf, int sendBytes);
	short GetAB_I2CMessage(VESAMonitorContext device, BYTE *inBuf, short &sInLength);

	//virtual char *GetControllerType () {return "Macintosh OSX DDCci Interface";}

	virtual bool OpenDevice (VESAMonitorContext *vmc=NULL, short port=0);
	virtual bool CloseDevice (VESAMonitorContext *vmc=NULL, short port=0);
	virtual short SetVCPFeature(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short SetVCPFeatureUtil(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short GetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent, short *sStatus);
	
	short LoGetVCPFeatureUtil (VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent,short *sStatus, int usToWait);
	short LoGetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent,short *sStatus, int usToWait);
	
	virtual short GetEDIDBlock (VESAMonitorContext device, unsigned char ucOffset, unsigned char *ucBlockData );
	virtual short GetCapabilities(VESAMonitorContext device, unsigned char *ucBuf, short *sLength);

	virtual bool IsDigitallyEnabled() {return true;}
	virtual CDigitalController::DDC_CONTROLLER_STATUS CLinuxDDCCIController::SupportsDDC(VESAMonitorContext device);
	virtual bool IsSoftwareDDC() { return true;}
	
	char* GetDeviceFilename() { return filename; }
	void SetDeviceFilename(char *c);
        
        virtual bool SaveMonitorSettings(VESAMonitorContext device);
        virtual bool EnableOnScreenControls(VESAMonitorContext device, bool enable);
};

#endif
