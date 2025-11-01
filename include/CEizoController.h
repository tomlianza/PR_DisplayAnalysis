/*
 *  CMacEizoController.h
 *
 *  Created by Ben Guthro on Mon Jan 26 2004.
 *  Copyright (c) 2004 GretagMacbeth. All rights reserved.
 *
 */

#ifndef __CEizoCONTROLLER_H_DEFINED__
#define __CEizoCONTROLLER_H_DEFINED__

#include "CDigitalController.h"

class CEizoController : public CDigitalController
{
protected:
	HANDLE eizMonPtr;
	VESAMonitorContext m_vmc;

	int VCP2Eizo(DMC_CONTROL DMC);
	DMC_CONTROL Eizo2VCP(int eiz);
	WORD EizoDoubleEncode(double dVal);
	double EizoDoubleDecode(WORD wVal);
public:
	
	CEizoController(CVesaMonitor *mon = NULL) {m_monitor = mon;eizMonPtr=NULL;}
	virtual ~CEizoController();
	
	virtual char *GetControllerType () {return "Eizo USB Interface";}

	virtual bool OpenDevice (VESAMonitorContext vmc, short port=0);
	virtual bool CloseDevice (VESAMonitorContext vmc, short port=0);
	virtual short SetVCPFeature(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short GetVCPFeatureEx(VESAMonitorContext device, DMC_CONTROL VCP, short *sMax, short *sCurrent, short *sStatus);
	
	virtual short GetEDIDBlock (VESAMonitorContext device, unsigned char ucOffset, unsigned char *ucBlockData );
	virtual short GetCapabilities(VESAMonitorContext device, unsigned char *ucBuf, short *sLength);
	
	virtual bool IsDigitallyEnabled() {return true;}
	virtual CDigitalController::DDC_CONTROLLER_STATUS SupportsDDC(VESAMonitorContext device);
	
	virtual bool IsSoftwareDDC() { return true;}
	
	virtual bool SaveMonitorSettings(VESAMonitorContext device);
	virtual bool EnableOnScreenControls(VESAMonitorContext device, bool enable);
		
	//Support for storing LUTs in the display
	//these will always be represented in float format 0.0-1.0
	//until we get to the storage in the hardware
	virtual bool SupportsDisplayHardwareLUT(VESAMonitorContext cp);
	virtual bool GetDisplayHardwareLUT(double *r, double *g, double *b, int inarrsize);
	virtual bool SetDisplayHardwareLUT(double *r, double *g, double *b, int inarrsize);
	
	// Non virtual functions
	void SetEizMonHandle(HANDLE h){ eizMonPtr = h; }
	HANDLE GetEizMonHandle() {return eizMonPtr; }
	bool GetModelAndSN(char* model, int modelsz, char* sn, int snsz);
	char *GetPresetName(int FineContrastNumber);
};

#endif
